#!/usr/bin/env python3
"""Focus on one near-miss (or every near-miss in one file): classify the diff, try the source rewrites that fit it, show the winning change."""

import argparse
import concurrent.futures as cf
import difflib
import itertools
import os
import random
import re
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)

from lib import asmdiff
import config
from lib import fastcc
import permute
import wd
from lib.pvzelf import Elf

_FILT = os.path.join(os.path.dirname(config.GXX), 'aarch64-linux-android-c++filt' +
                     ('.exe' if config.GXX.endswith('.exe') else ''))
SCALAR = r'(?:unsigned\s+int|unsigned|int|float|double|bool|size_t|long|short|char|[A-Z]\w*Flags?|[\w:]+\s*\*)'
DECL = re.compile(rf'^(\s+)((?:const\s+)?)({SCALAR})\s+(\w+)\s*=\s*(.+);\s*$')
WRITE = r'\b{n}\s*(?:[-+*/%|&^]?=(?!=)|\+\+|--)|(?:\+\+|--)\s*{n}\b|(?<![&\w)\]])&\s*{n}\b'


def demangle(syms):
    r = subprocess.run([_FILT], input='\n'.join(syms), capture_output=True, text=True, encoding='utf-8',
                       errors='replace')
    out = (r.stdout or '').splitlines()
    return {s: out[i] if i < len(out) else s for i, s in enumerate(syms)}


def split_args(s):
    depth, out, cur = 0, [], ''
    for c in s:
        depth += c in '(<[' and 1 or (c in ')>]' and -1 or 0)
        if c == ',' and depth == 0:
            out.append(cur)
            cur = ''
        else:
            cur += c
    return [a for a in (out + [cur]) if a.strip() and a.strip() != 'void']


def qual_and_args(dem):
    """'A::B::operator()(int, X*) const' -> ('A::B::operator()', 2)."""
    m = re.match(r'(.*?::(?:operator\s*\(\)|operator[^(]+|~?\w+))\s*\((.*)\)[^)]*$', dem)
    return (m.group(1), len(split_args(m.group(2)))) if m else (None, 0)


def find_defs(text, dem):
    qual, nargs = qual_and_args(dem)
    if not qual:
        return []
    pat = re.compile(rf'^(?:[^\s#/][^\n;]*?\b)?{re.escape(qual).replace(r"\ ", r"\s*")}\s*\(', re.M)
    spans = []
    for m in pat.finditer(text):
        close = wd._body_end(text, m.end() - 1)
        body_start = text.find('{', m.end())
        if body_start < 0 or body_start > close:
            continue
        spans.append((m.start(), close, len(split_args(text[m.end():text.rfind(')', m.end(), body_start)]))))
    exact = [(a, b) for a, b, n in spans if n == nargs]
    return exact or [(a, b) for a, b, _ in spans]


# --- recipes: fn text -> list of variants ---------------------------------

def body_lines(fn):
    return fn.split('\n')


def written_after(lines, k, name):
    rx = re.compile(WRITE.format(n=re.escape(name)))
    return any(rx.search(l) for l in lines[k + 1:])


def r_const(fn):
    lines = body_lines(fn)
    cand = []
    for k, l in enumerate(lines):
        m = DECL.match(l)
        if m and not m.group(2) and not written_after(lines, k, m.group(4)) and '*' not in m.group(3):
            cand.append(k)
    out = []

    def apply(ks):
        ls = list(lines)
        for k in ks:
            m = DECL.match(ls[k])
            ls[k] = f'{m.group(1)}const {m.group(3)} {m.group(4)} = {m.group(5)};'
        return '\n'.join(ls)
    for k in cand:
        out.append(apply([k]))
    if len(cand) > 1:
        out.append(apply(cand))
    if 2 < len(cand) <= 6:
        out += [apply(p) for p in itertools.combinations(cand, 2)]
    for k, l in enumerate(lines):
        m = DECL.match(l)
        if m and m.group(2):
            ls = list(lines)
            ls[k] = f'{m.group(1)}{m.group(3)} {m.group(4)} = {m.group(5)};'
            out.append('\n'.join(ls))
    return out


