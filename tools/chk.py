"""Compile one .cpp once; print match state (and with -d the diff) for every function whose mangled name contains a pattern (chk.py <file.cpp> [-d] [pattern ...])."""

import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from lib import asmdiff
import config
from lib import fastcc
import wd
from lib.pvzelf import Elf


def main():
    args = sys.argv[1:]
    diff = '-d' in args
    args = [a for a in args if a != '-d']
    src, pats = os.path.abspath(args[0]), args[1:]
    obj, err = fastcc.compile_file(src, pch=True)
    if obj is None:
        sys.exit('\n'.join([l for l in err.splitlines() if 'error:' in l][:20]))
    game, ours = Elf(config.TARGET_LIB), Elf(obj)
    names = sorted({n for n, v, s, sh, t in ours.symbols() if sh and t == 2 and s and not n.startswith('_ZTV')})
    for n in names:
        if pats and not any(p in n for p in pats):
            continue
        g, o = asmdiff.listing(game, n), asmdiff.listing(ours, n)
        if g is None:
            continue
        same, tot, _ = asmdiff.compare(g, o)
        ok = same == tot and len(g) == len(o)
        print(f'{"OK" if ok else f"{same}/{tot}":>8}  {n}')
        if diff and not ok:
            wd.show(wd.aligned(g, o), 2, False)


main()
