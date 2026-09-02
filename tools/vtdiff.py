"""Compares a class's vtable in our build against the game's.

    python tools/vtdiff.py PlantIceburg build/Plant_Iceburg.o

A vtable that is short by N slots means the headers are missing N virtual
declarations, and every virtual call above the gap resolves to the wrong
function. Finding where the two tables stop agreeing says where the missing
declarations belong.

Our side reads the vtable's relocations, which name each entry directly.
The game's side reads the addresses and looks them up.
"""

import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import config
from pvzelf import Elf


def game_entries(elf, table):
    addr = size = None
    for n, v, s, sh, t in elf.symbols():
        if n == table and sh:
            addr, size = v, s
            break
    if addr is None:
        return None
    names = {}
    for n, v, s, sh, t in elf.symbols():
        if sh and t == 2:
            names.setdefault(v, set()).add(n)
    out = []
    for off in range(16, size, 8):
        raw = elf.read_at(addr + off, 8)
        if not raw:
            break
        e = int.from_bytes(raw, 'little')
        out.append(sorted(names.get(e, {f'{e:#x}'})))
    return out


def our_entries(elf, table):
    addr = size = shndx = None
    for n, v, s, sh, t in elf.symbols():
        if n == table and sh:
            addr, size, shndx = v, s, sh
            break
    if addr is None or not size:
        return None
    section = elf._sh[shndx][-1]
    relocs = elf.relocations(section)
    out = []
    for off in range(16, size, 8):
        rel = relocs.get(addr + off)
        out.append([rel[0]] if rel else ['(null)'])
    return out


def main():
    cls = sys.argv[1]
    obj = sys.argv[2]
    table = f'_ZTV{len(cls)}{cls}'

    game = game_entries(Elf(config.TARGET_LIB), table)
    ours = our_entries(Elf(obj), table)
    if game is None:
        print(f'{table}: not in the game')
        return
    if ours is None:
        print(f'{table}: not emitted by {obj}')
        return

    print(f'{table}: game {len(game)} slots, ours {len(ours)} slots '
          f'({len(game) - len(ours):+d})')
    print()
    shown = 0
    for i in range(max(len(game), len(ours))):
        g = game[i] if i < len(game) else None
        o = ours[i] if i < len(ours) else None
        if g and o and set(g) & set(o):
            continue
        gs = '|'.join(g)[:56] if g else '(past end)'
        os_ = '|'.join(o)[:56] if o else '(past end)'
        print(f'  slot {i:3d} (+{16 + i * 8:#05x})')
        print(f'     game | {gs}')
        print(f'     ours | {os_}')
        shown += 1
        if shown >= 20:
            print('  ...')
            break
    if not shown:
        print('  every slot agrees')


if __name__ == '__main__':
    main()