def r_andor(fn):
    m = permute.mask(fn)
    out = []
    for x in re.finditer(r'(&&|\|\|)', m):
        i = x.start()
        lo, hi = permute.left_extent(m, i, 'cmp'), permute.right_extent(m, i + 2, 'cmp')
        if lo is None or hi is None:
            continue
        left, right = fn[lo:i].strip(), fn[i + 2:hi].strip()
        if left and right and permute.pure(left) and permute.pure(right):
            out.append(fn[:lo] + f'{right} {x.group(1)} {left}' + fn[hi:])
    return out


def r_inline_bool(fn):
    lines = body_lines(fn)
    out = []
    for k, l in enumerate(lines):
        m = re.match(r'^\s+(?:const\s+)?bool\s+(\w+)\s*=\s*(.+);\s*$', l)
        if not m or not permute.pure(m.group(2)) or written_after(lines, k, m.group(1)):
            continue
        name, expr = m.group(1), m.group(2).strip()
        alts = {expr}
        x = re.fullmatch(r'(\w+)\s*\^\s*(\w+)', expr) or re.fullmatch(r'(\w+)\s*!=\s*(\w+)', expr)
        if x:
            alts |= {f'{x.group(1)} != {x.group(2)}', f'{x.group(1)} ^ {x.group(2)}'}
        for a in alts:
            sub = a if re.fullmatch(r'[\w.>-]+', a) else f'({a})'
            rest = [re.sub(rf'(?<![\w.>]){name}\b', sub, t) for t in lines[k + 1:]]
            body = '\n'.join(lines[:k] + rest)
            # unwrap parens when the bool was the whole condition or one operand of && / ||
            body = re.sub(r'if \(\(([^()]*)\)\)', r'if (\1)', body)
            body = re.sub(r'(&&|\|\|) \(([^()&|]*)\)\)', r'\1 \2)', body)
            body = re.sub(r'\(\(([^()&|]*)\) (&&|\|\|)', r'(\1 \2', body)
            out.append(body)
    return out


_MEMBER_TYPES = {}


def member_type(name):
    if name not in _MEMBER_TYPES:
        _MEMBER_TYPES[name] = None
        rx = re.compile(rf'^\s*([\w:<>]+(?:\s*\*)?)\s+{re.escape(name)}\s*(?:;|=)', re.M)
        inc = os.path.join(HERE, os.pardir, 'include')
        r = subprocess.run(['git', 'grep', '-n', '--no-index', '-w', name, '--', inc], capture_output=True, text=True,
                           cwd=inc) if os.path.isdir(inc) else None
        for line in (r.stdout.splitlines() if r else []):
            m = rx.search(line.split(':', 2)[-1])
            if m and m.group(1) not in ('return', 'const'):
                _MEMBER_TYPES[name] = m.group(1)
                break
    return _MEMBER_TYPES[name]


def r_member_local(fn):
    lines = body_lines(fn)
    reads = {}
    for k, l in enumerate(lines[2:], 2):
        for x in re.finditer(r'(?<![\w.>])(m_\w+)\b(?!\s*(?:\(|\.|->|\[|[-+*/|&^]?=(?!=)))', l):
            reads.setdefault(x.group(1), []).append(k)
    out = []

    def apply(names):
        ls = list(lines)
        first = stmt_start(ls, min(reads[n][0] for n in names))
        ind = re.match(r'^(\s*)', ls[first]).group(1)
        decls = []
        if not all(member_type(n) for n in names):
            return None
        for n in names:
            local = n[2].lower() + n[3:] if len(n) > 3 else n[2:]
            if re.search(rf'\b{local}\b', fn):
                local += 'Value'
            decls.append(f'{ind}{member_type(n)} {local} = {n};')
            for k in reads[n]:
                ls[k] = re.sub(rf'(?<![\w.>]){n}\b(?!\s*(?:\(|\.|->|\[))', local, ls[k])
        return '\n'.join(ls[:first] + decls + ls[first:])
    for n in reads:
        out.append(apply([n]))
    same_line = {tuple(sorted(n for n in reads if k in reads[n])) for ns in reads.values() for k in ns}
    for g in same_line:
        if len(g) > 1:
            out.append(apply(list(g)))
    return [o for o in out if o]


