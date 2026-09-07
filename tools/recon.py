"""recon.py <mangled-sym> [--hdr path] [--this Class] [--vt _ZTV..] -- one-call function recon: Ghidra + annotated asm + resolved calls/vslots/members."""

import argparse
import os
import re
import struct
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from capstone import CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN, Cs

import config
from pvzelf import Elf
import ghidra as ghidramod

MD = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)
GREY, CYAN, YEL, OFF = '\033[90m', '\033[36m', '\033[33m', '\033[0m'

_DEMANGLE = os.path.join(os.path.dirname(config.GXX), 'aarch64-linux-android-c++filt' +
                         ('.exe' if config.GXX.endswith('.exe') else ''))


def demangle(sym):
    try:
        r = subprocess.run([_DEMANGLE], input=sym, capture_output=True, text=True)
        return r.stdout.strip() or sym
    except OSError:
        return sym


def owner_class(sym):
    m = re.match(r'^_ZN?K?((?:\d+\w+)+?)(\d+)([A-Za-z_]\w*)E', sym)
    if not m:
        return None
    # last length-prefixed component before the method name is the class
    segs = re.findall(r'(\d+)(\w)', m.group(1))
    # crude: take the class as everything the demangler says before ::method
    d = demangle(sym)
    mm = re.match(r'^(?:[\w:]+\s+)?((?:\w+::)*\w+)::~?\w+\(', d)
    if mm:
        return mm.group(1).split('::')[-1]
    return None


def find_header(cls):
    for root, _, files in os.walk(config.HEADERS):
        for f in files:
            if not f.endswith('.h'):
                continue
            p = os.path.join(root, f)
            try:
                txt = open(p, encoding='utf-8', errors='ignore').read()
            except OSError:
                continue
            if re.search(rf'\b(class|struct)\s+{cls}\b\s*[:{{]', txt):
                return os.path.relpath(p, config.HEADERS).replace(os.sep, '/')
    return None


def member_names(cls, hdr):
    """Data-member identifiers declared inside `class/struct <cls> { ... }` (brace-tracked)."""
    txt = open(os.path.join(config.HEADERS, hdr), encoding='utf-8', errors='ignore').read()
    m = re.search(rf'\b(?:class|struct)\s+{cls}\b[^{{;]*{{', txt)
    if not m:
        return []
    i, depth, body = m.end(), 1, []
    while i < len(txt) and depth:
        c = txt[i]
        if c == '{':
            depth += 1
        elif c == '}':
            depth -= 1
        if depth == 1:
            body.append(c)
        i += 1
    body = ''.join(body)
    body = re.sub(r'//.*', '', body)
    body = re.sub(r'/\*.*?\*/', '', body, flags=re.S)
    # drop nested {...} (method bodies, nested types)
    body = re.sub(r'\{[^{}]*\}', ';', body)
    names = []
    for stmt in body.split(';'):
        stmt = re.sub(r'^\s*(?:public|private|protected)\s*:\s*', '', stmt.strip())
        stmt = stmt.strip()
        if not stmt or '(' in stmt or '=' in stmt:      # methods / initialisers: skip
            continue
        if re.match(r'^(typedef|using|friend|enum|virtual|struct|class|template)\b', stmt):
            continue
        stmt = re.sub(r'^\s*(?:mutable|static)\s+', '', stmt)
        mm = re.search(r'\b([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*$', stmt)
        if mm and mm.group(1) not in names:
            names.append(mm.group(1))
    return names


def base_classes(cls, hdr):
    txt = open(os.path.join(config.HEADERS, hdr), encoding='utf-8', errors='ignore').read()
    m = re.search(rf'\b(?:class|struct)\s+{cls}\b\s*:\s*([^{{]+)\{{', txt)
    if not m:
        return []
    return [b.split('::')[-1].strip()
            for b in re.findall(r'(?:public|protected|private|virtual)\s+([\w:]+)', m.group(1))]


def all_member_names(cls, hdr, _seen=None):
    """Member identifiers of cls plus every visible base, in base-first order."""
    _seen = _seen or set()
    if cls in _seen or not hdr:
        return []
    _seen.add(cls)
    out = []
    for b in base_classes(cls, hdr):
        out += all_member_names(b, find_header(b), _seen)
    for n in member_names(cls, hdr):
        if n not in out:
            out.append(n)
    return out


