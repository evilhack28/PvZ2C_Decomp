"""Draft a C++ body for a game function by matching its shape (guess.py <sym> | --class <Name>)."""

import argparse
import os
import re
import struct
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from capstone import CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN, Cs

import config
import fields as fieldtool
from pvzelf import Elf

MD = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)
GREEN, YELLOW, RED, GREY, BOLD, OFF = (
    '\033[32m', '\033[33m', '\033[31m', '\033[90m', '\033[1m', '\033[0m')

LDR_SZ = {'b': 'uint8', 'h': 'uint16', 'w': 'int', 'x': 'int64', 's': 'float', 'd': 'double'}


def load_syms(elf):
    syms = {}
    for n, v, s, sh, t in elf.symbols():
        if sh and t == 2:
            syms.setdefault(v, n)
    return syms


def insns(code, addr):
    return list(MD.disasm(code, addr))


def strip_frame(ins):
    """Drop a standard prologue/epilogue so the body stands alone."""
    body = list(ins)
    while body and (
        (body[0].mnemonic == 'stp' and body[0].op_str.startswith(('x29', 'x19', 'x20', 'x21')))
        or (body[0].mnemonic == 'str' and re.match(r'x(19|2[0-8]|30)', body[0].op_str))
        or (body[0].mnemonic == 'mov' and body[0].op_str in ('x29, sp',))
        or (body[0].mnemonic == 'sub' and body[0].op_str.startswith('sp,'))):
        body.pop(0)
    while body and (
        (body[-1].mnemonic in ('ldp', 'ldr') and re.search(r'x(19|2[0-8]|29|30)', body[-1].op_str))
        or (body[-1].mnemonic == 'ret')
        or (body[-1].mnemonic == 'add' and body[-1].op_str.startswith('sp,'))):
        body.pop()
    return body


def field_map(elf, cls):
    try:
        out = {}
        found = elf.function(f'_ZN{len(cls)}{cls}15StaticClassInitEv')
        if found:
            for name, off in fieldtool.fields(elf, found[0]):
                out[off] = name
        return out
    except Exception:
        return {}


def branch_target(i):
    try:
        return int(i.op_str.lstrip('#'), 0)
    except ValueError:
        return None


def imm(text):
    """First #<number> in an operand string, or None."""
    m = re.search(r'#(0x[0-9a-fA-F]+|\d+)', text)
    return int(m.group(1), 0) if m else None