def r_ternary(fn):
    lines = body_lines(fn)
    out = []
    for k, l in enumerate(lines):
        m = re.match(r'^(\s+)((?:const\s+)?[\w:]+\s*\*?)\s+(\w+)\s*=\s*([^?;]+?)\s*\?\s*([^:;]+?)\s*:\s*([^;]+);\s*$', l)
        if not m:
            continue
        ind, ty, n, c, a, b = m.groups()
        ty = ty.replace('const ', '')
        out.append('\n'.join(lines[:k] + [f'{ind}{ty} {n};', f'{ind}if ({c})', f'{ind}\t{n} = {a};', f'{ind}else',
                                          f'{ind}\t{n} = {b};'] + lines[k + 1:]))
        out.append('\n'.join(lines[:k] + [f'{ind}{ty} {n} = {b};', f'{ind}if ({c})', f'{ind}\t{n} = {a};'] + lines[k + 1:]))
    return out


def r_types(fn):
    out = []
    for a, b in (('int', 'size_t'), ('size_t', 'int'), ('int', 'unsigned int')):
        for x in re.finditer(rf'(?<![\w:]){a}(\s+\w+\s*=)', fn):
            out.append(fn[:x.start()] + b + fn[x.start() + len(a):])
    return out


def r_mutators(fn, tries=24):
    out = set()
    for mut in set(permute.MUTATORS):
        for seed in range(tries):
            r = mut(fn, random.Random(seed))
            if r and r != fn:
                out.add(r)
    return list(out)


def stmt_start(lines, k):
    while k > 2 and lines[k - 1].strip() and not lines[k - 1].rstrip().endswith((';', '{', '}')):
        k -= 1
    return k


INV = {'==': '!=', '!=': '==', '<': '>=', '>=': '<', '>': '<=', '<=': '>'}


def paren_end(s, p):
    d = 0
    for k in range(p, len(s)):
        d += s[k] == '('
        d -= s[k] == ')'
        if d == 0:
            return k
    return None


def invert(c):
    c = c.strip()
    m = permute.mask(c)
    if '&&' not in m and '||' not in m and '?' not in m:
        ops = list(re.finditer(r'==|!=|<=|>=|(?<![<-])<(?![<=])|(?<![>-])>(?![>=])', m))
        if len(ops) == 1:
            o = ops[0]
            return f'{c[:o.start()].rstrip()} {INV[o.group()]} {c[o.end():].lstrip()}'
        if re.fullmatch(r'![\w.\->]+(\(\))?', c):
            return c[1:]
        if re.fullmatch(r'[\w.\->]+(\(\))?', c):
            return '!' + c
    return f'!({c})'


def stmt_end(s, j):
    """End of the statement starting at s[j:] (braced block or up to ';'); None for compound heads."""
    k = len(s) - len(s[j:].lstrip())
    if re.match(r'(if|for|while|do|switch|else)\b', s[k:]):
        return None
    return wd._body_end(s, k)


def ifs(s):
    m = permute.mask(s)
    for x in re.finditer(r'\bif\s*\(', m):
        p = x.end() - 1
        q = paren_end(m, p)
        if q:
            yield x.start(), p, q


def unblock(body):
    b = body.strip('\n')
    if b.strip().startswith('{') and b.strip().endswith('}'):
        b = b.strip()[1:-1].strip('\n')
    lines = [l for l in b.split('\n') if l.strip()]
    cut = min(len(l) - len(l.lstrip('\t')) for l in lines) if lines else 0
    return '\n'.join(l[cut:] if l.strip() else l for l in b.split('\n')).strip()


