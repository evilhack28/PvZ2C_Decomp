"""Disassembles one function out of the game, with symbols and strings named.

    python tools/dis.py _ZN12PlantIceburg9HasShadowEv
"""

import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from capstone import CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN, Cs

import config
from pvzelf import Elf

MD = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)


def main():
    elf = Elf(config.TARGET_LIB)
    syms = {}
    for n, v, s, sh, t in elf.symbols():
        if sh and t == 2:
            syms.setdefault(v, n)

    for name in sys.argv[1:]:
        found = elf.function(name)
        if found is None:
            print(f'{name}: not found')
            continue
        addr, size, code = found
        print(f'=== {name}  {size} bytes @ {addr:#x}')
        pages = {}
        for i in MD.disasm(code, addr):
            note = ''
            if i.mnemonic == 'adrp':
                r, v = [x.strip() for x in i.op_str.split(',')]
                pages[r] = (i.address & ~0xFFF) + int(v.lstrip('#'), 0)
            elif i.mnemonic == 'add':
                p = [x.strip() for x in i.op_str.split(',')]
                if len(p) == 3 and p[0] == p[1] and p[0] in pages and p[2].startswith('#'):
                    target = pages[p[0]] + int(p[2][1:], 0)
                    text = elf.cstr(target)
                    label = syms.get(target)
                    if text and text.isprintable() and 0 < len(text) < 60:
                        note = f'   ; "{text}"'
                    elif label:
                        note = f'   ; {label}'
                    else:
                        note = f'   ; {target:#x}'
                    pages[p[0]] = target
            elif i.mnemonic in ('bl', 'b'):
                try:
                    t = int(i.op_str.lstrip('#'), 0)
                    if t in syms:
                        note = f'   ; {syms[t]}'
                except ValueError:
                    pass
            print(f'  {i.address:#x}  {i.mnemonic:<10s} {i.op_str}{note}')
        print()


if __name__ == '__main__':
    main()