def offset_map(cls, hdr, _seen=None):
    """{offset: member_name} for cls and its visible bases, probed against cls."""
    if not hdr:
        hdr = find_header(cls)
    if not hdr:
        return {}, None
    merged = {}
    names = all_member_names(cls, hdr)
    src = os.path.join(config.BUILD, 'recon_off.cpp')
    os.makedirs(config.BUILD, exist_ok=True)
    for _ in range(4):
        if not names:
            return {}, hdr
        lines = ['#define private public', '#define protected public',
                 f'#include "{hdr}"', '#include <cstddef>',
                 'using namespace Sexy;', 'namespace { }',
                 'template<unsigned long N> struct P_;']
        base = cls.split('::')[-1]
        for i, n in enumerate(names):
            lines.append(f'P_<offsetof({base}, {n})> p_{i};')
        open(src, 'w').write('\n'.join(lines) + '\n')
        r = subprocess.run([config.GXX, *config.CXXFLAGS, '-fsyntax-only', '-w', src],
                           capture_output=True, text=True)
        out, ok_idx, err_idx = {}, set(), set()
        for l in r.stderr.splitlines():
            m = re.search(r'P_<(\d+)(?:ul|UL)?>[^\n]*?\bp_(\d+)\b', l)
            if m:
                off, idx = int(m.group(1)), int(m.group(2))
                if idx < len(names):
                    out.setdefault(off, names[idx])
                    ok_idx.add(idx)
                continue
            m = re.search(r'\bp_(\d+)\b', l)
            if m and 'error:' in l:
                err_idx.add(int(m.group(1)))
        real_bad = err_idx - ok_idx
        if not real_bad:
            merged.update(out)
            return merged, hdr
        names = [n for i, n in enumerate(names) if i not in real_bad]
    merged.update(out)
    return merged, hdr


def load_names(elf):
    names = {}
    for n, v, s, sh, t in elf.symbols():
        if sh and t in (1, 2):
            names.setdefault(v, n)
    return names


def vtable_rows(elf, table, names):
    for n, v, s, sh, t in elf.symbols():
        if n == table and sh:
            rows = {}
            for off in range(16, s, 8):
                raw = elf.read_at(v + off, 8)
                if not raw:
                    break
                p = int.from_bytes(raw, 'little')
                rows[off - 16] = names.get(p, hex(p))   # call offset -> name
            return rows
    return {}