def r_ifelse(fn):
    out = []
    for a, p, q in ifs(fn):
        cond = fn[p + 1:q]
        e1 = stmt_end(fn, q + 1)
        if e1 is None:
            continue
        x = re.compile(r'(\s*)else\b').match(fn, e1)
        if x:
            e2 = stmt_end(fn, x.end())
            if e2 is None:
                continue
            body1, body2 = fn[q + 1:e1], fn[x.end():e2]
            out.append(fn[:a] + f'if ({invert(cond)})' + body2 + x.group(1) + 'else' + body1 + fn[e2:])
            if re.fullmatch(r'\s*\{?\s*return\b[^;]*;\s*\}?\s*', body1):
                ind = x.group(1)
                rest = unblock(body2).replace('\n', ind)
                out.append(fn[:a] + f'if ({cond})' + body1 + ind + rest + fn[e2:])
            continue
        body = fn[q + 1:e1]
        rest = re.compile(r'(\s*)return\b([^;]*);').match(fn, e1)
        if rest and re.fullmatch(r'\s*\{?\s*return\b[^;]*;\s*\}?\s*', body):
            ra, rb = re.search(r'return\b([^;]*);', body).group(1), rest.group(2)
            out.append(fn[:a] + f'if ({invert(cond)})' + body.replace(f'return{ra};', f'return{rb};')
                       + rest.group(1) + f'return{ra};' + fn[rest.end():])
            out.append(fn[:a] + f'if ({invert(cond)})' + body.replace(f'return{ra};', f'return{rb};')
                       + rest.group(1) + 'else' + body + fn[rest.end():])
            if {ra.strip(), rb.strip()} == {'true', 'false'}:
                c = cond.strip() if ra.strip() == 'true' else invert(cond)
                out.append(fn[:a] + f'return {c};' + fn[rest.end():])
    return out


def r_ternary_flip(fn):
    out = []
    m = permute.mask(fn)
    for x in re.finditer(r'(?:=|return)\s+([^=;?{}]+?)\s*\?\s*([^:;?{}]+?)\s*:\s*([^;?{}]+);', m):
        c, a, b = (fn[x.start(i):x.end(i)] for i in (1, 2, 3))
        if c.count('(') == c.count(')'):
            out.append(fn[:x.start(1)] + f'{invert(c)} ? {b} : {a}' + fn[x.end(3):])
    return out


def r_expect(fn):
    out = []
    for a, p, q in ifs(fn):
        c = fn[p + 1:q]
        if '__builtin_expect' not in c:
            out += [fn[:p + 1] + f'__builtin_expect(!!({c}), {v})' + fn[q:] for v in ('0', '1')]
    return out


def r_null(fn):
    out = []
    m = permute.mask(fn)
    for x in re.finditer(r'([A-Za-z_][\w.\->]*)\s*(!=|==)\s*(NULL|nullptr)\b', m):
        e = fn[x.start(1):x.end(1)]
        out.append(fn[:x.start()] + (e if x.group(2) == '!=' else f'!{e}') + fn[x.end():])
    for a, p, q in ifs(fn):
        c = fn[p + 1:q].strip()
        if re.fullmatch(r'!?[A-Za-z_][\w.\->]*', c) and re.search(r'(Ptr|ptr|entity|Entity|[a-z][A-Z]\w*$)', c):
            out.append(fn[:p + 1] + (f'{c[1:]} == NULL' if c.startswith('!') else f'{c} != NULL') + fn[q:])
    return out


def r_for_while(fn):
    out = []
    m = permute.mask(fn)
    for x in re.finditer(r'\bfor\s*\(', m):
        p = x.end() - 1
        q = paren_end(m, p)
        if not q:
            continue
        head = fn[p + 1:q]
        parts = head.split(';')
        b = re.compile(r'(\s*)\{').match(fn, q + 1)
        if len(parts) != 3 or not b:
            continue
        be = wd._body_end(fn, b.end() - 1)
        if 'continue' in fn[b.end():be]:
            continue
        init, cond, step = (s.strip() for s in parts)
        ind = fn[:x.start()].rsplit('\n', 1)[-1]
        body = fn[b.end():be - 1].rstrip()
        new = (f'{init};\n{ind}' if init else '') + f'while ({cond or "true"})' + b.group(1) + '{' + body \
            + (f'\n{ind}\t{step};' if step else '') + f'\n{ind}}}'
        out.append(fn[:x.start()] + new + fn[be:])
    return out


