"""Finds which method name compiles to a given vtable offset.

Identical code folding means a vtable entry usually carries the name of some
unrelated trivial function, so reading the table backwards does not name the
method a call site meant. This goes the other way: it compiles a call to
each candidate and reports the offset the compiler emitted.

    python tools/slotprobe.py PlantFramework PlantFramework.h            # all
    python tools/slotprobe.py PlantFramework PlantFramework.h 0x190      # one
    python tools/slotprobe.py PlantAnimRig PlantAnimRig.h PlayIdleLooped

With no third argument every no-argument virtual in the header is probed.
A bare hex number filters the output to that offset.

All candidates go into one translation unit, so this costs one compile.
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


def candidates_from(header):
    """Every no-argument virtual method declared in a header."""
    path = os.path.join(config.HEADERS, 'PvZ', header)
    if not os.path.exists(path):
        for root, _d, files in os.walk(config.HEADERS):
            if header in files:
                path = os.path.join(root, header)
                break
    text = open(path, encoding='utf-8', errors='replace').read()
    names = []
    for line in text.splitlines():
        if 'virtual' not in line:
            continue
        m = re.search(r'\b([A-Za-z_]\w*)\s*\(\s*\)', line)
        if m and m.group(1) not in ('virtual', 'if', 'return'):
            names.append(m.group(1))
    return sorted(set(names))


def probe(cls, header, methods):
    src = os.path.join(config.BUILD, 'slotprobe.cpp')
    obj = os.path.join(config.BUILD, 'slotprobe.o')
    good = list(methods)

    # Anything that does not compile is dropped and the rest retried, so one
    # bad candidate cannot cost a whole run.
    for _round in range(6):
        with open(src, 'w') as f:
            f.write('#define private public\n#define protected public\n')
            f.write(f'#include "{header}"\n')
            for i, m in enumerate(good):
                f.write(f'void probe_{i}_{m}({cls}* p) {{ p->{m}(); }}\n')
        done = subprocess.run([config.GXX, *config.CXXFLAGS, '-c', src, '-o', obj],
                              capture_output=True, text=True)
        if done.returncode == 0:
            break
        bad = set()
        for line in done.stderr.splitlines():
            m = re.search(r'probe_(\d+)_', line)
            if m:
                bad.add(int(m.group(1)))
        if not bad:
            print('probe failed:')
            for line in [l for l in done.stderr.splitlines() if ' error: ' in l][:5]:
                print('  ', line[:180])
            return []
        good = [m for i, m in enumerate(good) if i not in bad]
    else:
        return []

    elf = Elf(obj)
    out = []
    for n, v, s, sh, t in elf.symbols():
        if not (sh and t == 2 and n.startswith('_Z') and 'probe_' in n):
            continue
        m = re.search(r'probe_(\d+)_(\w+?)P\d', n)
        if not m:
            continue
        name = m.group(2)
        found = elf.function(n)
        if not found:
            continue
        addr, size, code = found
        for ins in MD.disasm(code, addr):
            if ins.mnemonic == 'ldr' and '[' in ins.op_str and '#' in ins.op_str:
                hit = re.search(r'#(0x[0-9a-f]+)', ins.op_str)
                if hit and int(hit.group(1), 0) >= 0x10:
                    out.append((int(hit.group(1), 0), name))
                    break
    return sorted(set(out))


def main():
    cls = sys.argv[1]
    header = sys.argv[2]
    rest = sys.argv[3:]

    want = None
    methods = []
    for a in rest:
        if a.startswith('0x'):
            want = int(a, 0)
        else:
            methods.append(a)
    if not methods:
        methods = candidates_from(header)

    for off, name in probe(cls, header, methods):
        if want is None or off == want:
            print(f'  {off:#06x}  {name}')


if __name__ == '__main__':
    main()
