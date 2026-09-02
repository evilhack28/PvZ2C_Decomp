"""Names the function a virtual call lands on.

    python tools/vtable.py _ZTV20PlantAnimRig_Iceburg 0x118
    python tools/vtable.py _ZTV12PlantIceburg          # the whole table

A call compiled as `ldr xN, [vptr, #off]; blr xN` reaches the entry at that
byte offset in the class's vtable, which this reads out of the image.
"""

import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import config
from pvzelf import Elf


def main():
    elf = Elf(config.TARGET_LIB)

    names = {}
    for n, v, s, sh, t in elf.symbols():
        if sh and t in (1, 2):
            names.setdefault(v, set()).add(n)

    table = sys.argv[1]
    addr = None
    size = 0
    for n, v, s, sh, t in elf.symbols():
        if n == table and sh:
            addr, size = v, s
            break
    if addr is None:
        print(f'{table}: not found')
        return

    wanted = [int(a, 0) for a in sys.argv[2:]]
    print(f'{table} @ {addr:#x}, {size} bytes')
    for off in range(0, size, 8):
        if wanted and off not in wanted:
            continue
        raw = elf.read_at(addr + off, 8)
        if not raw:
            continue
        entry = int.from_bytes(raw, 'little')
        if entry == 0:
            label = '(null)'
        else:
            label = ' | '.join(sorted(names.get(entry, {f'{entry:#x}'})))
        print(f'  +{off:#05x}  slot {max(0, (off - 16) // 8):3d}  {label}')


if __name__ == '__main__':
    main()
