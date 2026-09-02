"""Tries a translation unit under several flag sets and reports which one
matches the most functions.

The build flags are not recorded anywhere in the library, so they are found
the same way everything else here is: by compiling and comparing.

    python tools/sweep.py src/PvZ2/PVP/PVPDatas.cpp
"""

import os
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import asmdiff
import config
from pvzelf import Elf

CANDIDATES = [
    ['-O2'],
    ['-Os'],
    ['-O1'],
    ['-O2', '-fno-inline-functions'],
    ['-O2', '-fno-inline-small-functions'],
    ['-Os', '-fno-inline-functions'],
    ['-O3'],
]


def flags_without_opt():
    return [f for f in config.CXXFLAGS if f not in ('-O0', '-O1', '-O2', '-O3', '-Os')]


def score(source, extra):
    obj = os.path.join(config.BUILD, 'sweep.o')
    cmd = [config.GXX, *flags_without_opt(), *extra, '-c', source, '-o', obj]
    done = subprocess.run(cmd, capture_output=True, text=True)
    if done.returncode != 0:
        return None, done.stderr.strip().splitlines()[-1] if done.stderr else 'compile failed'

    ours = Elf(obj)
    game = Elf(config.TARGET_LIB)
    matched = total = 0
    for name, value, size, shndx, styp in ours.symbols():
        if not shndx or styp != 2 or not size:
            continue
        theirs = asmdiff.listing(game, name)
        if theirs is None:
            continue
        mine = asmdiff.listing(ours, name)
        if mine is None:
            continue
        total += 1
        same, count, _ = asmdiff.compare(theirs, mine)
        if same == count and len(theirs) == len(mine):
            matched += 1
    return (matched, total), None


def main():
    source = sys.argv[1]
    os.makedirs(config.BUILD, exist_ok=True)
    best = None
    for extra in CANDIDATES:
        result, err = score(source, extra)
        label = ' '.join(extra)
        if result is None:
            print(f'  {label:<36s} {err}')
            continue
        matched, total = result
        print(f'  {label:<36s} {matched}/{total} match')
        if best is None or matched > best[0]:
            best = (matched, total, label)
    if best:
        print()
        print(f'best: {best[2]}  ({best[0]}/{best[1]})')


if __name__ == '__main__':
    main()
