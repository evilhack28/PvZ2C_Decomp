#!/usr/bin/env python3
"""Only the instructions that still differ, game vs ours (wd.py <sym>... | <Class> <method>... | <file.cpp> <sym>...; --shape, --asm, -s)."""

import argparse
import difflib
import functools
import glob
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

from lib import asmdiff
import config
from lib import fastcc
from lib.pvzelf import Elf

GREEN, RED, GREY, BOLD, OFF = '\033[32m', '\033[31m', '\033[90m', '\033[1m', '\033[0m'


# --- resolving a symbol to the file that defines it -------------------------

@functools.lru_cache(None)
def _units():
    path = os.path.join(HERE, os.pardir, 'units.json')
    if not os.path.exists(path):
        return {}
    return json.load(open(path)).get('units', {})


@functools.lru_cache(None)
def _game_funcs():
    return frozenset(n for n, v, s, shndx, t in Elf(config.TARGET_LIB).symbols() if t == 2)


@functools.lru_cache(None)
def _sources():
    paths = sorted(glob.glob(os.path.join(HERE, os.pardir, 'src', '**', '*.cpp'), recursive=True))
    return {x: open(x, encoding='utf-8', errors='replace').read() for x in paths}


_OPERATORS = {'()': 'cl', '[]': 'ix', '=': 'aS', '==': 'eq', '!=': 'ne', '<': 'lt', '>': 'gt', '<=': 'le',
              '>=': 'ge', '+': 'pl', '-': 'mi', '*': 'ml', '/': 'dv', '+=': 'pL', '-=': 'mI', '!': 'nt',
              '->': 'pt', '<<': 'ls', '>>': 'rs', 'new': 'nw', 'delete': 'dl'}


def resolve(token, method=None, source=None):
    """(mangled symbol, source path). `token` is a mangled name or a class (`A::B` if nested); `source` skips the file search."""
    units = _units()

    if method is None and token.startswith('_Z'):
        if token not in _game_funcs():
            sys.exit(f'{token}: not a game function (check the <length><name> counts)')
        if source:
            return token, source
        for rel, u in units.items():
            if any(s == token for s, _ in u.get('funcs', [])):
                return token, os.path.normpath(os.path.join(HERE, os.pardir, rel))
        return token, _search_objdefs(token)

    # Itanium mangling writes each name <length><name>, so both appear verbatim.
    parts = token.split('::') + ([method] if method else [])
    needles = [f'{len(p)}{p}' for p in parts]
    if len(parts) >= 2:
        scope, meth = ''.join(needles[:-1]), parts[-1]
        # a ctor/dtor is mangled C1/C2/D0/D1/D2, not by name
        tail = 'C[123]' if meth == parts[-2] else 'D[012]' if meth == '~' + parts[-2] else re.escape(needles[-1])
        if meth.startswith('operator'):
            tail = _OPERATORS.get(meth[8:].strip(), tail)
        exact = re.compile(rf'(?<![0-9]){re.escape(scope)}{tail}(?=[EI])')
        match = exact.search
    else:
        match = lambda sym: needles[0] in sym
    hits = []
    for rel, u in units.items():
        for sym, _size in u.get('funcs', []):
            if match(sym):
                hits.append((sym, os.path.normpath(os.path.join(HERE, os.pardir, rel))))
    # C1/D1 stands for its C2/D2 twin
    hits = [h for h in hits if not re.search(r'[CD]2E', h[0])
            or re.sub(r'([CD])2E', r'\g<1>1E', h[0], 1) not in {x[0] for x in hits}]
    if not hits:
        # not in units.json -- get the symbol from the game, the file by compiling
        game_syms = sorted(n for n in _game_funcs() if match(n))
        game_syms = [n for n in game_syms if not re.search(r'[CD]2E', n)
                     or re.sub(r'([CD])2E', r'\g<1>1E', n, 1) not in game_syms]
        if len(game_syms) == 1:
            return game_syms[0], source or _search_objdefs(game_syms[0])
        if game_syms:
            sys.exit(f'{" ".join(parts)!r} matches several game symbols, pass one:\n  '
                     + '\n  '.join(game_syms[:12]))
        sys.exit(f'no symbol contains {" + ".join(needles)}')
    if len({h[0] for h in hits}) > 1:
        listing = '\n'.join(f'  {s}   {r}' for s, r in hits[:12])
        sys.exit(f'{" ".join(parts)!r} is ambiguous:\n{listing}')
    return hits[0][0], source or hits[0][1]


