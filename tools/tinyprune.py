"""Drop instantiations (and their includes) from a .cpp until it compiles (tinyprune.py <file.cpp>)."""

import os
import re
import subprocess
import sys

root = os.path.join(os.path.dirname(os.path.abspath(__file__)), os.pardir)
path = sys.argv[1]
for _ in range(200):
    out = subprocess.run([sys.executable, os.path.join(root, 'tools', 'chk.py'), path], capture_output=True, text=True, cwd=root)
    txt = out.stdout + out.stderr
    err = [l for l in txt.splitlines() if 'error' in l]
    if not err:
        break
    e = err[0]
    src = open(path, encoding='utf-8', newline='').read().split('\n')
    m = re.search(r'/([A-Za-z0-9_]+)\.h:\d+', e)
    bad = None
    if m:
        bad = m.group(1)
    else:
        m = re.search(r'Board\.cpp:(\d+)', e)
        if m:
            ln = src[int(m.group(1)) - 1]
            t = re.search(r'template (\w+)\*', ln)
            bad = t.group(1) if t else None
    if not bad:
        print('stuck:', e[:200])
        break
    new = [l for l in src if not (l.startswith('#include "%s.h' % bad) or re.match(r'template %s\* ' % bad, l))]
    print('drop', bad)
    open(path, 'w', encoding='utf-8', newline='').write('\n'.join(new))
