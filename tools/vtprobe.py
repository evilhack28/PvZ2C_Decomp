"""Compares a class's vtable slot numbering against the game's by name.

    python tools/vtprobe.py Zombie Zombie.h

`vtdiff.py` needs an object file that emits `_ZTV<class>`, which only happens
in the translation unit defining the class's key function. For a class we
only have a header for, nothing emits it.

This works from names instead. `slotprobe.py` gives the offset the headers
compile each no-argument virtual to. The game's vtable is scanned for the
address of that same mangled symbol. Where the two offsets stop agreeing is
where a header is missing declarations, and the delta is how many.

Only methods the game exports and places in the table exactly once are used,
so identical code folding cannot put a name in the wrong row.
"""

import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import config
import slotprobe
from pvzelf import Elf


def game_offsets(elf, cls):
    """Offset of every uniquely-placed method of `cls` in its own vtable."""
    table = f'_ZTV{len(cls)}{cls}'
    addr = size = None
    for n, v, s, sh, t in elf.symbols():
        if n == table and sh:
            addr, size = v, s
            break
    if addr is None:
        return None

    # The vptr stored in an object points 16 bytes into the table, past the
    # offset-to-top and the typeinfo pointer, so a call's `[x8, #N]` is
    # measured from there. Offsets below are vptr-relative to match.
    slots = []
    for off in range(16, size, 8):
        raw = elf.read_at(addr + off, 8)
        if not raw:
            break
        slots.append((off - 16, int.from_bytes(raw, 'little')))

    # A name is usable only if its address sits in exactly one row.
    seen = {}
    for off, entry in slots:
        seen.setdefault(entry, []).append(off)

    out = {}
    tag = f'{len(cls)}{cls}'
    for n, v, s, sh, t in elf.symbols():
        if not (sh and t == 2 and n.startswith('_Z')):
            continue
        if tag not in n:
            continue
        rows = seen.get(v)
        if not rows or len(rows) != 1:
            continue
        m = re.search(re.escape(tag) + r'(\d+)', n)
        if not m:
            continue
        want = int(m.group(1))
        name = n[m.end():m.end() + want]
        if len(name) == want and re.fullmatch(r'[A-Za-z_]\w*', name):
            out.setdefault(name, rows[0])
    return out


def main():
    cls = sys.argv[1]
    header = sys.argv[2]

    game = game_offsets(Elf(config.TARGET_LIB), cls)
    if game is None:
        print(f'_ZTV{len(cls)}{cls}: not in the game')
        return

    ours = dict((name, off) for off, name in
                slotprobe.probe(cls, header, slotprobe.candidates_from(header)))

    both = sorted((game[n], ours[n], n) for n in ours if n in game)
    if not both:
        print(f'{cls}: no method is both probeable and uniquely placed')
        return

    print(f'{cls}: {len(both)} methods anchored in both tables')
    print()
    print(f'  {"game":>7}  {"ours":>7}  {"delta":>6}  method')
    run = None
    for g, o, n in both:
        d = g - o
        mark = '' if d == 0 else '  <-'
        if d != run:
            run = d
            mark += f'  gap changes to {d // 8:+d} slot(s)' if d else '  (aligned)'
        print(f'  {g:#07x}  {o:#07x}  {d // 8:+6d}  {n}{mark}')

    bad = [(g, o, n) for g, o, n in both if g != o]
    print()
    if not bad:
        print('  every anchored method agrees')
    else:
        first = bad[0]
        prior = [x for x in both if x[0] < first[0] and x[0] == x[1]]
        after = prior[-1] if prior else None
        print(f'  {len(bad)} of {len(both)} disagree.')
        print(f'  first divergence: {first[2]} '
              f'(game {first[0]:#x}, ours {first[1]:#x}, '
              f'{(first[0] - first[1]) // 8:+d} slots)')
        if after:
            print(f'  last agreement:   {after[2]} at {after[0]:#x}')
            print(f'  the missing declarations belong between '
                  f'{after[2]} and {first[2]} in {header}')
        else:
            print(f'  nothing agrees; the gap is above the first virtual')


if __name__ == '__main__':
    main()
