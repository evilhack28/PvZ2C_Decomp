"""Vtable checks: vt.py <Class> | diff <Class> [obj] | names <Class> | slot <Class> [0xOFF|method...] | expr [h.h] 'params' 'call'... | fix <Class>... [--chain] (header found automatically, --hdr overrides)."""

import json
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from capstone import CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN, Cs

import config
from lib import fastcc, hdrindex
from lib.pvzelf import Elf

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), os.pardir)
MD = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)


def header_of(cls, hdr=None):
    """Include path (relative to include/) of the header defining cls."""
    rel = hdr or hdrindex.header_of(cls)
    if not rel:
        sys.exit(f'no header defines {cls} -- pass --hdr <path under include/>')
    return re.sub(r'^include/', '', rel)


def _vptr_offset(elf, name):
    """First vptr-relative ldr offset (>= 0x10) in a compiled probe function."""
    found = elf.function(name)
    if not found:
        return None
    addr, size, code = found
    for ins in MD.disasm(code, addr):
        if ins.mnemonic == 'ldr' and '[' in ins.op_str and '#' in ins.op_str:
            hit = re.search(r'#(0x[0-9a-f]+)', ins.op_str)
            if hit and int(hit.group(1), 0) >= 0x10:
                return int(hit.group(1), 0)
    return None


# -- slot: the offset our headers compile each method call to (ICF-proof naming) --

def candidates_from(header):
    """Every no-argument virtual method declared in a header."""
    path = os.path.join(config.HEADERS, header)
    if not os.path.exists(path):
        path = os.path.join(config.HEADERS, 'PvZ', header)
    if not os.path.exists(path):
        for root, _d, files in os.walk(config.HEADERS):
            if os.path.basename(header) in files:
                path = os.path.join(root, os.path.basename(header))
                break
    names = []
    for line in open(path, encoding='utf-8', errors='replace').read().splitlines():
        if 'virtual' not in line:
            continue
        m = re.search(r'\b([A-Za-z_]\w*)\s*\(\s*\)', line)
        if m and m.group(1) not in ('virtual', 'if', 'return'):
            names.append(m.group(1))
    return sorted(set(names))


def probe(cls, header, methods):
    """[(offset, method)] for each no-argument virtual call that compiles."""
    found = fastcc.memo(('vt.probe', cls, header, sorted(methods)), lambda: _probe(cls, header, methods))
    return [tuple(x) for x in found]


def _probe(cls, header, methods):
    src = os.path.join(config.BUILD, 'slotprobe.cpp')
    obj = os.path.join(config.BUILD, 'slotprobe.o')
    good = list(methods)
    # anything that does not compile is dropped and the rest retried
    for _round in range(6):
        text = f'#define private public\n#define protected public\n#include "{header}"\n' + ''.join(
            f'void probe_{i}_{m}({cls}* p) {{ p->{m}(); }}\n' for i, m in enumerate(good))
        ok, err = fastcc.compile_text(src, text, obj)
        if ok:
            break
        bad = {int(m.group(1)) for m in re.finditer(r'probe_(\d+)_', err)}
        if not bad:
            print('probe failed:')
            for line in [l for l in err.splitlines() if ' error: ' in l][:5]:
                print('  ', line[:180])
            return [], None
        good = [m for i, m in enumerate(good) if i not in bad]
    else:
        return [], None
    elf, out = Elf(obj), []
    for n, v, s, sh, t in elf.symbols():
        m = re.search(r'probe_(\d+)_(\w+?)P\d', n) if sh and t == 2 and n.startswith('_Z') else None
        off = m and _vptr_offset(elf, n)
        if off:
            out.append((off, m.group(2)))
    return sorted(set(out)), obj


def cmd_slot(cls, header, rest):
    want = next((int(a, 0) for a in rest if a.startswith('0x')), None)
    methods = [a for a in rest if not a.startswith('0x')] or candidates_from(header)
    for off, name in probe(cls, header, methods):
        if want is None or off == want:
            print(f'  {off:#06x}  {name}')


# -- expr: the offset of a call with arguments --

