#!/usr/bin/env python3
"""Game-vs-ours listing for one function.

    py -3 diff.py _ZN12PlantIceburg9HasShadowEv   # mangled symbol
    py -3 diff.py Iceburg ApplyPlantfood          # plant + method (-> fndiff.py)
"""

import glob
import json
import os
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, 'tools'))

import config  # noqa: E402
from pvzelf import Elf  # noqa: E402
from progress import is_stub  # noqa: E402

PY = [sys.executable]


def resolve_file(mangled):
    mpath = os.path.join(HERE, 'units.json')
    if os.path.exists(mpath):
        for path, u in json.load(open(mpath))['units'].items():
            if any(s == mangled for s, _ in u.get('funcs', [])):
                full = os.path.join(HERE, path)
                if os.path.exists(full) and not is_stub(full):
                    return path
    os.makedirs(config.BUILD, exist_ok=True)
    for src in sorted(glob.glob(os.path.join(HERE, 'src', '**', '*.cpp'), recursive=True)):
        if is_stub(src):
            continue
        obj = os.path.join(config.BUILD, os.path.basename(src).replace('.cpp', '.diff.o'))
        if subprocess.run([config.GXX, *config.CXXFLAGS, '-c', src, '-o', obj],
                          capture_output=True).returncode != 0:
            continue
        if any(n == mangled and shndx and t == 2
               for n, v, s, shndx, t in Elf(obj).symbols()):
            return src
    return None


def main(argv):
    if not argv:
        print(__doc__)
        return 2
    if len(argv) >= 2 and not argv[0].startswith('_Z'):
        return subprocess.call(PY + [os.path.join(HERE, 'tools', 'fndiff.py'), *argv])
    src = resolve_file(argv[0])
    if not src:
        print(f'{argv[0]}: not defined by any file under src/')
        return 1
    print(f'# {os.path.relpath(src, HERE)}', flush=True)
    return subprocess.call(PY + [os.path.join(HERE, 'tools', 'm.py'), src, '-f', argv[0], '-v'])


if __name__ == '__main__':
    raise SystemExit(main(sys.argv[1:]))