def r_split_decl(fn):
    lines = body_lines(fn)
    out = []
    for k, l in enumerate(lines):
        m = DECL.match(l)
        if m and not m.group(2):
            out.append('\n'.join(lines[:k] + [f'{m.group(1)}{m.group(3)} {m.group(4)};',
                                              f'{m.group(1)}{m.group(4)} = {m.group(5)};'] + lines[k + 1:]))
    return out


def params(fn):
    head = fn[:fn.index('{')]
    p = head.index('(')
    res = []
    for a in split_args(head[p + 1:paren_end(head, p)]):
        m = re.fullmatch(rf'\s*((?:const\s+)?{SCALAR})\s*(\w+)\s*', a.split('=')[0])
        if m:
            res.append((m.group(1).replace('const ', ''), m.group(2)))
    return res


def r_param_local(fn):
    out = []
    try:
        ps = params(fn)
    except (ValueError, TypeError):
        return out
    open_at = fn.index('{') + 1
    body = fn[open_at:]
    for ty, n in ps:
        if not re.search(rf'(?<![\w.>]){n}\b', body):
            continue
        local = re.sub(r'^[io]_', '', n)
        if local == n or re.search(rf'\b{local}\b', fn):
            local += 'Value'
        new_body = re.sub(rf'(?<![\w.>]){n}\b', local, body)
        out += [fn[:open_at] + f'\n\t{c}{ty} {local} = {n};' + new_body for c in ('const ', '')]
    return out


def r_switch(fn):
    out = []
    for a, p, q in ifs(fn):
        if re.search(r'else\s*$', fn[:a]):
            continue
        arms, pos, var, default = [], a, None, None
        while True:
            m = re.compile(r'if\s*\(\s*([\w.\->]+(?:\(\))?)\s*==\s*([\w:]+)\s*\)').match(fn, pos)
            if not m or (var and m.group(1) != var):
                break
            var = m.group(1)
            e = stmt_end(fn, m.end())
            if e is None:
                break
            arms.append((m.group(2), fn[m.end():e]))
            pos = e
            x = re.compile(r'\s*else\b').match(fn, pos)
            if not x:
                break
            nxt = x.end() + len(fn[x.end():]) - len(fn[x.end():].lstrip())
            if fn.startswith('if', nxt) and re.match(r'if\b', fn[nxt:]):
                pos = nxt
                continue
            e = stmt_end(fn, x.end())
            if e is None:
                arms = []
                break
            default, pos = fn[x.end():e], e
            break
        if len(arms) < 2:
            continue
        ind = fn[:a].rsplit('\n', 1)[-1]

        def case(body):
            b = unblock(body)
            lines = [f'{ind}\t{l}' if l.strip() else l for l in b.split('\n')]
            tail = '' if re.search(r'\b(return|break)\b[^;]*;\s*$', b) else f'\n{ind}\tbreak;'
            return '\n'.join(lines) + tail
        for order in (arms, arms[::-1]):
            s = f'switch ({var})\n{ind}{{\n'
            for k, body in order:
                s += f'{ind}case {k}:\n{case(body)}\n'
            if default is not None:
                s += f'{ind}default:\n{case(default)}\n'
            out.append(fn[:a] + s + f'{ind}}}' + fn[pos:])
    return out


def r_loop_bound(fn):
    out = []
    lines = body_lines(fn)
    for k, l in enumerate(lines):
        m = re.match(r'^\s*(?:const\s+)?(?:size_t|int|unsigned\s+int|unsigned)\s+(\w+)\s*=\s*([\w.\->]+(?:\(\))?\s*(?:\.|->)\s*size\(\))\s*;\s*$', l)
        if not m:
            continue
        n, expr = m.groups()
        rest = '\n'.join(lines[k + 1:])
        uses = list(re.finditer(rf'(?<![\w.>]){n}\b', rest))
        if uses and all(re.match(r'\s*(?:for\s*\([^;]*;|while\s*\()', rest[:u.start()].rsplit('\n', 1)[-1]) for u in uses):
            out.append('\n'.join(lines[:k]) + '\n' + re.sub(rf'(?<![\w.>]){n}\b', expr, rest))
    m = permute.mask(fn)
    for x in re.finditer(r'\bfor\s*\(\s*(size_t|int|unsigned\s+int)\s+(\w+)\s*=\s*0\s*;\s*\2\s*(<|!=)\s*([\w.\->]+(?:\(\))?\s*(?:\.|->)\s*size\(\))\s*;', m):
        ty, i, op, expr = (fn[x.start(g):x.end(g)] for g in (1, 2, 3, 4))
        ind = fn[:x.start()].rsplit('\n', 1)[-1]
        alt = '!=' if op == '<' else '<'
        out.append(fn[:x.start(3)] + alt + fn[x.end(3):])
        out.append(fn[:x.start()] + f'{ty} n = {expr};\n{ind}' + fn[x.start():x.start(4)] + 'n' + fn[x.end(4):])
    return out


