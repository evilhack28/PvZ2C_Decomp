#!/usr/bin/env python3
"""Not-yet-matching functions, largest first.

    py -3 first_diff.py [FILTER] [-n N] [--stubs]
"""

import argparse
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, 'tools'))

import config  # noqa: E402
import progress  # noqa: E402
from pvzelf import Elf  # noqa: E402


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('filter', nargs='?')
    ap.add_argument('-n', type=int, default=20)
    ap.add_argument('--stubs', action='store_true', help='include not-yet-started units')
    args = ap.parse_args()

    progress._CACHE = True
    game = Elf(config.TARGET_LIB)
    game_syms = {}
    for n, v, s, sh, t in game.symbols():
        if t == 2 and sh and s:
            game_syms.setdefault(n, (v, s))
    game_names = sorted(game_syms)

    mpath = os.path.join(config.HERE, 'units.json')
    manifest = json.load(open(mpath))['units'] if os.path.exists(mpath) else {}

    todo = []
    for src in progress.sources():
        if args.filter and args.filter.lower() not in src.lower():
            continue
        _s, obj, err = progress.compile_one(src)
        if not obj:
            print(f'COMPILE FAILED  {src}')
            continue
        rel = os.path.relpath(src, config.HERE).replace(os.sep, '/')
        if obj is progress.STUB and not (args.stubs or args.filter):
            continue
        for state, same, tot, size, label in progress.analyse(
                src, obj, game, game_syms, game_names, manifest.get(rel)):
            if state == 'near':
                todo.append((size, f'{same}/{tot}', label, rel))
            elif state == 'todo':
                todo.append((size, 'unwritten', label, rel))

    todo.sort(reverse=True)
    w = max((len(t[2]) for t in todo[:args.n]), default=0)
    for size, score, label, rel in todo[:args.n]:
        print(f'  {size:6d} B  {score:>10s}  {label:<{w}s}  {rel}')
    print(f'\n{len(todo)} functions left')


if __name__ == '__main__':
    main()
