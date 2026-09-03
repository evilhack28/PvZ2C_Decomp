"""off.py <Class> [member ...] -- struct offsets / sizeof from the headers."""

import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import config

# class -> a header that defines it (extend as needed; --hdr overrides)
GUESS = [
    ('Plant', 'PvZ/Plant.h'), ('PlantType', 'PvZ/PlantType.h'),
    ('PlantPropertySheet', 'PvZ/PlantPropertySheet.h'),
    ('Zombie', 'PvZ/Zombie.h'), ('ZombieType', 'PvZ/ZombieType.h'),
    ('BoardEntity', 'PvZ/BoardEntity.h'), ('RealObject', 'PvZ/RealObject.h'),
    ('Board', 'PvZ/Board.h'), ('LawnApp', 'PvZ/LawnApp.h'),
    ('Projectile', 'PvZ/Projectile.h'), ('GridItem', 'PvZ/GridItem.h'),
]


def probe(cls, members, hdr=None):
    if hdr is None:
        hdr = next((h for c, h in GUESS if c == cls), None)
        if hdr is None:
            # brute: grep the headers for "class <cls>" / "struct <cls>"
            for root, _, files in os.walk(config.HEADERS):
                for f in files:
                    if not f.endswith('.h'):
                        continue
                    p = os.path.join(root, f)
                    if re.search(rf'\b(class|struct)\s+{cls}\b',
                                 open(p, encoding='utf-8', errors='ignore').read()):
                        hdr = os.path.relpath(p, config.HEADERS).replace(os.sep, '/')
                        break
                if hdr:
                    break
    if hdr is None:
        raise SystemExit(f'no header found for {cls} -- pass --hdr <path under include/>')

    src = os.path.join(config.BUILD, 'off.cpp')
    lines = ['#define private public', '#define protected public',
             f'#include "{hdr}"', '#include <cstddef>',
             'template<unsigned long N> struct OffProbe_;']
    if members:
        for i, m in enumerate(members):
            lines.append(f'OffProbe_<offsetof({cls}, {m})> _{i};')
    else:
        lines.append(f'OffProbe_<sizeof({cls})> _sz;')
    open(src, 'w').write('\n'.join(lines) + '\n')

    r = subprocess.run([config.GXX, *config.CXXFLAGS, '-fsyntax-only', src],
                       capture_output=True, text=True)
    want = members or [f'sizeof({cls})']
    got = {}
    for l in r.stderr.splitlines():
        m = re.search(r'OffProbe_<(\d+)ul>', l)
        if m:
            got.setdefault(len(got), int(m.group(1)))
    if not got:
        for l in r.stderr.splitlines():
            if ' error: ' in l:
                print('  ', l[:200])
        raise SystemExit('probe did not compile')
    for i, name in enumerate(want):
        v = got.get(i)
        print(f'  {name:<32} {hex(v) if v is not None else "?"}')


def main():
    a = sys.argv[1:]
    hdr = None
    if '--hdr' in a:
        i = a.index('--hdr')
        hdr = a[i + 1]
        a = a[:i] + a[i + 2:]
    if not a:
        raise SystemExit('usage: python tools/off.py <Class> [member ...] [--hdr path]')
    probe(a[0], a[1:], hdr)


if __name__ == '__main__':
    main()