def _search_objdefs(mangled):
    os.makedirs(config.BUILD, exist_ok=True)
    text = _sources()
    comps, i = [], re.match(r'_ZN?K?', mangled).end() if mangled.startswith('_Z') else 0
    while i < len(mangled) and mangled[i].isdigit():
        k = re.match(r'\d+', mangled[i:])
        n = int(k.group(0))
        comps.append(mangled[i + k.end():i + k.end() + n])
        i += k.end() + n
    if len(comps) < 2:
        sys.exit(f'{mangled}: no class scope to search by -- pass the file: wd.py <file.cpp> {mangled}')
    cls, meth = comps[-2], comps[-1]
    first = {c + '.cpp' for c in comps}
    # only files that write cls::meth or are named after a scope; never a tree sweep
    sources = [x for x in sorted(text) if f'{cls}::{meth}' in text[x]]
    sources += [x for x in sorted(text) if os.path.basename(x) in first and x not in sources]
    if not sources:
        sys.exit(f'{mangled}: no file under src/ writes {cls}::{meth} yet -- pass the file: wd.py <file.cpp> {mangled}')
    for src in sources:
        print(f'searching {os.path.relpath(src)}', file=sys.stderr, flush=True)
        obj, err = fastcc.compile_file(src, pch=True)
        if obj is None:
            print(f'{RED}{os.path.relpath(src)} failed to compile{OFF}\n{(err or "")[:2000]}', file=sys.stderr)
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
    from lib import hdrindex
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


def shape(game_rows, our_rows):
    """Mnemonic-only diff: where instructions were added or dropped, register naming aside."""
    sa = [asmdiff._short(x) for x in asmdiff.render(game_rows)]
    sb = [asmdiff._short(y) for y in asmdiff.render(our_rows)]
    ka, kb = [l.split()[0] for l in sa], [l.split()[0] for l in sb]
    print(f'      game {len(ka)} instructions, ours {len(kb)}')
    for op, i1, i2, j1, j2 in difflib.SequenceMatcher(None, ka, kb, autojunk=False).get_opcodes():
        if op == 'equal':
            continue
        print(f'\n      {op}: game[{i1}:{i2}] ours[{j1}:{j2}]')
        for k in range(max(0, i1 - 3), min(len(sa), i2 + 3)):
            print(f'      {RED if i1 <= k < i2 else GREY}{">" if i1 <= k < i2 else " "} game  {sa[k]}{OFF}')
        for k in range(max(0, j1 - 3), min(len(sb), j2 + 3)):
            print(f'      {GREEN if j1 <= k < j2 else GREY}{">" if j1 <= k < j2 else " "} ours  {sb[k]}{OFF}')


def targets(items):
    """[(mangled, source)] from `sym...`, `Class method...` or `file.cpp sym|Class::method...`."""
    first = items[0]
    if first.endswith('.cpp') or '/' in first or os.sep in first:
        source = first if os.path.isabs(first) else os.path.normpath(os.path.join(os.getcwd(), first))
        out = []
        for n in items[1:]:
            if n.startswith('_Z'):
                out.append(resolve(n, source=source))
                continue
            cls, _, meth = n.replace(' ', '::').rpartition('::')
            out.append(resolve(cls, meth, source) if cls else resolve(meth, source=source))
        return out
    if first.startswith('_Z'):
        return [resolve(n) for n in items]
    return [resolve(first, m) for m in (items[1:] or [None])]


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('items', nargs='+', help='mangled names | Class method... | file.cpp sym...')
    ap.add_argument('-c', '--context', type=int, default=2, help='matching lines kept around each hunk (default 2)')
    ap.add_argument('-a', '--all', action='store_true', help='every line, folded-name noise included')
    ap.add_argument('--asm', action='store_true', help='a clean listing instead of a diff')
    ap.add_argument('--ours', action='store_true', help='with --asm, our listing not the game')
    ap.add_argument('--shape', action='store_true', help='mnemonics only: find added or missing instructions')
    ap.add_argument('-s', '--src', action='store_true', help='print our source of just this function (and its header decl) first')
    args = ap.parse_args()

    game_elf, objs, elfs, rc = Elf(config.TARGET_LIB), {}, {}, 0
    for mangled, source in targets(args.items):
        rel = os.path.relpath(source, os.path.join(HERE, os.pardir))
        if args.src:
            print_source(source, mangled)
        if source not in objs:
            objs[source] = build(source)
            elfs[source] = Elf(objs[source])
        game = asmdiff.listing(game_elf, mangled)
        ours = asmdiff.listing(elfs[source], mangled)
        if game is None or ours is None:
            print(f'{BOLD}{mangled}{OFF}  {RED}' + ('not in the game' if game is None else f'{rel} does not define it') + OFF)
            rc = 1
            continue
        same, total, _ = asmdiff.compare(game, ours)
        ok = same == total and len(game) == len(ours)
        tag = f'{GREEN}OK{OFF}' if ok else f'{RED}{same}/{total} ({100 * same // max(total, 1)}%){OFF}'
        countnote = '' if len(game) == len(ours) else f'  {RED}[game {len(game)} insns, ours {len(ours)}]{OFF}'
        print(f'{BOLD}{mangled}{OFF}  {rel}   {tag}{countnote}')
        if args.asm:
            members = member_names(mangled)
            for line in asmdiff.render(ours if args.ours else game):
                print(f'  {annotate(asmdiff._short(line), members)}')
        elif args.shape:
            shape(game, ours)
        elif not ok:
            show(aligned(game, ours), args.context, args.all)
        rc = rc or (0 if ok else 1)
    return rc


if __name__ == '__main__':
    raise SystemExit(main())