def r_back(fn):
    out = []
    m = permute.mask(fn)
    for x in re.finditer(r'([\w.\->]+(?:\(\))?)\s*(\.|->)\s*(back|front)\(\)', m):
        e, dot, which = (fn[x.start(g):x.end(g)] for g in (1, 2, 3))
        obj = e if dot == '.' else f'(*{e})'
        idx = f'{e}{dot}size() - 1' if which == 'back' else '0'
        out.append(fn[:x.start()] + f'{obj}[{idx}]' + fn[x.end():])
    for x in re.finditer(r'([\w.]+)\[\s*\1\s*\.\s*size\(\)\s*-\s*1\s*\]', m):
        out.append(fn[:x.start()] + f'{fn[x.start(1):x.end(1)]}.back()' + fn[x.end():])
    return out


def r_single_exit(fn):
    m = permute.mask(fn)
    rets = list(re.finditer(r'\breturn\b\s*([^;]*);', m))
    if len(rets) < 2:
        return []
    last = rets[-1]
    val = fn[last.start(1):last.end(1)].strip()
    if not val or fn[last.end():].strip() != '}' or 'done:' in fn:
        return []
    early = [r for r in rets[:-1] if fn[r.start(1):r.end(1)].strip() == val]
    if not early:
        return []
    head, ind = fn[:last.start()].rsplit('\n', 1)
    s = f'{head}\ndone:\n{ind}' + fn[last.start():]
    for r in reversed(early):
        s = s[:r.start()] + 'goto done;' + s[r.end():]
    return [s]


def r_delegate(fn):
    out = []
    for x in re.finditer(r'MakeDelegate\(\s*(\*?)this\s*,', fn):
        out.append(fn[:x.start()] + ('MakeDelegate(this,' if x.group(1) else 'MakeDelegate(*this,') + fn[x.end():])
    return out


RECIPES = [r_const, r_andor, r_inline_bool, r_member_local, r_ternary, r_types, r_ifelse, r_ternary_flip, r_switch,
           r_for_while, r_split_decl, r_param_local, r_null, r_expect, r_loop_bound, r_back, r_single_exit,
           r_delegate, r_mutators]


REG = re.compile(r'\b[xwsdqv](\d+|zr)\b')
BRANCH = re.compile(r'^(b\.\w+|b|cbz|cbnz|tbz|tbnz)$')

# recipes most likely to move each kind of diff, tried first
FIRST = {
    'regs': [r_const, r_param_local, r_member_local, r_types, r_loop_bound, r_split_decl, r_inline_bool, r_expect],
    'branch': [r_expect, r_ifelse, r_single_exit, r_andor, r_ternary_flip, r_switch, r_null],
    'sched': [r_const, r_split_decl, r_member_local, r_param_local, r_inline_bool, r_andor],
    'const': [r_types, r_ternary_flip, r_ifelse],
    'call': [r_delegate, r_back],
    'count': [r_types, r_loop_bound, r_back, r_single_exit, r_ifelse, r_switch, r_ternary, r_inline_bool,
              r_for_while, r_andor, r_ternary_flip],
    'mixed': [r_const, r_andor, r_expect, r_single_exit, r_loop_bound, r_back, r_delegate, r_ifelse, r_inline_bool,
              r_member_local, r_types, r_ternary_flip],
}