def cmd_expr(args):
    headers = []
    while args and args[0].endswith('.h'):
        headers.append(args.pop(0))
    pairs = list(zip(args[0::2], args[1::2]))
    if not headers:
        classes = {c for p, _ in pairs for c in re.findall(r'\b([A-Z]\w+)\s*[*&]', p)}
        headers = [header_of(c) for c in sorted(classes) if hdrindex.header_of(c)]
    src = os.path.join(config.BUILD, 'exprprobe.cpp')
    obj = os.path.join(config.BUILD, 'exprprobe.o')
    text = '#define private public\n#define protected public\n' + ''.join(f'#include "{h}"\n' for h in headers) + ''.join(
        f'void probe_{i}({p}) {{ (void)({c}); }}\n' for i, (p, c) in enumerate(pairs))
    ok, err = fastcc.compile_text(src, text, obj)
    if not ok:
        for line in [l for l in err.splitlines() if ' error: ' in l][:8]:
            print('  ', line[:200])
        return
    elf = Elf(obj)
    for n, v, s, sh, t in sorted(elf.symbols()):
        m = re.match(r'_Z7probe_(\d+)', n)
        if sh and t == 2 and m:
            off = _vptr_offset(elf, n)
            print(f'  {f"{off:#06x}" if off is not None else "not virtual"}  {pairs[int(m.group(1))][1]}')


# -- names: our slot numbering vs the game's, anchored on uniquely placed methods --

def game_offsets(elf, cls):
    """{method: vptr-relative offset} for every method of cls placed exactly once in its own vtable."""
    table = f'_ZTV{len(cls)}{cls}'
    found = next(((v, s) for n, v, s, sh, t in elf.symbols() if n == table and sh), None)
    if found is None:
        return None
    addr, size = found
    rows = {}
    for off in range(16, size, 8):
        raw = elf.read_at(addr + off, 8)
        if not raw:
            break
        rows.setdefault(int.from_bytes(raw, 'little'), []).append(off - 16)
    out, tag = {}, f'{len(cls)}{cls}'
    for n, v, s, sh, t in elf.symbols():
        if not (sh and t == 2 and n.startswith('_Z') and tag in n) or len(rows.get(v, [])) != 1:
            continue
        m = re.search(re.escape(tag) + r'(\d+)', n)
        name = m and n[m.end():m.end() + int(m.group(1))]
        if name and len(name) == int(m.group(1)) and re.fullmatch(r'[A-Za-z_]\w*', name):
            out.setdefault(name, rows[v][0])
    return out


def cmd_names(cls, header):
    game = game_offsets(Elf(config.TARGET_LIB), cls)
    if game is None:
        print(f'_ZTV{len(cls)}{cls}: not in the game')
        return
    ours = {name: off for off, name in probe(cls, header, candidates_from(header))}
    both = sorted((game[n], ours[n], n) for n in ours if n in game)
    if not both:
        print(f'{cls}: no method is both probeable and uniquely placed')
        return
    print(f'{cls}: {len(both)} methods anchored in both tables ({header})\n')
    print(f'  {"game":>7}  {"ours":>7}  {"delta":>6}  method')
    run = None
    for g, o, n in both:
        d = g - o
        mark = '' if d == 0 else '  <-'
        if d != run:
            run = d
            mark += f'  gap changes to {d // 8:+d} slot(s)' if d else '  (aligned)'
        print(f'  {g:#07x}  {o:#07x}  {d // 8:+6d}  {n}{mark}')
    bad = [x for x in both if x[0] != x[1]]
    if not bad:
        print('\n  every anchored method agrees')
        return
    first = bad[0]
    prior = [x for x in both if x[0] < first[0] and x[0] == x[1]]
    print(f'\n  {len(bad)} of {len(both)} disagree.')
    print(f'  first divergence: {first[2]} (game {first[0]:#x}, ours {first[1]:#x}, {(first[0] - first[1]) // 8:+d} slots)')
    if prior:
        print(f'  last agreement:   {prior[-1][2]} at {prior[-1][0]:#x}')
        print(f'  the missing declarations belong between {prior[-1][2]} and {first[2]} in {header}')
    else:
        print('  nothing agrees; the gap is above the first virtual')


# -- diff: our emitted vtable vs the game's, slot by slot --

