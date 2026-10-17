"""autofill.py with member names taken from the header's offsets too (tinyfill.py <file.cpp> [--min N] [--dry])."""

import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import guess as G
import autofill as A

_orig = G.field_map
_cache = {}


def header_fields(cls):
    if cls not in _cache:
        out = subprocess.run([sys.executable, os.path.join(A.ROOT, 'tools', 'off.py'), cls, '--all'],
                             capture_output=True, text=True, cwd=A.ROOT).stdout
        _cache[cls] = {int(m.group(2), 16): m.group(1)
                       for m in re.finditer(r'^\s+(\w+)\s+0x([0-9a-f]+)\s*$', out, re.M)}
    return _cache[cls]


def field_map(elf, cls):
    d = dict(header_fields(cls))
    d.update(_orig(elf, cls))
    return d


G.field_map = field_map

if __name__ == '__main__':
    sys.exit(A.main())
