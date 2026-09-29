#!/usr/bin/env python3
"""Only the instructions that still differ, game vs ours (wd.py <sym> | <Class> <method>)."""

import argparse
import difflib
import glob
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import asmdiff
import config
import fastcc
from pvzelf import Elf

GREEN, RED, GREY, BOLD, OFF = '\033[32m', '\033[31m', '\033[90m', '\033[1m', '\033[0m'


# --- resolving a symbol to the file that defines it -------------------------

def _units():
    path = os.path.join(HERE, os.pardir, 'units.json')
    if not os.path.exists(path):
        return {}
    return json.load(open(path)).get('units', {})


def resolve(token, method=None):
    """(mangled symbol, source path). `token` is a mangled name or a class."""
    units = _units()

    if method is None and token.startswith('_Z'):
        for rel, u in units.items():
            if any(s == token for s, _ in u.get('funcs', [])):
                return token, os.path.normpath(os.path.join(HERE, os.pardir, rel))
        # not mapped -- find it by compiling candidates
        return token, _search_objdefs(token)

    # Itanium mangling writes each name <length><name>, so both appear verbatim.
    parts = [token] + ([method] if method else [])
    needles = [f'{len(p)}{p}' for p in parts]
    hits = []
    for rel, u in units.items():
        for sym, _size in u.get('funcs', []):
            if all(n in sym for n in needles):
                hits.append((sym, os.path.normpath(os.path.join(HERE, os.pardir, rel))))
    if not hits:
        # not in units.json -- get the symbol from the game, the file by compiling
        game_syms = sorted({n for n, v, s, shndx, t in Elf(config.TARGET_LIB).symbols()
                            if t == 2 and all(x in n for x in needles)})
        if len(game_syms) == 1:
            return game_syms[0], _search_objdefs(game_syms[0])
        if game_syms:
            sys.exit(f'{" ".join(parts)!r} matches several game symbols, pass one:\n  '
                     + '\n  '.join(game_syms[:12]))
        sys.exit(f'no symbol contains {" + ".join(needles)}')
    if len({h[0] for h in hits}) > 1:
        listing = '\n'.join(f'  {s}   {r}' for s, r in hits[:12])
        sys.exit(f'{" ".join(parts)!r} is ambiguous:\n{listing}')
    return hits[0][0], hits[0][1]


def _search_objdefs(mangled):
    os.makedirs(config.BUILD, exist_ok=True)
    sources = sorted(glob.glob(os.path.join(HERE, os.pardir, 'src', '**', '*.cpp'), recursive=True))
    comps, i = [], re.match(r'_ZN?K?', mangled).end() if mangled.startswith('_Z') else 0
    while i < len(mangled) and mangled[i].isdigit():
        k = re.match(r'\d+', mangled[i:])
        n = int(k.group(0))
        comps.append(mangled[i + k.end():i + k.end() + n])
        i += k.end() + n
    if len(comps) >= 2:
        cls, meth = comps[-2], comps[-1]
        exact = re.compile(rf'{re.escape(cls)}::{re.escape(meth)}')
        defines = re.compile(rf'{re.escape(cls)}::')
        first = {c + '.cpp' for c in comps}
        sources = ([x for x in sources if os.path.basename(x) in first]
                   + [x for x in sources if os.path.basename(x) not in first])
    for src in sources:
        obj, _err = fastcc.compile_file(src)
        if obj is None:
            continue
        syms = Elf(obj).symbols()
        if any(n == mangled and shndx and t == 2 for n, v, s, shndx, t in syms):
            return src
        # ctor/dtor aliases: accept the class's own file if it defines the same class::name
        base = os.path.basename(src)[:-4]
        if base in comps[-2:] and re.search(rf'{len(base)}{base}[CD]\d', mangled) \
                and any(f'{len(base)}{base}' in n and shndx for n, v, s, shndx, t in syms):
            return src
    sys.exit(f'{mangled}: not defined by any file under src/')


# --- build ---------------------------------------------------------------

def build(source):
    # recompiles only when the source or a header in its depfile changed
    obj, err = fastcc.compile_file(source, pch=True)
    if obj is None:
        # the include-order warnings are a wall of noise; keep only real errors
        lines = [l for l in err.splitlines() if 'error:' in l]
        print('\n'.join(lines[:40]) or err[:2000])
        sys.exit(f'{RED}compile failed{OFF}')
    return obj


# --- annotation ----------------------------------------------------------

_MEMREF = re.compile(r'\[x\d+, #(0x[0-9a-f]+)\]')


def member_names(mangled):
    """{offset: field} for the classes this symbol probably touches. Best effort."""
    try:
        import explain
        m = re.match(r'^_ZNK?\d+(\w+?)\d+[A-Za-z_]', mangled)
        classes = ([m.group(1)] if m else []) + ['BoardEntity', 'Plant', 'Zombie']
        return explain.field_table(Elf(config.TARGET_LIB), classes)
    except Exception:
        return {}


def annotate(line, members):
    m = _MEMREF.search(line)
    if m and int(m.group(1), 0) in members:
        return f'{line:<40s} ; {members[int(m.group(1), 0)]}'
    return line


# --- the diff -------------------------------------------------------------