def game_entries(elf, table):
    found = next(((v, s) for n, v, s, sh, t in elf.symbols() if n == table and sh), None)
    if found is None:
        return None
    names = {}
    for n, v, s, sh, t in elf.symbols():
        if sh and t == 2:
            names.setdefault(v, set()).add(n)
    out = []
    for off in range(16, found[1], 8):
        raw = elf.read_at(found[0] + off, 8)
        if not raw:
            break
        e = int.from_bytes(raw, 'little')
        out.append(sorted(names.get(e, {f'{e:#x}'})))
    return out


def our_entries(elf, table):
    found = next(((v, s, sh) for n, v, s, sh, t in elf.symbols() if n == table and sh), None)
    if found is None or not found[1]:
        return None
    addr, size, shndx = found
    relocs = elf.relocations(elf._sh[shndx][-1])
    return [[relocs[addr + off][0]] if addr + off in relocs else ['(null)'] for off in range(16, size, 8)]


def our_object(cls):
    """Object of the unit that defines cls's methods (via units.json), compiled if needed."""
    from lib import fastcc
    units = json.load(open(os.path.join(ROOT, 'units.json'))).get('units', {}) if os.path.exists(os.path.join(ROOT, 'units.json')) else {}
    tag = f'N{len(cls)}{cls}'
    for rel, u in units.items():
        if any(tag in s for s, _ in u.get('funcs', [])) and os.path.exists(os.path.join(ROOT, rel)):
            return fastcc.compile_file(os.path.join(ROOT, rel), pch=True)[0]
    return None


def cmd_diff(cls, header, obj=None):
    table = f'_ZTV{len(cls)}{cls}'
    game = game_entries(Elf(config.TARGET_LIB), table)
    if game is None:
        print(f'{table}: not in the game')
        return
    obj = obj or our_object(cls)
    ours = our_entries(Elf(obj), table) if obj else None
    if ours is None:
        print(f'{table}: not emitted by {obj and os.path.basename(obj) or "any unit"}; comparing by name instead\n')
        return cmd_names(cls, header)
    print(f'{table}: game {len(game)} slots, ours {len(ours)} slots ({len(game) - len(ours):+d})\n')
    shown = 0
    for i in range(max(len(game), len(ours))):
        g = game[i] if i < len(game) else None
        o = ours[i] if i < len(ours) else None
        if g and o and set(g) & set(o):
            continue
        print(f'  slot {i:3d} (+{16 + i * 8:#05x})')
        print(f'     game | {"|".join(g)[:56] if g else "(past end)"}')
        print(f'     ours | {"|".join(o)[:56] if o else "(past end)"}')
        shown += 1
        if shown >= 20:
            print('  ...')
            break
    if not shown:
        print('  every slot agrees')


# -- fix: pad a header until its vtable slots and instance size agree with the game --

def _read(p):
    return open(p, encoding='utf-8', errors='replace', newline='').read()


def _write(p, t):
    open(p, 'w', encoding='utf-8', newline='').write(t)


def first_gap(cls, header):
    """(method, slots_missing) for the first anchored method whose slot disagrees, or None."""
    game = game_offsets(Elf(config.TARGET_LIB), cls)
    if game is None:
        return None
    ours = {n: o for o, n in probe(cls, header, candidates_from(header))}
    for g, o, n in sorted((game[n], ours[n], n) for n in ours if n in game):
        if g != o:
            return n, (g - o) // 8
    return None


def add_placeholders(path, cls, method, k):
    text = _read(path)
    nl = '\r\n' if '\r\n' in text else '\n'
    m = re.search(r'^[ \t]*virtual[^\n;{]*\b' + re.escape(method) + r'\s*\(', text, re.M) \
        or re.search(r'^[ \t]*[^\n;{]*\b' + re.escape(method) + r'\s*\(', text, re.M)
    if not m:
        return False
    base = len(re.findall(r'reserved_%s_\d+' % cls, text))
    add = nl.join('\tvirtual void reserved_%s_%d() {}' % (cls, base + i) for i in range(k)) + nl
    _write(path, text[:m.start()] + add + text[m.start():])
    return True


