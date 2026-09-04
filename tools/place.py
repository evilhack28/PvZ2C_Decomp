#!/usr/bin/env python3
"""place.py -- suggests a file for each unplaced class from linker address adjacency."""

import argparse
import bisect
import collections
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import config
from pvzelf import Elf

UNPLACED = os.path.join(config.HERE, 'docs', 'unplaced-symbols.txt')
GAP = 8192

NS_DIRS = {'Lua': 'src/LuaEngine', 'Sexy': 'src/SexyAppFramework'}


def qualifier(sym):
    """The class path of a mangled method, e.g. Lua::LMMessageRouter, or None."""
    m = re.match(r'_ZN([KV]*)(.*)', sym)
    if not m:
        return None
    body, parts, i = m.group(2), [], 0
    while i < len(body) and body[i].isdigit():
        j = i
        while j < len(body) and body[j].isdigit():
            j += 1
        n = int(body[i:j])
        parts.append(body[j:j + n])
        i = j + n
    return '::'.join(parts[:-1]) if len(parts) > 1 else None


def placed_index():
    """Class stem -> repo-relative .cpp path, for every file already in src/."""
    out = {}
    for root, _dirs, files in os.walk(config.SRC):
        for fn in files:
            if fn.endswith('.cpp'):
                rel = os.path.relpath(os.path.join(root, fn), config.HERE)
                out.setdefault(fn[:-4], rel.replace(os.sep, '/'))
    return out


def load_symbols():
    e = Elf(config.TARGET_LIB)
    addr = collections.defaultdict(list)
    for name, val, size, _shndx, typ, _bind in e.symbols_full():
        if typ == 2 and size > 0:
            addr[val].append(name)
    return addr


def runs_of(addrs):
    """Split sorted addresses into contiguous runs, largest first."""
    groups, cur = [], [addrs[0]]
    for a, b in zip(addrs, addrs[1:]):
        if b - a > GAP:
            groups.append(cur)
            cur = [b]
        else:
            cur.append(b)
    groups.append(cur)
    return sorted(groups, key=len, reverse=True)


def unplaced_classes():
    for line in open(UNPLACED, encoding='utf-8'):
        line = line.strip()
        if not line or line.startswith('#'):
            continue
        f = line.split('\t')
        if len(f) >= 3:
            yield f[0], int(f[1].split()[0]), int(f[2].split()[0])


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('name', nargs='?', help='one class; default is every unplaced class')
    ap.add_argument('-n', '--limit', type=int, default=40)
    ap.add_argument('--tsv', action='store_true')
    args = ap.parse_args()

    addr = load_symbols()
    allv = sorted(addr)
    placed = placed_index()

    owner = {}
    for v, names in addr.items():
        for s in names:
            q = qualifier(s)
            if q:
                owner.setdefault(v, set()).add(q)

    byclass = collections.defaultdict(list)
    for v, qs in owner.items():
        for q in qs:
            byclass[q].append(v)

    rows = []
    targets = [(args.name, 0, 0)] if args.name else list(unplaced_classes())[:args.limit]

    for cls, nfn, nbytes in targets:
        cands = [k for k in byclass if k == cls or k.endswith('::' + cls)]
        if not cands:
            print(f'{cls}\t-\tno symbols')
            continue
        key = max(cands, key=lambda k: len(byclass[k]))
        vs = sorted(byclass[key])
        best = runs_of(vs)[0]
        i = bisect.bisect_left(allv, best[0])
        j = bisect.bisect_right(allv, best[-1])
        inside = j - i
        purity = len(best) * 100 // max(inside, 1)

        neigh = collections.Counter()
        for v in allv[max(i - 12, 0):min(j + 12, len(allv))]:
            for q in owner.get(v, ()):
                top = q.split('::')[-1]
                if top != cls and top in placed:
                    neigh[top] += 1

        top, hits = neigh.most_common(1)[0] if neigh else (None, 0)
        ns_pre = key.rsplit('::', 1)[0] if '::' in key else None

        sugg, why = '', ''
        if ns_pre and ns_pre in NS_DIRS:
            sugg, why = f'{NS_DIRS[ns_pre]}/{cls}.cpp', f'namespace {ns_pre}'
        elif top:
            sugg, why = os.path.dirname(placed[top]) + '/' + cls + '.cpp', f'next to {top}'

        if why.startswith('namespace') or (purity >= 60 and hits >= 3):
            conf = 'HIGH'
        elif hits >= 3 or purity >= 60:
            conf = 'MED'
        else:
            conf = 'LOW'
        ns = ','.join(f'{k}:{v}' for k, v in neigh.most_common(4))

        if args.tsv:
            print(f'{conf}\t{cls}\t{nfn}\t{nbytes}\t{purity}\t{sugg}\t{why}\t{ns}')
        else:
            rows.append((conf, cls, nfn, nbytes, purity, len(best), len(vs), sugg, why, ns))

    order = {'HIGH': 0, 'MED': 1, 'LOW': 2}
    for conf, cls, nfn, nbytes, purity, nrun, ntot, sugg, why, ns in sorted(
            rows, key=lambda r: (order[r[0]], -r[3])):
        print(f'[{conf}] {cls}  ({nfn} fn, {nbytes} B)')
        print(f'   run {nrun}/{ntot}, {purity}% pure   neighbours: {ns or "-"}')
        print(f'   suggest: {sugg or "-"}   ({why or "no evidence"})')


if __name__ == '__main__':
    main()