def aligned(game_rows, our_rows):
    """[(g, o, matched)] -- g/o are rendered strings or None for a gap."""
    a, b = asmdiff.render(game_rows), asmdiff.render(our_rows)
    sm = difflib.SequenceMatcher(None, [asmdiff._key(x) for x in a],
                                 [asmdiff._key(y) for y in b], autojunk=False)
    rows = []
    for op, i1, i2, j1, j2 in sm.get_opcodes():
        if op == 'equal':
            rows += [(a[k], b[j1 + (k - i1)], True) for k in range(i1, i2)]
        elif op == 'replace':
            g, o = a[i1:i2], b[j1:j2]
            for k in range(max(len(g), len(o))):
                gg = g[k] if k < len(g) else None
                oo = o[k] if k < len(o) else None
                same = gg is not None and oo is not None and asmdiff._same(gg, oo)
                rows.append((gg, oo, same))
        elif op == 'delete':
            rows += [(x, None, False) for x in a[i1:i2]]
        elif op == 'insert':
            rows += [(None, y, False) for y in b[j1:j2]]
    return rows


def show(rows, context, show_all):
    keep = [i for i, (_, _, ok) in enumerate(rows) if not ok]
    if not keep:
        return
    if show_all:
        wanted = set(range(len(rows)))
    else:
        wanted = set()
        for i in keep:
            wanted |= set(range(max(0, i - context), min(len(rows), i + context + 1)))

    prev = -1
    for i in sorted(wanted):
        if prev >= 0 and i != prev + 1:
            print(f'      {GREY}...{OFF}')
        g, o, ok = rows[i]
        g = asmdiff._short(g) if g else ''
        o = asmdiff._short(o) if o else ''
        if ok:
            print(f'      {GREY}  {g}{OFF}')
        else:
            if g:
                print(f'      {RED}- {g}{OFF}')
            if o:
                print(f'      {GREEN}+ {o}{OFF}')
        prev = i


def _body_end(text, i):
    """Index just past the brace block starting at the first '{' from i (skips strings and comments)."""
    depth, n = 0, len(text)
    while i < n:
        c = text[i]
        if text.startswith('//', i):
            i = text.find('\n', i)
            if i < 0:
                return n
        elif text.startswith('/*', i):
            i = text.find('*/', i) + 1 or n
        elif c in '"\'':
            j = i + 1
            while j < n and text[j] != c:
                j += 2 if text[j] == '\\' else 1
            i = j
        elif c == '{':
            depth += 1
        elif c == '}':
            depth -= 1
            if depth == 0:
                return i + 1
        elif c == ';' and depth == 0:
            return i + 1
        i += 1
    return n


def source_of(source, mangled):
    """[(first line no, lines)] for each definition of the symbol's Class::method in source, plus header decls."""
    import progress
    parts = progress.pretty(mangled).split('::')
    if len(parts) < 2:
        return [], []
    cls, meth = parts[-2], parts[-1]
    text = open(source, encoding='utf-8', errors='replace').read()
    out = []
    for m in re.finditer(rf'^(?:[^\s#/][^\n;]*\b)?{re.escape(cls)}::{re.escape(meth)}\s*\(', text, re.M):
        end = _body_end(text, m.end())
        first = text.count('\n', 0, m.start()) + 1
        out.append((first, text[m.start():end].split('\n')))
    decls = []
    import hdrindex
    h = hdrindex.header_of(cls)
    want = re.compile((r'~' if meth.startswith('~') else r'(?<!~)\b') + rf'{re.escape(meth.lstrip("~"))}\s*\(')
    if h:
        h = os.path.join(HERE, os.pardir, h)
        for no, line in enumerate(open(h, encoding='utf-8', errors='replace'), 1):
            if want.search(line):
                decls.append(f'{os.path.relpath(h, os.path.join(HERE, os.pardir))}:{no}: {line.strip()}')
    return out, decls


def print_source(source, mangled):
    defs, decls = source_of(source, mangled)
    for d in decls:
        print(f'  {GREY}{d}{OFF}')
    if not defs:
        print(f'  {GREY}(no definition in {os.path.basename(source)} yet){OFF}')
    for first, lines in defs:
        for k, line in enumerate(lines):
            print(f'{first + k:6d}\t{line}')
    print()


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('symbol', help='mangled name, or a class (with method as the next arg)')
    ap.add_argument('method', nargs='?')
    ap.add_argument('-c', '--context', type=int, default=2, help='matching lines kept around each hunk (default 2)')
    ap.add_argument('-a', '--all', action='store_true', help='every line, folded-name noise included')
    ap.add_argument('--asm', action='store_true', help='a clean listing instead of a diff')
    ap.add_argument('--ours', action='store_true', help='with --asm, our listing not the game')
    ap.add_argument('-s', '--src', action='store_true', help='print our source of just this function (and its header decl) first')
    args = ap.parse_args()

    mangled, source = resolve(args.symbol, args.method)
    rel = os.path.relpath(source, os.path.join(HERE, os.pardir))
    if args.src:
        print_source(source, mangled)
    obj = build(source)

    game = asmdiff.listing(Elf(config.TARGET_LIB), mangled)
    ours = asmdiff.listing(Elf(obj), mangled)
    if game is None:
        sys.exit(f'{mangled}: not in the game')
    if ours is None:
        sys.exit(f'{mangled}: {rel} compiled but does not define it')

    same, total, _ = asmdiff.compare(game, ours)
    ok = same == total and len(game) == len(ours)
    tag = f'{GREEN}OK{OFF}' if ok else f'{RED}{same}/{total} ({100 * same // max(total, 1)}%){OFF}'
    countnote = '' if len(game) == len(ours) else f'  {RED}[game {len(game)} insns, ours {len(ours)}]{OFF}'
    print(f'{BOLD}{mangled}{OFF}  {rel}   {tag}{countnote}')

    if args.asm:
        members = member_names(mangled)
        for line in asmdiff.render(ours if args.ours else game):
            print(f'  {annotate(asmdiff._short(line), members)}')
        return 0 if ok else 1

    if not ok:
        show(aligned(game, ours), args.context, args.all)
    return 0 if ok else 1


if __name__ == '__main__':
    raise SystemExit(main())
