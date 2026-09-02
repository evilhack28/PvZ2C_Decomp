"""Everything about one plant's progress, in one place.

    python tools/plant.py Iceburg                # progress table
    python tools/plant.py Iceburg --todo         # only what is unwritten
    python tools/plant.py Iceburg --calls        # internal call graph
    python tools/plant.py Iceburg --callers Fire # who calls one method

Classes are found as Plant<Name>, PlantType<Name> and PlantAnimRig_<Name>.
"""

import argparse
import bisect
import glob
import os
import re
import struct
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import asmdiff
import config
from pvzelf import Elf

GREEN, RED, YELLOW, GREY, BOLD, OFF = (
    '\033[32m', '\033[31m', '\033[33m', '\033[90m', '\033[1m', '\033[0m')


def classes_for(name):
    return [f'Plant{name}', f'PlantType{name}', f'PlantAnimRig_{name}']


def mangled_prefixes(classes):
    out = []
    for c in classes:
        out.append(f'_ZN{len(c)}{c}')
        out.append(f'_ZNK{len(c)}{c}')
    return tuple(out)


def game_methods(elf, classes):
    """{symbol: size} for methods actually belonging to these classes."""
    pre = mangled_prefixes(classes)
    out = {}
    for n, v, s, sh, t in elf.symbols():
        if t == 2 and sh and n.startswith(pre):
            out.setdefault(n, (v, s))
    return out


def build(source):
    obj = os.path.join(config.BUILD, os.path.basename(source).replace('.cpp', '.o'))
    done = subprocess.run([config.GXX, *config.CXXFLAGS, '-c', source, '-o', obj],
                          capture_output=True, text=True)
    if done.returncode != 0:
        print(f'{RED}compile failed{OFF}')
        for line in done.stderr.splitlines():
            if ' error: ' in line:
                print('  ', line[:200])
        raise SystemExit(1)
    return obj


def demangle(sym, classes):
    """A readable method name, without running a demangler."""
    m = re.match(r'^_ZNK?(\d+)(\w+?)(\d+)([A-Za-z_]\w*)', sym)
    if not m:
        return sym
    return f'{m.group(2)}::{m.group(4)}'


def call_graph(elf, methods):
    sec = elf.section('.text')
    TA, TO, TZ = sec[2], sec[3], sec[4]
    words = struct.unpack_from('<%dI' % (TZ // 4), elf.data, TO)
    names = {}
    for n, v, s, sh, t in elf.symbols():
        if t == 2 and sh:
            names.setdefault(v, n)
    starts = sorted(names)

    def owner(a):
        i = bisect.bisect_right(starts, a) - 1
        return names.get(starts[i]) if i >= 0 else None

    addr_of = {v: n for n, (v, s) in methods.items()}
    edges = {}
    for i, w in enumerate(words):
        op = w >> 26
        if op not in (0b000101, 0b100101):
            continue
        imm = w & 0x3FFFFFF
        if imm & (1 << 25):
            imm -= (1 << 26)
        src = TA + i * 4
        dst = src + imm * 4
        if dst in addr_of:
            o = owner(src)
            if o:
                edges.setdefault(addr_of[dst], set()).add(o)
    return edges


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('name')
    ap.add_argument('--src')
    ap.add_argument('--todo', action='store_true')
    ap.add_argument('--calls', action='store_true')
    ap.add_argument('--callers')
    args = ap.parse_args()

    classes = classes_for(args.name)
    game = Elf(config.TARGET_LIB)
    methods = game_methods(game, classes)
    if not methods:
        print(f'no methods found for {", ".join(classes)}')
        return

    if args.calls or args.callers:
        edges = call_graph(game, methods)
        if args.callers:
            want = [s for s in methods if args.callers in s]
            for s in want:
                who = sorted(demangle(x, classes) for x in edges.get(s, ()))
                print(f'{demangle(s, classes)} <- {who or "nobody (virtual or unused)"}')
        else:
            for s in sorted(methods, key=lambda x: -methods[x][1]):
                who = sorted(demangle(x, classes) for x in edges.get(s, ()))
                if who:
                    print(f'{demangle(s, classes):<44s} <- {", ".join(who)}')
        return

    # A plant is usually more than one translation unit: the plant itself
    # and its animation rig live in separate files, somewhere under src/.
    if args.src:
        sources = [args.src]
    else:
        root = os.path.join(config.HERE, 'src')
        pats = (f'Plant_{args.name}.cpp', f'PlantAnimRig_{args.name}.cpp',
                f'PlantType_{args.name}.cpp')
        sources = sorted(
            p.replace(os.sep, '/')
            for pat in pats
            for p in glob.glob(f'{root}/**/{pat}', recursive=True))
    mine = {}
    for src in sources:
        if not os.path.exists(src):
            continue
        e = Elf(build(src))
        for n, v, s, sh, t in e.symbols():
            if sh and t == 2 and s:
                mine[n] = e

    rows = []
    for sym, (va, size) in methods.items():
        if sym not in mine:
            rows.append(('todo', 0, 0, size, sym))
            continue
        th = asmdiff.listing(game, sym)
        m = asmdiff.listing(mine[sym], sym)
        if th is None or m is None:
            rows.append(('todo', 0, 0, size, sym))
            continue
        same, tot, _ = asmdiff.compare(th, m)
        state = 'ok' if (same == tot and len(th) == len(m)) else 'near'
        rows.append((state, same, tot, size, sym))

    rows.sort(key=lambda r: (r[0] != 'todo', -r[3]))
    done_bytes = sum(r[3] for r in rows if r[0] == 'ok')
    all_bytes = sum(r[3] for r in rows)
    n_ok = sum(1 for r in rows if r[0] == 'ok')

    for state, same, tot, size, sym in rows:
        if args.todo and state == 'ok':
            continue
        label = demangle(sym, classes)
        if state == 'ok':
            print(f'  {GREEN}OK  {OFF} {size:5d} B  {label}')
        elif state == 'near':
            print(f'  {YELLOW}{same:3d}/{tot:<3d}{OFF} {size:5d} B  {label}')
        else:
            print(f'  {GREY}--  {OFF} {size:5d} B  {label}')

    print()
    print(f'{BOLD}{n_ok}/{len(rows)} methods'
          f'   {done_bytes}/{all_bytes} bytes'
          f'   ({100.0 * done_bytes / all_bytes:.0f}% of the code){OFF}')


if __name__ == '__main__':
    main()
