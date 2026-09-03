#!/usr/bin/env python3
"""wdm.py <src.cpp|Class> <sym|method> ... -- compile once, diff many vs the game."""

import argparse
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import asmdiff
import config
import wd
from pvzelf import Elf

GREEN, RED, GREY, BOLD, OFF = '\033[32m', '\033[31m', '\033[90m', '\033[1m', '\033[0m'


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('first', help='a .cpp path, or a class name')
    ap.add_argument('names', nargs='+', help='mangled symbols, or methods of the class')
    ap.add_argument('-c', '--context', type=int, default=2)
    ap.add_argument('-a', '--all', action='store_true')
    args = ap.parse_args()

    is_path = args.first.endswith('.cpp') or os.sep in args.first or '/' in args.first
    targets = []  # (mangled, source)
    if is_path:
        source = os.path.normpath(os.path.join(HERE, os.pardir, args.first)) \
            if not os.path.isabs(args.first) else args.first
        for n in args.names:
            if n.startswith('_Z'):
                targets.append((n, source))
            else:
                cls, _, meth = n.replace('::', ' ').partition(' ')
                m, _s = wd.resolve(cls, meth or None)
                targets.append((m, source))
    else:
        for meth in args.names:
            m, source = wd.resolve(args.first, meth)
            targets.append((m, source))

    sources = sorted({s for _, s in targets})
    objs = {}
    for s in sources:
        rel = os.path.relpath(s, os.path.join(HERE, os.pardir))
        print(f'{GREY}compiling {rel} ...{OFF}', file=sys.stderr)
        objs[s] = wd.build(s)

    rc = 0
    for mangled, source in targets:
        rel = os.path.relpath(source, os.path.join(HERE, os.pardir))
        game = asmdiff.listing(Elf(config.TARGET_LIB), mangled)
        ours = asmdiff.listing(Elf(objs[source]), mangled)
        if game is None:
            print(f'{BOLD}{mangled}{OFF}  {RED}not in the game{OFF}')
            continue
        if ours is None:
            print(f'{BOLD}{mangled}{OFF}  {RED}{rel} does not define it{OFF}')
            rc = 1
            continue
        same, total, _ = asmdiff.compare(game, ours)
        ok = same == total and len(game) == len(ours)
        tag = f'{GREEN}OK{OFF}' if ok else f'{RED}{same}/{total} ({100 * same // max(total, 1)}%){OFF}'
        note = '' if len(game) == len(ours) else f'  {RED}[game {len(game)}, ours {len(ours)}]{OFF}'
        print(f'{BOLD}{mangled}{OFF}  {tag}{note}')
        if not ok:
            wd.show(wd.aligned(game, ours), args.context, args.all)
        rc = rc or (0 if ok else 1)
    return rc


if __name__ == '__main__':
    sys.exit(main())