def classify(g, o):
    """count (insns missing/extra), regs, branch, call (callee names only), sched (same insns, other order), const, mixed."""
    if len(g) != len(o):
        return 'count'
    diff = [(a, b) for a, b in zip(g, o) if not asmdiff._same(asmdiff.render([a])[0], asmdiff.render([b])[0])]
    if not diff:
        return 'ok'
    if any(a[0] != b[0] for a, b in diff):
        if all(BRANCH.match(a[0]) and BRANCH.match(b[0]) for a, b in diff):
            return 'branch'
        if sorted(m for m, _ in g) == sorted(m for m, _ in o):
            return 'sched'
        return 'mixed'
    kinds = set()
    for (m, a), (_, b) in diff:
        if REG.sub('R', a) == REG.sub('R', b):
            kinds.add('regs')
        elif BRANCH.match(m):
            kinds.add('branch')
        elif m in ('bl', 'b') or '<' in a:
            kinds.add('call')
        else:
            kinds.add('const')
    return kinds.pop() if len(kinds) == 1 else 'mixed'


def children(fn, recipes):
    seen, out = {fn}, []
    for r in recipes:
        for c in r(fn):
            if c not in seen:
                seen.add(c)
                out.append((r.__name__[2:], c))
    return out


def evaluate(job):
    try:
        return permute.evaluate(job)
    except Exception:
        return None


def src_diff(a, b):
    d = difflib.unified_diff(a.split('\n'), b.split('\n'), n=0, lineterm='')
    return '\n'.join('      ' + l for l in d if not l.startswith(('---', '+++', '@@')))


def focus(source, mangled, dem, args, ex):
    """Search one function; -> new file text when it reached OK (or a gain with --keep-gains), else None."""
    t0 = time.time()
    text = open(source, encoding='utf-8', newline='').read()
    enc = (lambda t: t.replace('\n', '\r\n')) if '\r\n' in text else (lambda t: t)
    defs = find_defs(text, dem)
    if not defs:
        print('    definition not found in this file')
        return None
    elf = Elf(config.TARGET_LIB)
    game = asmdiff.listing(elf, mangled)
    src_dir, stem = os.path.dirname(source), os.path.splitext(os.path.basename(source))[0]
    build_dir = os.path.join(config.BUILD, 'nm')
    os.makedirs(build_dir, exist_ok=True)
    rng = random.Random(args.seed)
    deadline = t0 + args.minutes * 60
    found = None
    for a, b in defs:
        orig = text[a:b].replace('\r\n', '\n')

        def job(tag, fn):
            return (src_dir, stem, tag, text[:a] + enc(fn) + text[b:], mangled, build_dir)
        ours = evaluate(job('base', orig))
        base = permute.rank(game, ours)
        kind = classify(game, ours) if ours else 'count'
        print(f'    {base[0]}/{len(game)}, kind: {kind}', flush=True)
        if kind == 'call' and not children(orig, FIRST['call']):
            print('    only callee names differ (linker folding / lambda symbols): no source rewrite changes that')
            return None
        first = FIRST.get(kind, RECIPES)
        beam, best, trail, stale = [(base, orig, [])], (base, orig, []), {orig}, 0
        for rnd in range(args.rounds):
            if time.time() > deadline:
                print('    time budget used')
                break
            # round 1: only the recipes for this kind; later rounds: everything, mutators to fill the cap
            recipes = first if rnd == 0 else RECIPES
            kids = []
            for _, fn, path in beam:
                kids += [(n, c, path) for n, c in children(fn, recipes) if c not in trail]
            trail |= {c for _, c, _ in kids}
            fixed = [k for k in kids if k[0] != 'mutators']
            rest = [k for k in kids if k[0] == 'mutators']
            if len(fixed) > args.cap:
                fixed = rng.sample(fixed, args.cap)
            room = max(args.cap - len(fixed), 0)
            kids = fixed + (rng.sample(rest, room) if len(rest) > room else rest)
            if not kids:
                break
            res = list(ex.map(evaluate, [job(f'{rnd}_{i}', c) for i, (_, c, _) in enumerate(kids)]))
            scored = sorted(((permute.rank(game, r), c, p + [n]) for (n, c, p), r in zip(kids, res)),
                            key=lambda x: x[0], reverse=True)
            top = scored[0][0][0] if scored else '-'
            print(f'    round {rnd + 1}: {len(kids)} variants, best {top}/{len(game)}  ({time.time() - t0:.0f} s)', flush=True)
            if scored and scored[0][0] > best[0]:
                best, stale = scored[0], 0
            else:
                stale += 1
            if best[0] == (len(game), 0) or stale >= 2:
                break
            beam = scored[:args.beam] if scored and scored[0][0] >= beam[0][0] else beam
        if best[0] > base and (found is None or best[0] > found[0]):
            found = (best[0], best[1], best[2], a, b, base, orig)
    if not found:
        print(f'    no gain  ({time.time() - t0:.0f} s)')
        return None
    sc, fn, path, a, b, base, orig = found
    ok = sc == (len(game), 0)
    out = os.path.join(build_dir, f'{mangled[:80]}.best.cpp')
    open(out, 'w', encoding='utf-8', newline='').write(fn)
    print(f'    {"OK" if ok else f"{sc[0]}/{len(game)}"} (was {base[0]}) via {" + ".join(path)}  ({time.time() - t0:.0f} s)')
    print(src_diff(orig, fn))
    if args.apply and (ok or args.keep_gains):
        return text[:a] + enc(fn) + text[b:]
    if not ok:
        print(f'    best source -> {os.path.relpath(out, ROOT)}')
    return None


