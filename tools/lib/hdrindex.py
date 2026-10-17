"""Map class name -> header path by scanning include/ once (cached in build/hdr_index.json)."""

import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import config

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), os.pardir, os.pardir)
CACHE = os.path.join(config.BUILD, 'hdr_index.json')
DEF = re.compile(r'^\s*(?:class|struct)\s+(?:\w+\s+)?(\w+)\s*(?:final\s*)?(?::[^;{]*)?\{', re.M)


def build():
    idx = {}
    base = os.path.join(ROOT, 'include')
    for d, _, fs in os.walk(base):
        for f in fs:
            if not f.endswith('.h'):
                continue
            p = os.path.join(d, f)
            try:
                text = open(p, encoding='utf-8', errors='replace').read()
            except OSError:
                continue
            for m in DEF.finditer(text):
                name = m.group(1)
                own = os.path.splitext(f)[0] == name
                if name not in idx or own:
                    idx[name] = os.path.relpath(p, ROOT).replace(os.sep, '/')
    os.makedirs(config.BUILD, exist_ok=True)
    json.dump(idx, open(CACHE, 'w'))
    return idx


def load():
    if os.path.exists(CACHE) and os.path.getmtime(CACHE) > os.path.getmtime(os.path.join(ROOT, 'include')):
        return json.load(open(CACHE))
    return build()


def header_of(cls, idx=None):
    return (idx or load()).get(cls)
