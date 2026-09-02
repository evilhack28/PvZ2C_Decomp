"""Annotated disassembly: says what every constant actually is.

    python tools/explain.py _ZN12PlantIceburg4IdleEv
    python tools/explain.py _ZN12PlantIceburg4IdleEv --this PlantIceburg

Resolves, inline:
  - string literals
  - floats in the literal pool
  - member offsets, from the reflected field table of the class named by
    --this and of any class whose fields are already known
  - unnamed local clones (.isra/.part), by disassembling their one-line body
  - vtable offsets, printed as `vtable+0xNN` so slotprobe.py can name them
"""

import argparse
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from capstone import CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN, Cs

import config
import fields as fieldtool
from pvzelf import Elf

MD = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)
GREY, CYAN, OFF = '\033[90m', '\033[36m', '\033[0m'


def field_table(elf, classes):
    """{offset: name} merged over several classes."""
    out = {}
    for cls in classes:
        sym = f'_ZN{len(cls)}{cls}15StaticClassInitEv'
        found = elf.function(sym)
        if found is None:
            continue
        va, size, _ = found
        fn = fieldtool._regfn(elf, va, size)
        if not fn:
            continue
        for name, off in fieldtool.fields(elf, fn):
            if name and name[0].islower() or name.startswith('m_'):
                out.setdefault(off, name)
    return out


def clone_body(elf, addr, names):
    """A one-line summary of an unnamed local clone."""
    raw = elf.read_at(addr, 32)
    if not raw:
        return None
    parts = []
    for ins in MD.disasm(raw, addr):
        if ins.mnemonic in ('b', 'bl'):
            t = int(ins.op_str.lstrip('#'), 0)
            parts.append(f'-> {names.get(t, hex(t))}')
            break
        parts.append(f'{ins.mnemonic} {ins.op_str}')
        if ins.mnemonic == 'ret':
            break
        if len(parts) >= 4:
            parts.append('...')
            break
    return '; '.join(parts)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('symbol')
    ap.add_argument('--this', action='append', default=[],
                    help='class whose member offsets should be named')
    args = ap.parse_args()

    elf = Elf(config.TARGET_LIB)
    names = {}
    for n, v, s, sh, t in elf.symbols():
        if sh and t == 2:
            names.setdefault(v, n)

    # Always try to name members of the class the symbol belongs to.
    owner = re.match(r'^_ZNK?\d+(\w+?)\d+[A-Za-z_]', args.symbol)
    classes = list(args.this)
    if owner and owner.group(1) not in classes:
        classes.append(owner.group(1))
    classes += ['Plant', 'BoardEntity']
    members = field_table(elf, classes)

    found = elf.function(args.symbol)
    if found is None:
        print(f'{args.symbol}: not found')
        return
    addr, size, code = found
    print(f'=== {args.symbol}  {size} bytes @ {addr:#x}')
    print(f'    members named from: {", ".join(classes)}')

    pages = {}
    for ins in MD.disasm(code, addr):
        note = ''
        m, ops = ins.mnemonic, ins.op_str

        if m == 'adrp':
            r, v = [x.strip() for x in ops.split(',')]
            pages[r] = int(v.lstrip('#'), 0)

        elif m == 'add':
            p = [x.strip() for x in ops.split(',')]
            if len(p) == 3 and p[0] == p[1] and p[1] in pages and p[2].startswith('#'):
                target = pages[p[1]] + int(p[2][1:], 0)
                text = elf.cstr(target)
                if text and text.isprintable() and 0 < len(text) < 70:
                    note = f'   "{text}"'
                elif target in names:
                    note = f'   {names[target]}'
                else:
                    note = f'   data {target:#x}'

        elif m in ('ldr', 'ldrb', 'ldrsw', 'str', 'strb') and '[' in ops:
            inner = ops[ops.index('[') + 1:ops.rindex(']')]
            parts = [x.strip() for x in inner.split(',')]
            if len(parts) > 1 and parts[1].startswith('#'):
                off = int(parts[1][1:], 0)
                if off in members:
                    note = f'   {members[off]}'
                elif off >= 0x10:
                    note = f'   vtable+{off:#x}' if parts[0] != 'sp' else ''

        elif m == 'ldr' and '#0x' in ops and '[' not in ops:
            reg, imm = [x.strip() for x in ops.split(',', 1)]
            target = int(imm.lstrip('#'), 0)
            raw = elf.read_at(target, 8)
            if raw:
                if reg[0] == 's':
                    note = f'   = {struct.unpack("<f", raw[:4])[0]}f'
                elif reg[0] == 'd':
                    note = f'   = {struct.unpack("<d", raw)[0]}'
                else:
                    note = f'   = {int.from_bytes(raw, "little"):#x}'

        elif m in ('b', 'bl'):
            t = int(ops.lstrip('#'), 0)
            if t in names:
                note = f'   {names[t]}'
            else:
                body = clone_body(elf, t, names)
                note = f'   {CYAN}[local clone]{OFF} {body}' if body else f'   {t:#x}'

        elif m in ('mov', 'movz') and '#' in ops:
            try:
                v = int(ops.split('#')[1], 0)
                if 0x20 < v < 0x7fffffff:
                    note = f'   {GREY}({v}){OFF}'
            except (ValueError, IndexError):
                pass

        print(f'  {ins.address:#x}  {m:<10s} {ops}{note}')


if __name__ == '__main__':
    main()
