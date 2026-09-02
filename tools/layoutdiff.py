"""Compares a class's field offsets in the game against what the headers give.

Reads the offsets the game registers for every reflected field, generates an
offsetof probe for the same names, compiles it, and prints the two side by
side. A run of fields all off by the same amount says how much something
above them grew; the point where the delta changes is where it grew.

    python tools/layoutdiff.py Plant Plant.h
"""

import os
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import config
import fields as fieldtool
from pvzelf import Elf


def game_fields(cls):
    elf = Elf(config.TARGET_LIB)
    sym = f'_ZN{len(cls)}{cls}15StaticClassInitEv'
    found = elf.function(sym)
    if found is None:
        return []
    va, size, _ = found
    fn = fieldtool._regfn(elf, va, size)
    if not fn:
        return []
    return [(k, o) for k, o in fieldtool.fields(elf, fn) if not k[0].isupper()]


def main():
    cls = sys.argv[1]
    headers = sys.argv[2:] or [f'{cls}.h']

    want = game_fields(cls)
    if not want:
        print(f'{cls}: nothing registered')
        return

    src = os.path.join(config.BUILD, 'layoutprobe.cpp')
    obj = os.path.join(config.BUILD, 'layoutprobe.o')
    names = [n for n, _ in want]
    missing = []
    ok = False

    # A member the game registers and the headers lack is itself part of the
    # answer, so those are dropped one round at a time and reported.
    for _round in range(len(names) + 2):
        with open(src, 'w') as f:
            f.write('#define private public\n#define protected public\n')
            for h in headers:
                f.write(f'#include "{h}"\n')
            f.write('#include <cstddef>\n')
            f.write(f'char probe__size[sizeof({cls})] = {{}};\n')
            for name in names:
                f.write(f'char probe_{name}[offsetof({cls}, {name}) + 1] = {{}};\n')

        done = subprocess.run([config.GXX, *config.CXXFLAGS, '-c', src, '-o', obj],
                              capture_output=True, text=True)
        if done.returncode == 0:
            ok = True
            break

        gone = set()
        for line in done.stderr.splitlines():
            if 'has no member named' in line:
                gone.add(line.rsplit("'", 2)[-2])
        if not gone:
            bad = [l for l in done.stderr.splitlines() if ' error: ' in l]
            print(f'{len(bad)} error(s); first few:')
            for line in bad[:8]:
                print('  ', line[:200])
            return
        missing += sorted(gone)
        names = [n for n in names if n not in gone]

    if not ok:
        print('could not get a clean probe')
        return

    elf = Elf(obj)
    ours = {n[len('probe_'):]: s - 1 for n, v, s, sh, t in elf.symbols()
            if n.startswith('probe_') and n != 'probe__size'}
    size = next((s for n, v, s, sh, t in elf.symbols() if n == 'probe__size'), None)

    print(f'{cls}: sizeof = {size:#x} in the headers')
    if missing:
        print(f'the game registers these and the headers have none: {", ".join(missing)}')
    print()
    print(f'{"field":<34s} {"game":>7s} {"headers":>8s} {"delta":>7s}')
    last = None
    for name, off in sorted(want, key=lambda x: x[1]):
        mine = ours.get(name)
        if mine is None:
            print(f'{name:<34s} {off:>7x} {"absent":>8s}')
            continue
        delta = off - mine
        mark = '' if delta == last else '   <-- delta changes'
        last = delta
        print(f'{name:<34s} {off:>7x} {mine:>8x} {delta:>+7d}{mark}')


if __name__ == '__main__':
    main()
