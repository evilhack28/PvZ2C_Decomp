"""Prints the reflected fields a class registers, with their struct offsets.

    python tools/fields.py PlantIceburg

Reads the StaticClassInit the RT_CLASS macros generate, which passes the
field-registration function in x2; that function names each field with the
key it serialises under and the offset it lives at.
"""

import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from capstone import CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN, Cs

import config
from pvzelf import Elf

MD = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)


def _regfn(elf, va, size):
    pages, got = {}, None
    for i in MD.disasm(elf.data[va:va + size], va):
        if i.mnemonic == 'adrp':
            r, v = [x.strip() for x in i.op_str.split(',')]
            pages[r] = int(v.lstrip('#'), 0)
        elif i.mnemonic == 'add':
            p = [x.strip() for x in i.op_str.split(',')]
            if len(p) == 3 and p[0] == p[1] and p[0] in pages and p[2].startswith('#'):
                val = pages[p[0]] + int(p[2][1:], 0)
                if p[0] == 'x2':
                    got = val
                pages[p[0]] = val
    return got


def fields(elf, fn, limit=9000):
    out, pages, pend = [], {}, None
    for i in MD.disasm(elf.data[fn:fn + limit], fn):
        m = i.mnemonic
        if m == 'adrp':
            r, v = [x.strip() for x in i.op_str.split(',')]
            pages[r] = int(v.lstrip('#'), 0)
        elif m == 'add':
            p = [x.strip() for x in i.op_str.split(',')]
            if len(p) == 3 and p[0] == p[1] == 'x1' and p[2].startswith('#') and 'x1' in pages:
                if pend is None:
                    pend = elf.cstr(pages['x1'] + int(p[2][1:], 0))
        elif m == 'mov' and i.op_str.startswith('w3, #'):
            off = int(i.op_str.split('#')[1], 0)
            if pend is not None:
                out.append((pend, off))
                pend = None
        elif m == 'ret':
            break
    return out


def main():
    elf = Elf(config.TARGET_LIB)
    for cls in sys.argv[1:]:
        sym = f'_ZN{len(cls)}{cls}15StaticClassInitEv'
        found = elf.function(sym)
        if found is None:
            print(f'{cls}: no StaticClassInit')
            continue
        va, size, _ = found
        fn = _regfn(elf, va, size)
        if not fn:
            print(f'{cls}: StaticClassInit registers nothing ({size} bytes)')
            continue
        print(f'{cls}:')
        for key, off in fields(elf, fn):
            print(f'    {off:#6x}  {key}')


if __name__ == '__main__':
    main()
