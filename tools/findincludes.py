"""Compiles a file, and for every "No such file or directory" it reports,
finds that header in the tree and adds its directory to the include path.

Prints the flags it settled on, which then go into config.py.

    python tools/findincludes.py build/probe.cpp
"""

import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import config

MISSING = re.compile(r'fatal error: (.+?): No such file or directory')


def index_tree(root):
    """{'a/b.h': [dirs that make that path resolve]}"""
    byname = {}
    for dirpath, _dirs, files in os.walk(root):
        for f in files:
            if not f.endswith(('.h', '.hpp', '.inl')):
                continue
            full = os.path.join(dirpath, f).replace('\\', '/')
            byname.setdefault(f, []).append(full)
    return byname


def resolve(want, byname):
    """Directories that would satisfy #include "want"."""
    base = os.path.basename(want)
    out = []
    for full in byname.get(base, []):
        if want.count('/') == 0:
            out.append(os.path.dirname(full))
        elif full.endswith('/' + want):
            out.append(full[:-(len(want) + 1)])
    return out


def main():
    source = sys.argv[1]
    byname = index_tree(config.HEADERS)
    extra = []
    seen = set()

    for _round in range(400):
        cmd = [config.GXX, *config.CXXFLAGS, *extra, '-fsyntax-only', source]
        done = subprocess.run(cmd, capture_output=True, text=True)
        if done.returncode == 0:
            print('compiles clean')
            break

        m = MISSING.search(done.stderr)
        if not m:
            errs = [l for l in done.stderr.splitlines() if ' error: ' in l]
            print(f'{len(errs)} error(s), none of them a missing header:')
            for line in errs[:20]:
                print('  ', line[:220])
            break

        want = m.group(1)
        if want in seen:
            print(f'cannot resolve {want}')
            break
        seen.add(want)

        dirs = resolve(want, byname)
        if not dirs:
            print(f'{want} is not anywhere in the header tree')
            break
        dirs.sort(key=len)
        extra += ['-I', dirs[0]]
        print(f'  + {want:<44s} -> {dirs[0][len(config.HEADERS) + 1:]}')

    print()
    print('extra include flags:')
    for i in range(0, len(extra), 2):
        print(f'    {extra[i]} {extra[i + 1]}')


if __name__ == '__main__':
    main()
