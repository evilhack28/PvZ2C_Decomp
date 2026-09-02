"""Compares one of our functions against a raw address range in the game.

    python tools/rawdiff.py <our-symbol> 0x3f37340 1556

Most of a translation unit never reaches `.dynsym`. Local clones, template
instantiations and the classes the reflection macros declare inside a
function body are all emitted as local symbols, and the shipped library is
stripped of those. `plant.py` therefore never scores them, even when they
are the largest thing in the file.

This takes the game's side as an address and a length, read out of the gaps
between exported symbols, and scores it against a symbol from our object
using the same normalisation `plant.py` uses.
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


class RawAt(object):
    """An Elf that reports one extra function at a fixed address."""

    def __init__(self, elf, name, addr, size):
        self._elf = elf
        self._name = name
        self._addr = addr
        self._size = size

    def __getattr__(self, item):
        return getattr(self._elf, item)

    def function(self, name):
        if name != self._name:
            return self._elf.function(name)
        return self._addr, self._size, self._elf.read_at(self._addr, self._size)

    def section_of(self, name):
        return '.text' if name == self._name else self._elf.section_of(name)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('symbol', help='the symbol in our object')
    ap.add_argument('addr', help='address of the game-side function')
    ap.add_argument('size', type=int, help='its length in bytes')
    ap.add_argument('--src', default='src/PvZ2/Plant_Iceburg.cpp')
    ap.add_argument('--context', type=int, default=3)
    args = ap.parse_args()

    ours = Elf(plant.build(args.src))
    game = RawAt(Elf(config.TARGET_LIB), args.symbol, int(args.addr, 0), args.size)

    a = asmdiff.listing(game, args.symbol)
    b = asmdiff.listing(ours, args.symbol)
    if b is None:
        print(f'{args.symbol}: not in {args.src}')
        return
    same, total, _ = asmdiff.compare(a, b)
    print(f'{args.symbol[:80]}   {same}/{total}')
    print()
    for line in difflib.unified_diff([asmdiff._short(x) for x in asmdiff.render(a)],
                                     [asmdiff._short(y) for y in asmdiff.render(b)],
                                     'original', 'ours', lineterm='', n=args.context):
        print(line)


if __name__ == '__main__':
    main()