def guess(elf, syms, name):
    found = elf.function(name)
    if not found:
        return name, None, 0, 'symbol not in the library'
    addr, size, code = found
    ins = insns(code, addr)
    mnem = [i.mnemonic for i in ins]
    body = strip_frame(ins)
    bm = [i.mnemonic for i in body]

    cls = None
    m = re.match(r'_ZN?K?(\d+)([A-Za-z0-9_]+)', name)
    if m:
        n = int(m.group(1))
        cls = m.group(2)[:n] if len(m.group(2)) >= n else m.group(2)
    fields = field_map(elf, cls) if cls else {}

    def fld(off):
        return fields.get(off, f'/*+{off:#x}*/')

    # ---- empty body -------------------------------------------------------
    if mnem == ['ret']:
        return name, '{\n}', 90, 'single ret -- empty body (void)'

    # ---- constant return ------------------------------------------------
    if bm and bm[-1] == 'mov' and re.match(r'w0, #(0x)?[0-9a-f]+$', body[-1].op_str) and len(bm) == 1:
        k = int(body[-1].op_str.split('#')[1], 0)
        lit = {0: 'false', 1: 'true'}.get(k, str(k))
        return name, f'{{\n\treturn {lit};\n}}', 70, f'mov w0,#{k}; ret'

    # ---- member accessor: ldr REG,[x0,#N]; ret ------------------------
    if len(body) == 1 and body[0].mnemonic == 'ldr':
        mm = re.match(r'([wxsd])\d+, \[x0(?:, #(0x[0-9a-f]+|\d+))?\]', body[0].op_str)
        if mm:
            off = int(mm.group(2), 0) if mm.group(2) else 0
            return name, f'{{\n\treturn {fld(off)};\n}}', 75 if off in fields else 45, \
                f'ldr {mm.group(1)}0,[x0,+{off:#x}]  ({LDR_SZ.get(mm.group(1),"?")})'

    # ---- plain setter: str REG,[x0,#N]; ret --------------------------
    if len(body) == 1 and body[0].mnemonic in ('str', 'strb', 'strh'):
        mm = re.match(r'[wxsd]\d+, \[x0(?:, #\S+)?\]$', body[0].op_str)
        if mm:
            off = imm(body[0].op_str) or 0
            return name, f'{{\n\t{fld(off)} = i_arg;\n}}', 65 if off in fields else 40, \
                f'str into member +{off:#x}'

    # ---- member tail-thunk: add x0,x0,#N; b <fn> ----------------------
    if bm == ['add', 'b'] and body[0].op_str.startswith('x0, x0, #'):
        off = imm(body[0].op_str)
        tgt = syms.get(branch_target(body[1]), '?')
        conf = 45 if off in fields else 30
        if re.search(r'aSERKS0?_$', tgt):          # operator=
            return name, f'{{\n\t{fld(off)} = i_arg;\n}}', conf, \
                f'assign into member +{off:#x} (operator= on {tgt})'
        return name, f'{{\n\t// {fld(off)}.<{tgt}>(...)\n}}', conf, \
            f'tail call on member +{off:#x} -> {tgt}'

    # ---- tail flag read: ldr w0,[x0,#N]; b <TestFlag|TeamsAreOpposing> --
    if bm == ['ldr', 'b'] and re.match(r'w0, \[x0(, #\S+)?\]', body[0].op_str):
        off = imm(body[0].op_str) or 0
        tgt = syms.get(branch_target(body[1]), '?')
        conf = 60 if off in fields else 40
        if '_Z8TestFlagI' in tgt:
            return name, f'{{\n\treturn TestFlag({fld(off)}, i_arg);\n}}', conf, \
                f'read member +{off:#x}, tail TestFlag'
        return name, f'{{\n\treturn {tgt.split("E")[0]}({fld(off)}, i_arg);\n}}', conf - 10, \
            f'read member +{off:#x}, tail call {tgt}'

    # ---- flag get/set: ... TestFlag / SetFlag ------------------------
    calls = [syms.get(branch_target(i), '') for i in ins if i.mnemonic in ('b', 'bl')]
    if any('_Z8TestFlagI' in c for c in calls) and mnem[-1] == 'ret':
        offs = [imm(i.op_str) for i in ins
                if i.mnemonic == 'ldr' and re.match(r'w0, \[x0, #', i.op_str)]
        off = offs[0] if offs else None
        f = fld(off) if off is not None else '/*flag member*/'
        return name, f'{{\n\treturn TestFlag({f}, /*FLAG*/);\n}}', 50, 'reads a member, calls TestFlag'
    if any('_Z7SetFlagI' in c for c in calls):
        offs = [imm(i.op_str) for i in ins
                if i.mnemonic == 'add' and i.op_str.startswith('x0, x0, #')]
        off = offs[0] if offs else None
        f = fld(off) if off is not None else '/*flag member*/'
        bit = [imm(i.op_str) for i in ins if i.mnemonic == 'mov' and i.op_str.startswith('w1, #')]
        return name, f'{{\n\tSetFlag({f}, /*FLAG={bit}*/, i_on);\n}}', 50, 'add on member, calls SetFlag'

    # ---- single virtual call ----------------------------------------
    vslots = []
    for a, b in zip(ins, ins[1:]):
        if a.mnemonic == 'ldr' and re.search(r'x\d+, \[x\d+\]$', a.op_str) \
           and b.mnemonic == 'ldr' and '#' in b.op_str:
            mm = re.search(r'#(0x[0-9a-f]+)', b.op_str)
            if mm:
                vslots.append(int(mm.group(1), 0))
    ncalls = sum(1 for i in ins if i.mnemonic in ('bl', 'blr', 'b', 'br'))
    if len(vslots) == 1 and ncalls == 1:
        return name, f'{{\n\t// one virtual call, vtable +{vslots[0]:#x}\n' \
                     f'\t// name it:  py -3 tools/vtprobe.py {cls} {cls}.h\n}}', 35, \
               f'single virtual dispatch at vtable +{vslots[0]:#x}'

    # ---- RT_CLASS machinery ---------------------------------------
    tail = name.split(cls or '', 1)[-1] if cls else name
    rtc = {
        '9StaticNewEv': ('return new %s;' % cls, 80),
        '8IsAbstractEv': ('return false;', 80),
        '8GetClassEv': ('return StaticGetClass();', 80),
    }
    if tail in rtc:
        src, conf = rtc[tail]
        return name, f'{{\n\t{src}\n}}', conf, 'RT_CLASS_IMPLEMENT boilerplate'
    if '15StaticClassInitEv' in name:
        return name, ('{\n\tREFLECTION_CLASSBUILDER_BEGIN(%s);\n'
                      '\tREFLECTION_CLASSBUILDER_RTCLASS_BIND;\n\n'
                      '\t\tREFLECTION_CLASSBUILDER_ANCESTOR(/*base*/);\n\n'
                      '\tREFLECTION_CLASSBUILDER_END(%s);\n}' % (cls, cls)), 45, \
               'looks like StaticClassInit -- fill the ancestor / fields'

    return name, None, 0, f'{size} B, {len(ins)} insns -- no shape matched'


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('symbols', nargs='*')
    ap.add_argument('--class', dest='cls', help='guess every method this class has')
    ap.add_argument('--templates', action='store_true',
                    help='with --class, also include template instantiations')
    args = ap.parse_args()

    elf = Elf(config.TARGET_LIB)
    syms = load_syms(elf)

    targets = list(args.symbols)
    if args.cls:
        pre = (f'_ZN{len(args.cls)}{args.cls}', f'_ZNK{len(args.cls)}{args.cls}')
        cand = {n for n in syms.values() if n.startswith(pre)}
        if not args.templates:
            cand = {n for n in cand if not re.search(r'I[A-Z0-9]', n)}
        targets += sorted(cand)

    if not targets:
        ap.error('give a symbol or --class NAME')

    hi = 0
    for sym in targets:
        nm, src, conf, why = guess(elf, syms, sym)
        col = GREEN if conf >= 70 else YELLOW if conf >= 40 else GREY
        print(f'{col}{conf:3d}%{OFF}  {BOLD}{nm}{OFF}')
        print(f'      {GREY}{why}{OFF}')
        if src:
            for ln in src.splitlines():
                print(f'      {ln}')
        print()
        hi = max(hi, conf)
    return 0 if hi else 1


if __name__ == '__main__':
    sys.exit(main())