def file_scores(source):
    obj, _ = fastcc.compile_file(source, pch=True)
    if obj is None:
        return None
    game, ours = Elf(config.TARGET_LIB), Elf(obj)
    res = {}
    for n, v, s, sh, t in ours.symbols():
        if sh and t == 2 and s and not n.startswith('_ZTV'):
            g = asmdiff.listing(game, n)
            if g is not None:
                res[n] = (permute.rank(g, asmdiff.listing(ours, n)), len(g))
    return res


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('target', nargs='+', help='<Class> <method> | <mangled> | <file.cpp> [pattern...]')
    ap.add_argument('--apply', action='store_true', help='write an OK into the source (reverted if another function drops)')
    ap.add_argument('--keep-gains', action='store_true', help='with --apply, also write a partial gain')
    ap.add_argument('--minutes', type=float, default=3, help='budget per function')
    ap.add_argument('--rounds', type=int, default=4)
    ap.add_argument('--beam', type=int, default=3)
    ap.add_argument('--cap', type=int, default=120, help='max variants compiled per round')
    ap.add_argument('--jobs', type=int, default=12)
    ap.add_argument('--seed', type=int, default=0)
    args = ap.parse_args()
    t = args.target
    if t[0].endswith('.cpp'):
        source, pats = os.path.abspath(t[0]), t[1:]
        before = file_scores(source)
        if before is None:
            sys.exit('compile failed')
        todo = [n for n, (sc, tot) in sorted(before.items(), key=lambda x: x[1][1]) if sc != (tot, 0)]
        todo = [n for n in todo if not pats or any(p in n for p in pats)]
    else:
        mangled, source = wd.resolve(t[0], t[1] if len(t) > 1 else None)
        source, todo, before = os.path.abspath(source), [mangled], None
    dem = demangle(todo)
    text = open(source, encoding='utf-8', newline='').read()
    todo = [n for n in todo if find_defs(text, dem[n])]
    if not todo:
        sys.exit('nothing to do (no written near-miss matched)')
    with cf.ThreadPoolExecutor(args.jobs) as ex:
        for n in todo:
            print(f'  {dem[n]}', flush=True)
            saved = open(source, encoding='utf-8', newline='').read()
            new = focus(source, n, dem[n], args, ex)
            if new is None:
                continue
            before = before or file_scores(source)
            open(source, 'w', encoding='utf-8', newline='').write(new)
            after = file_scores(source) or {}
            lost = [m for m in before if m != n and (m not in after or after[m][0] < before[m][0])]
            if not after or lost:
                open(source, 'w', encoding='utf-8', newline='').write(saved)
                print(f'    reverted: {"compile failed" if not after else "drops " + ", ".join(lost[:3])}')
            else:
                before = after
                print('    applied')


if __name__ == '__main__':
    main()