def game_size(cls):
    f = Elf(config.TARGET_LIB).function('_ZN%d%s9StaticNewEv' % (len(cls), cls))
    for i in MD.disasm(f[2], f[0]) if f else []:
        if i.mnemonic == 'mov' and i.op_str.startswith('x0, #'):
            return int(i.op_str.split('#')[1], 0)
    return None


def our_size(cls, header):
    path = os.path.join(config.BUILD, 'vtfix_%d.cpp' % os.getpid())
    _write(path, '#include "SexyAppFramework/Common.h"\n#include "%s"\ntemplate<int N> struct Show;\nShow<(int)sizeof(%s)> s;\n' % (header, cls))
    r = subprocess.run([config.GXX, *config.CXXFLAGS, '-w', '-fsyntax-only', path], capture_output=True, text=True)
    os.remove(path)
    m = re.search(r'Show<(\d+)> s', r.stderr)
    return int(m.group(1)) if m else None


def add_padding(path, cls, delta):
    text = _read(path)
    m = re.search(r'^\s*(?:class|struct)\s+(?:\w+\s+)?' + re.escape(cls) + r'\s*(?:final\s*)?(?::[^;{]*)?\{', text, re.M)
    if not m:
        return False
    depth = 0
    for j in range(m.end() - 1, len(text)):
        depth += {'{': 1, '}': -1}.get(text[j], 0)
        if text[j] == '}' and depth == 0:
            nl = '\r\n' if '\r\n' in text else '\n'
            _write(path, text[:j] + 'private:%s\tchar m_unknownTail[%d];%s' % (nl, delta, nl) + text[j:])
            return True
    return False


def fix(cls):
    rel = hdrindex.header_of(cls)
    if not rel:
        return '%s: no header' % cls
    path, header = os.path.join(ROOT, rel), header_of(cls)
    notes = []
    for _ in range(5):
        gap = first_gap(cls, header)
        if not gap:
            break
        n, k = gap
        if k <= 0 or not add_placeholders(path, cls, n, k):
            notes.append('unfixable gap at %s (%+d)' % (n, k))
            break
        notes.append('%+d slots before %s' % (k, n))
    g, o = game_size(cls), our_size(cls, header)
    if g and o and g > o and add_padding(path, cls, g - o):
        notes.append('size +%d' % (g - o))
    elif g and o and g < o:
        notes.append('ours %d larger than game' % (o - g))
    return '%s: %s' % (cls, '; '.join(notes) or 'already agrees')


def base_of(cls):
    rel = hdrindex.header_of(cls)
    m = rel and re.search(r'(?:class|struct)\s+' + re.escape(cls) + r'\s*(?:final\s*)?:\s*(?:public\s+|protected\s+|private\s+)?([\w:]+)',
                          _read(os.path.join(ROOT, rel)))
    return m.group(1).split('::')[-1] if m else None


def fix_chain(cls):
    """fix() the ancestors first, then cls; returns the notes that changed something."""
    chain, c = [], cls
    while c and hdrindex.header_of(c) and len(chain) < 30:
        chain.append(c)
        c = base_of(c)
    return [r for r in (fix(x) for x in reversed(chain)) if 'already agrees' not in r]


def main():
    args = sys.argv[1:]
    hdr = None
    if '--hdr' in args:
        i = args.index('--hdr')
        hdr, args = args[i + 1], args[:i] + args[i + 2:]
    if not args:
        sys.exit(__doc__)
    cmd = args.pop(0) if args[0] in ('diff', 'names', 'slot', 'expr', 'fix') else 'diff'
    if cmd == 'expr':
        return cmd_expr(args)
    if cmd == 'fix':
        chain = '--chain' in args
        for c in [a for a in args if a != '--chain']:
            print('\n'.join(fix_chain(c)) or f'{c}: already agrees' if chain else fix(c))
        return
    cls = args.pop(0)
    # old form: a header basename as the second argument
    if args and args[0].endswith('.h'):
        hdr = hdr or args.pop(0)
    header = header_of(cls, hdr)
    if cmd == 'slot':
        cmd_slot(cls, header, args)
    elif cmd == 'names':
        cmd_names(cls, header)
    else:
        cmd_diff(cls, header, args[0] if args else None)


if __name__ == '__main__':
    main()
