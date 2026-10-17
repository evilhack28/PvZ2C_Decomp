"""Recover `m_x = constant;` lines from a game constructor by matching stores to header members (used by autofill)."""

import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import config
from lib import hdrindex
from capstone import CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN, Cs
from lib.pvzelf import Elf

MD = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)
ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), os.pardir, os.pardir)
_OFFS = {}


def class_body(text, cls):
    m = re.search(r'^\s*(?:class|struct)\s+(?:\w+\s+)?' + re.escape(cls) + r'\s*(?:final\s*)?(?::[^;{]*)?\{', text, re.M)
    if not m:
        return None
    depth, i = 0, m.end() - 1
    for j in range(i, len(text)):
        if text[j] == '{':
            depth += 1
        elif text[j] == '}':
            depth -= 1
            if depth == 0:
                return text[i + 1:j]
    return None


def member_names(body):
    """Names of data members declared directly in a class body (depth 1, no parentheses)."""
    out, depth, cur = [], 0, ''
    for c in body:
        if c == '{':
            depth += 1
        elif c == '}':
            depth -= 1
            cur = ''
        elif depth == 0:
            if c == ';':
                s = re.sub(r'//[^\n]*', '', cur).strip()
                if s and '(' not in s and not s.startswith(('typedef', 'using', 'friend', 'enum', 'struct', 'class', 'static', 'RT_')):
                    s = s.split('=')[0].strip()
                    m = re.search(r'(\w+)(?:\[[^\]]*\])?$', s)
                    if m and ' ' in s.replace('\t', ' ') and not s.endswith(':'):
                        out.append(m.group(1))
                cur = ''
            else:
                cur += c
    return out


def offsets(cls):
    """{offset: member name} from an offsetof probe compiled against the class header."""
    if cls in _OFFS:
        return _OFFS[cls]
    _OFFS[cls] = {}
    rel = hdrindex.header_of(cls)
    if not rel:
        return {}
    text = open(os.path.join(ROOT, rel), encoding='utf-8', errors='replace').read()
    body = class_body(text, cls)
    names = member_names(body) if body else []
    if not names:
        return {}
    probe = os.path.join(config.BUILD, 'ctorprobe_%d.cpp' % os.getpid())
    with open(probe, 'w') as f:
        f.write('#define private public\n#define protected public\n#include "SexyAppFramework/Common.h"\n#include "%s"\n'
                '#include <stddef.h>\ntemplate<int N> struct Show;\n' % os.path.basename(rel))
        for i, n in enumerate(names):
            f.write('Show<(int)offsetof(%s, %s)> p%d;\n' % (cls, n, i))
    r = subprocess.run([config.GXX, *config.CXXFLAGS, '-w', '-I', os.path.dirname(os.path.join(ROOT, rel)), '-fsyntax-only', probe],
                       capture_output=True, text=True)
    os.remove(probe)
    got = {}
    for m in re.finditer(r'Show<(\d+)> p(\d+)', r.stderr):
        got.setdefault(int(m.group(1)), names[int(m.group(2))])
    _OFFS[cls] = got
    return got


_NAMES = None


def _names():
    global _NAMES
    if _NAMES is None:
        e = Elf(config.TARGET_LIB)
        _NAMES = {}
        for n, v, sz, sh, t in e.symbols():
            if sh and t == 2 and sz:
                _NAMES.setdefault(v, n)
    return _NAMES


def stores(sym):
    """[(offset, value)] of constant stores through `this` after the base constructor call."""
    e = Elf(config.TARGET_LIB)
    found = e.function(sym)
    if not found:
        return []
    addr, size, code = found
    this, imm, out, seenbl, last = {'x0'}, {}, [], False, None
    for i in MD.disasm(code, addr):
        m, ops = i.mnemonic, [x.strip() for x in i.op_str.split(',')]
        if m == 'mov' and len(ops) == 2 and ops[1] == 'x0' and ops[0].startswith('x'):
            this.add(ops[0])
        elif m == 'mov' and len(ops) == 2 and ops[1].startswith('#') and ops[0][0] in 'wx':
            imm[ops[0]] = int(ops[1][1:], 0)
        elif m == 'bl':
            seenbl = True
            try:
                last = _names().get(int(ops[0].lstrip('#'), 0))
            except ValueError:
                last = None
        elif m in ('str', 'strb', 'strh') and len(ops) >= 2 and seenbl:
            mm = re.match(r'\[(x\d+)(?:, #(0x[0-9a-f]+|\d+))?\]', ', '.join(ops[1:]))
            if mm and mm.group(1) in this:
                off = int(mm.group(2), 0) if mm.group(2) else 0
                reg = ops[0]
                val = 0 if reg in ('wzr', 'xzr') else imm.get(reg)
                if val is None and last and reg in ('s0', 'd0', 'w0', 'x0'):
                    fm = re.fullmatch(r'_Z(\d+)(\w+)v', last)
                    if fm and len(fm.group(2)) == int(fm.group(1)):
                        val = fm.group(2) + '()'
                if val is not None and off >= 8:
                    out.append((off, val))
                last = None
    return out


def body_lines(cls, sym):
    """'\tm_x = 1;\n' lines for the constructor, or '' when nothing could be recovered."""
    st = stores(sym)
    if not st:
        return ''
    names = offsets(cls)
    lines = []
    for off, val in st:
        n = names.get(off)
        if not n:
            return ''
        if isinstance(val, int) and val > 1:
            val = '(decltype(%s))%d' % (n, val)
        lines.append('\t%s = %s;\n' % (n, val))
    return ''.join(lines)


def base_of(cls):
    rel = hdrindex.header_of(cls)
    if not rel:
        return None
    t = open(os.path.join(ROOT, rel), encoding='utf-8', errors='replace').read()
    m = re.search(r'(?:class|struct)\s+' + re.escape(cls) + r'\s*(?:final\s*)?:\s*(?:public\s+|protected\s+|private\s+)?([\w:]+)', t)
    return m.group(1).split('::')[-1] if m else None


def find_member(cls, key):
    """Header text to search for `key` starting at cls and walking up its bases; returns the variable name or None."""
    c, hops = cls, 0
    while c and hops < 12:
        rel = hdrindex.header_of(c)
        if rel:
            t = open(os.path.join(ROOT, rel), encoding='utf-8', errors='replace').read()
            body = class_body(t, c) or t
            mm = re.search(r'\b(m_)?' + re.escape(key) + r'\s*(?:=[^;]*)?;', body)
            if mm:
                return (mm.group(1) or '') + key
        c, hops = base_of(c), hops + 1
    return None
