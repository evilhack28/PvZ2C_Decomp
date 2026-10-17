"""Candidates copied from already-written functions the game folded into the same code (used by autofill)."""

import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import config
import progress as P
from lib.pvzelf import Elf

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), os.pardir, os.pardir)
CACHE = os.path.join(config.BUILD, 'src_defs.json')
DEF = re.compile(r'^(?P<ret>[^\n;{}=#/]*?)\b(?P<cls>\w+)::(?P<meth>\w+)\((?P<params>[^)]*)\)\s*(?P<const>const)?\s*\n\{', re.M)

_FOLD = None
_DEFS = None


def fold_groups():
    """address -> [function symbols] for every address the game gives more than one name."""
    global _FOLD
    if _FOLD is None:
        e = Elf(config.TARGET_LIB)
        by = {}
        for n, v, s, sh, t in e.symbols():
            if sh and t == 2 and s:
                by.setdefault(v, []).append(n)
        _FOLD = by
    return _FOLD


def body_end(text, start):
    depth = 0
    for i in range(start, len(text)):
        c = text[i]
        if c == '{':
            depth += 1
        elif c == '}':
            depth -= 1
            if depth == 0:
                return i + 1
    return None


def src_defs():
    """(class, method) -> (ret, params, const, body) for every out-of-line definition under src/."""
    global _DEFS
    if _DEFS is not None:
        return _DEFS
    defs = {}
    for d, _, fs in os.walk(os.path.join(ROOT, 'src')):
        for f in fs:
            if not f.endswith('.cpp'):
                continue
            try:
                text = open(os.path.join(d, f), encoding='utf-8', errors='replace').read().replace('\r\n', '\n')
            except OSError:
                continue
            for m in DEF.finditer(text):
                end = body_end(text, m.end() - 1)
                if end is None:
                    continue
                key = (m.group('cls'), m.group('meth'))
                if key in defs:
                    defs[key] = None
                else:
                    defs[key] = (m.group('ret').strip(), m.group('params'), m.group('const') or '', text[m.end() - 1:end])
    _DEFS = defs
    return defs


def candidates(todo):
    """[(sym, cls, text)] copying a folded sibling's source with the class name substituted."""
    groups = fold_groups()
    game = Elf(config.TARGET_LIB)
    defs = src_defs()
    out = []
    for sym in todo:
        comps = P._components(sym)
        if len(comps) < 2 or re.search(r'[CD][012]E', sym[3:8 + len(comps[-1][0])]):
            continue
        found = game.function(sym)
        if not found:
            continue
        cls, meth = comps[-2][0], comps[-1][0]
        for other in groups.get(found[0], []):
            if other == sym:
                continue
            oc = P._components(other)
            if len(oc) < 2:
                continue
            d = defs.get((oc[-2][0], oc[-1][0]))
            if not d:
                continue
            ret, params, const, body = d
            text = '%s %s::%s(%s)%s\n%s\n' % (ret, cls, meth, params, ' const' if sym.startswith('_ZNK') else '', body)
            text = text.replace(oc[-2][0] + '::', cls + '::')
            out.append((sym, cls, text))
            break
    return out