def clone_body(elf, addr, names, got=None):
    raw = elf.read_at(addr, 40)
    if not raw:
        return None
    parts, pages = [], {}
    for ins in MD.disasm(raw, addr):
        m, o = ins.mnemonic, ins.op_str
        if m == 'adrp':
            r, v = [x.strip() for x in o.split(',')]
            pages[r] = int(v.lstrip('#'), 0)
        if m in ('b', 'bl'):
            t = int(o.lstrip('#'), 0)
            parts.append(f'-> {names.get(t, hex(t))}')
            break
        if m == 'ldr' and got and '[' in o:
            inner = o[o.index('[') + 1:o.rindex(']')]
            p = [x.strip() for x in inner.split(',')]
            if p[0] in pages and len(p) > 1 and p[1].startswith('#'):
                tgt = pages[p[0]] + int(p[1][1:], 0)
                if tgt in got:
                    parts.append(f'{m} [GOT {got[tgt]}]')
                    continue
        parts.append(f'{m} {o}')
        if m in ('ret', 'br') or len(parts) >= 5:
            break
    return '; '.join(parts)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('symbol')
    ap.add_argument('--hdr', help='header (under include/) for member naming')
    ap.add_argument('--this', help='class for member naming (default: inferred)')
    ap.add_argument('--vt', action='append', default=[],
                    help='_ZTV.. table(s) to resolve virtual-call slots against')
    ap.add_argument('--no-ghidra', action='store_true')
    ap.add_argument('--asm-only', action='store_true')
    args = ap.parse_args()

    elf = Elf(config.TARGET_LIB)
    names = load_names(elf)
    try:
        got = {a: r[0] for a, r in elf.relocations('.plt').items()}
    except Exception:
        got = {}

    cls = args.this or owner_class(args.symbol)
    members, hdr = ({}, args.hdr)
    if cls:
        members, hdr = offset_map(cls, args.hdr)

    # vtables: explicit --vt, plus the owner class's own _ZTV if present
    vts = list(args.vt)
    if cls:
        for cand in (f'_ZTVN4Sexy{len(cls)}{cls}E', f'_ZTV{len(cls)}{cls}'):
            if cand not in vts and any(n == cand for n, *_ in elf.symbols()):
                vts.append(cand)
    vrows = {}
    for t in vts:
        vrows[t] = vtable_rows(elf, t, names)

    found = elf.function(args.symbol)
    if found is None:
        print(f'{args.symbol}: not found'); return
    addr, size, code = found

    print(f'=== {args.symbol}')
    print(f'    {demangle(args.symbol)}')
    print(f'    {size} B @ {addr:#x}   class={cls}  hdr={hdr}  vt={",".join(vts) or "-"}')

    if not args.no_ghidra and not args.asm_only:
        print('\n--- GHIDRA ---')
        try:
            dump = ghidramod.decompile(f'{addr:x}')
            body = re.sub(r'^.*?// =====', '// =====', dump, count=1, flags=re.S)
            body = re.split(r'\n// ===== ', body)[0]
            print(body.strip()[:6000] or dump.strip()[-4000:])
        except SystemExit as e:
            print(f'(ghidra: {e})')

    print('\n--- ASM ---')
    pages, vptr_regs = {}, {}
    calls, vslots, memoff = {}, {}, {}
    for ins in MD.disasm(code, addr):
        m, ops, note = ins.mnemonic, ins.op_str, ''

        if m == 'adrp':
            r, v = [x.strip() for x in ops.split(',')]
            pages[r] = int(v.lstrip('#'), 0)
        elif m == 'add':
            p = [x.strip() for x in ops.split(',')]
            if len(p) == 3 and p[1] in pages and p[2].startswith('#'):
                tgt = pages[p[1]] + int(p[2][1:], 0)
                txt = elf.cstr(tgt)
                if txt and txt.isprintable() and 0 < len(txt) < 70:
                    note = f'   "{txt}"'
                elif tgt in names:
                    note = f'   {names[tgt]}'
        elif m in ('ldr', 'ldrb', 'ldrsw', 'str', 'strb') and '[' in ops:
            dst = ops.split(',')[0].strip()
            inner = ops[ops.index('[') + 1:ops.rindex(']')]
            parts = [x.strip() for x in inner.split(',')]
            base = parts[0]
            off = int(parts[1][1:], 0) if len(parts) > 1 and parts[1].startswith('#') else 0
            if len(parts) == 1 and m == 'ldr':
                vptr_regs[dst] = ('vptr', base)      # xD = *xBase  -> maybe a vtable ptr
            elif base in vptr_regs and m == 'ldr':
                vptr_regs[dst] = ('slot', off)
                for t, rows in vrows.items():
                    if off in rows:
                        note = f'   {YEL}vslot {off:#x} = {rows[off]}{OFF} ({t})'
                        vslots[off] = rows[off]
                        break
                else:
                    note = f'   {YEL}vslot {off:#x}{OFF}'
                    vslots.setdefault(off, '?')
            elif base != 'sp' and base != 'x29' and off:
                if off in members:
                    note = f'   {members[off]}'
                    memoff[off] = members[off]
                elif off >= 0x10:
                    note = f'   +{off:#x}'
                    memoff.setdefault(off, '?')
        elif m == 'ldr' and '#0x' in ops and '[' not in ops:
            reg, imm = [x.strip() for x in ops.split(',', 1)]
            tgt = int(imm.lstrip('#'), 0)
            raw = elf.read_at(tgt, 8)
            if raw:
                if reg[0] == 's':
                    note = f'   = {struct.unpack("<f", raw[:4])[0]}f'
                elif reg[0] == 'd':
                    note = f'   = {struct.unpack("<d", raw)[0]}'
                else:
                    note = f'   = {int.from_bytes(raw, "little"):#x}'
        elif m in ('b', 'bl') and ops.startswith('#'):
            t = int(ops.lstrip('#'), 0)
            if addr <= t < addr + size:
                pass                                  # local branch
            elif t in names:
                note = f'   {names[t]}'
                if m == 'bl':
                    calls[names[t]] = calls.get(names[t], 0) + 1
            else:
                body = clone_body(elf, t, names, got)
                note = f'   {CYAN}[clone]{OFF} {body}' if body else f'   {t:#x}'
                calls[f'{t:#x} [clone] {body}'] = calls.get(f'{t:#x} [clone] {body}', 0) + 1
        elif m in ('mov', 'movz', 'movn') and '#' in ops:
            try:
                v = int(ops.split('#')[1].split(',')[0], 0)
                if 8 < abs(v) < 0x7fffffff:
                    note = f'   {GREY}({v}){OFF}'
            except (ValueError, IndexError):
                pass

        print(f'  {ins.address:#x}  {m:<9s} {ops}{note}')

    print('\n--- REFERENCES ---')
    print('calls  :', ', '.join(f'{k}' + (f' x{v}' if v > 1 else '') for k, v in calls.items()) or '-')
    print('vslots :', ', '.join(f'{o:#x}={n}' for o, n in sorted(vslots.items())) or '-')
    unknown = sorted(o for o, n in memoff.items() if n == '?')
    print('members:', ', '.join(f'{o:#x}={n}' for o, n in sorted(memoff.items()) if n != '?') or '-')
    if unknown:
        print('  unnamed offsets:', ', '.join(hex(o) for o in unknown))


if __name__ == '__main__':
    main()
