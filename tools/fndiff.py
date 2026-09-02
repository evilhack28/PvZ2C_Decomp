"""Prints the aligned instruction diff for one function.

    python tools/fndiff.py Iceburg OnAnimCommand
    python tools/fndiff.py Iceburg OnAnimCommand --context 6

`plant.py` reports a score per function; this shows where the score is lost.
The listing is the same normalised form the score is computed from, so a
line that reads identical on both sides is a line that counted as a match.
"""

import argparse
import difflib
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import asmdiff
import config
import plant
from pvzelf import Elf


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('name', help='plant name, as passed to plant.py')
    ap.add_argument('method', help='method name, or part of its mangled name')
    ap.add_argument('--context', type=int, default=3)
    ap.add_argument('--shape', action='store_true',
                    help='compare mnemonics only, to find added or missing '
                         'instructions without register naming in the way')
    args = ap.parse_args()

    game = Elf(config.TARGET_LIB)
    methods = plant.game_methods(game, plant.classes_for(args.name))

    mine = {}
    for src in (f'src/PvZ2/Plant_{args.name}.cpp',
                f'src/PvZ2/PlantAnimRig_{args.name}.cpp'):
        if not os.path.exists(src):
            continue
        e = Elf(plant.build(src))
        for n, v, s, sh, t in e.symbols():
            if sh and t == 2 and s:
                mine[n] = e

    want = [s for s in methods if args.method in s]
    if not want:
        print(f'{args.method}: no such method on {args.name}')
        return
    for sym in want:
        if sym not in mine:
            print(f'{sym}: not written yet')
            continue
        a = asmdiff.render(asmdiff.listing(game, sym))
        b = asmdiff.render(asmdiff.listing(mine[sym], sym))
        same, total, _ = asmdiff.compare(asmdiff.listing(game, sym),
                                         asmdiff.listing(mine[sym], sym))
        print(f'{plant.demangle(sym, plant.classes_for(args.name))}   {same}/{total}')
        print()
        if args.shape:
            sa = [asmdiff._short(x) for x in a]
            sb = [asmdiff._short(y) for y in b]
            ka = [l.split()[0] for l in sa]
            kb = [l.split()[0] for l in sb]
            print(f'game {len(ka)} instructions, ours {len(kb)}')
            ops = difflib.SequenceMatcher(None, ka, kb, autojunk=False).get_opcodes()
            for op, i1, i2, j1, j2 in ops:
                if op == 'equal':
                    continue
                print('')
                print(f'{op}: game[{i1}:{i2}] ours[{j1}:{j2}]')
                for k in range(max(0, i1 - 3), min(len(sa), i2 + 3)):
                    print(f'  {">" if i1 <= k < i2 else " "} game  {sa[k]}')
                for k in range(max(0, j1 - 3), min(len(sb), j2 + 3)):
                    print(f'  {">" if j1 <= k < j2 else " "} ours  {sb[k]}')
            continue
        for line in difflib.unified_diff([asmdiff._short(x) for x in a],
                                         [asmdiff._short(y) for y in b],
                                         'original', 'ours',
                                         lineterm='', n=args.context):
            print(line)


if __name__ == '__main__':
    main()
