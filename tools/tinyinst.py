"""Explicit instantiations of Board's AddEffect<T>/FindGameSubSystem<T>/... that the game emits (tinyinst.py <Class> <file.cpp> [--write])."""

import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import config
import guess as G
from lib import hdrindex
from lib.pvzelf import Elf

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), os.pardir)


def main():
    cls, path = sys.argv[1], sys.argv[2]
    elf = Elf(config.TARGET_LIB)
    rx = re.compile(r'^_ZN%d%s(\d+)(\w+?)I(\d+)(\w+)EEPT_v$' % (len(cls), cls))
    src = open(path, encoding='utf-8', newline='').read()
    lines, incs, missing = [], [], set()
    for n in sorted({n for n in G.load_syms(elf).values() if n.startswith('_ZN%d%s' % (len(cls), cls))}):
        m = rx.match(n)
        if not m or len(m.group(2)) != int(m.group(1)):
            continue
        meth = m.group(2)
        t = m.group(4)[:int(m.group(3))]
        if not t.isidentifier():
            continue
        h = hdrindex.header_of(t)
        if not h:
            missing.add(t)
            continue
        line = 'template %s* %s::%s<%s>();' % (t, cls, meth, t)
        if line in src:
            continue
        inc = '#include "%s"' % os.path.basename(h)
        if inc not in src and inc not in incs:
            incs.append(inc)
        lines.append(line)
    print(len(lines), 'instantiations,', len(incs), 'new includes, no header:', sorted(missing))
    if '--write' in sys.argv and lines:
        NL = chr(10)
        text = src.replace(chr(13) + NL, NL)
        last = max(m.end() for m in re.finditer(r'^#include .*$', text, re.M))
        text = text[:last] + NL + NL.join(sorted(incs)) + text[last:]
        if 'Template instantiations' not in text:
            text = text.rstrip(NL) + NL + NL + '/' * 15 + ' Template instantiations ' + '/' * 15 + NL
        text = text.rstrip(NL) + NL + NL + NL.join(sorted(lines)) + NL
        open(path, 'w', encoding='utf-8', newline='').write(text)
        subprocess.run([sys.executable, os.path.join(ROOT, 'tools', 'tinyprune.py'), path])


main()
