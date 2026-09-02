"""Names the vtable offset a virtual call compiles to, for calls with arguments.

`slotprobe.py` enumerates a header's no-argument virtuals automatically. A
virtual that takes arguments cannot be called from a generated stub without
knowing its parameter types, so those are written by hand here:

    python tools/exprprobe.py Zombie.h \
        'Zombie* z, const DamageInfo& d' 'z->TakeDamage(d)' \
        'Zombie* z, bool b'              'z->SnapToGround(b)'

Arguments come in pairs: a parameter list, then the call to make with it.
Each pair becomes one function in a single translation unit, and the first
`ldr` from a vptr in the compiled body is the offset.

The offset printed is what a call site's `[x8, #N]` will read, so it is
directly comparable to a disassembled call in the game.
"""

import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from capstone import CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN, Cs

import config
from pvzelf import Elf

MD = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)


def probe(headers, pairs):
    src = os.path.join(config.BUILD, 'exprprobe.cpp')
    obj = os.path.join(config.BUILD, 'exprprobe.o')
    with open(src, 'w') as f:
        f.write('#define private public\n#define protected public\n')
        for h in headers:
            f.write(f'#include "{h}"\n')
        for i, (params, call) in enumerate(pairs):
            f.write(f'void probe_{i}({params}) {{ (void)({call}); }}\n')

    done = subprocess.run([config.GXX, *config.CXXFLAGS, '-c', src, '-o', obj],
                          capture_output=True, text=True)
    if done.returncode != 0:
        for line in [l for l in done.stderr.splitlines() if ' error: ' in l][:8]:
            print('  ', line[:200])
        return []

    elf = Elf(obj)
    out = []
    for n, v, s, sh, t in elf.symbols():
        m = re.match(r'_Z7probe_(\d+)', n)
        if not (sh and t == 2 and m):
            continue
        found = elf.function(n)
        if not found:
            continue
        addr, size, code = found
        for ins in MD.disasm(code, addr):
            if ins.mnemonic == 'ldr' and '[' in ins.op_str and '#' in ins.op_str:
                hit = re.search(r'#(0x[0-9a-f]+)', ins.op_str)
                if hit and int(hit.group(1), 0) >= 0x10:
                    out.append((int(m.group(1)), int(hit.group(1), 0)))
                    break
        else:
            out.append((int(m.group(1)), None))
    return sorted(out)


def main():
    args = sys.argv[1:]
    headers = []
    while args and args[0].endswith('.h'):
        headers.append(args.pop(0))
    pairs = list(zip(args[0::2], args[1::2]))
    for i, off in probe(headers, pairs):
        shown = f'{off:#06x}' if off is not None else 'not virtual'
        print(f'  {shown}  {pairs[i][1]}')


if __name__ == '__main__':
    main()
