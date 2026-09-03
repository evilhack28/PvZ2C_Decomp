"""reflect.py <Class> [--cpp] -- REFLECTION_CLASSBUILDER blocks -> C++."""

import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from capstone import CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN, Cs

import config
import ghidra
from pvzelf import Elf

MD = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)

# reflected type-string  ->  REFLECTION_CLASSBUILDER_FIELD(xType, ...)
PRIM = {'float', 'bool', 'int', 'uint', 'int32', 'uint32', 'int64', 'uint64',
        'int8', 'uint8', 'int16', 'uint16', 'double', 'pvztime_t'}


def _known_enums():
    """Set of `enum <Name>` found anywhere under include/ (for value casts)."""
    names = set()
    for root, _, files in os.walk(config.HEADERS):
        for f in files:
            if not f.endswith('.h'):
                continue
            try:
                txt = open(os.path.join(root, f), encoding='utf-8', errors='ignore').read()
            except OSError:
                continue
            names.update(re.findall(r'\benum(?:\s+class)?\s+([A-Za-z_]\w*)', txt))
    return names


def macro_for(typ, name):
    ct = re.sub(r'>>', '> >', typ)   # "vector<vector<float>>" -> "... > >"
    # RtWeakPtr/RtStrongPtr fields: use the _UNSAFE variant (keeps the exact game string)
    if re.match(r'Rt(Weak|Strong)Ptr<', typ):
        return f'\t\tREFLECTION_CLASSBUILDER_FIELD_UNSAFE({ct}, {name});'
    return f'\t\tREFLECTION_CLASSBUILDER_FIELD({ct}, {name});'


def driver_blocks(elf, cls):
    """[(regname, callback_ref_addr, sizeof), ...] from Class::StaticClassInit."""
    sym = f'_ZN{len(cls)}{cls}15StaticClassInitEv'
    found = elf.function(sym)
    if not found:
        raise SystemExit(f'{cls}: no StaticClassInit in the reference lib')
    va, size, code = found
    # AddClass(name x1, callback x2, sizeof w3, 0) -- scan for the trio
    pages, out = {}, []
    name = cb = None
    for i in MD.disasm(code, va):
        if i.mnemonic == 'adrp':
            r, v = [x.strip() for x in i.op_str.split(',')]
            pages[r] = int(v.lstrip('#'), 0)
        elif i.mnemonic == 'add':
            p = [x.strip() for x in i.op_str.split(',')]
            if len(p) == 3 and p[0] == p[1] and p[0] in pages and p[2].startswith('#'):
                t = pages[p[0]] + int(p[2][1:], 0)
                s = elf.cstr(t)
                if p[0] == 'x1' and s:
                    name = s
                elif p[0] == 'x2':
                    cb = t
                pages[p[0]] = t
        elif i.mnemonic == 'mov' and re.match(r'w3, #', i.op_str):
            sz = int(i.op_str.split('#')[1], 0)
            if name and cb:
                out.append((name, cb, sz))
            name = cb = None
    return out, size


def driver_enums(elf, cls):
    """[(enumname, [(member, value), ...]), ...] -- the ENUMBUILDER blocks."""
    va, size, code = elf.function(f'_ZN{len(cls)}{cls}15StaticClassInitEv')
    syms = {v: n for n, v, s, sh, t in elf.symbols() if sh and t == 2}
    pages, regstr = {}, {}      # reg -> page addr / reg -> string it points at
    pend_imm = {}              # reg -> last immediate moved into it
    last_str = None            # most recent string materialised
    val = None                # value stored to the pair's value slot
    members, out = [], []
    for i in MD.disasm(code, va):
        m, ops = i.mnemonic, i.op_str
        if m == 'adrp':
            r, v = [x.strip() for x in ops.split(',')]
            pages[r] = int(v.lstrip('#'), 0)
        elif m == 'add':
            p = [x.strip() for x in ops.split(',')]
            if len(p) == 3 and p[1] in pages and p[2].startswith('#'):
                t = pages[p[1]] + int(p[2][1:], 0)
                pages[p[0]] = t
                s = elf.cstr(t)
                if s is not None:
                    regstr[p[0]] = s
                    last_str = s
        elif m == 'mov':
            p = [x.strip() for x in ops.split(',')]
            if len(p) == 2 and p[1].startswith('#'):
                try:
                    pend_imm[p[0]] = int(p[1][1:], 0)
                except ValueError:
                    pass
            elif len(p) == 2 and p[1] in regstr:
                regstr[p[0]] = regstr[p[1]]
        elif m == 'str':
            p = [x.strip() for x in ops.split(',', 1)]
            if p[0] == 'wzr':
                val = 0
            elif p[0] in pend_imm:
                val = pend_imm[p[0]]
        elif m in ('bl', 'blr'):
            nm = ''
            if m == 'bl' and ops.startswith('#'):
                nm = syms.get(int(ops[1:], 0), '')
            if re.search(r'St4pairISsjEC[12]', nm):   # DEnumMemberPair(string,uint) ctor
                members.append((last_str, val))
                val = None
            elif 'AddEnum' in nm or (m == 'blr' and len(members) >= 2):
                out.append((last_str, members))
                members = []
                last_str = None                       # don't let the name leak in
    if members:
        out.append((last_str, members))
    return out


STR = re.compile(r'FUN_054763d4\(&?\w+,"([^"]*)"\)')
SLOTDEF = re.compile(r'(\w+) = \*\(code \*\*\)\(\*\(long \*\)param_1 \+ (0x[0-9a-f]+)\)')
# builder call: (*pcVarN)(...NAME,OFF) or (**(...param_1 + 0xNN))(...OFF)
CALL = re.compile(
    r'(?:\(\*(?P<var>\w+)\)|\+ (?P<slot>0x[0-9a-f]+)\)\))'
    r'\(param_1,param_2,\s*&?\w+,\s*(?P<off>[^,)]+)')


def parse_callback(text):
    """[('ancestor', name) | ('field', name, type, off) | ('method', name, argtype)]."""
    entries = []
    strs = []            # string literals since the last builder call
    slot = {}            # pcVarN -> vtable offset it was loaded from
    for ln in text.splitlines():
        l = ln.strip()
        for m in SLOTDEF.finditer(l):
            slot[m.group(1)] = int(m.group(2), 0)
        for s in STR.findall(l):
            strs.append(s)
        m = CALL.search(l)
        if not m:
            continue
        s = slot.get(m.group('var')) if m.group('var') else int(m.group('slot'), 0)
        off = m.group('off').strip()
        try:
            off = int(off, 0)
        except ValueError:
            pass
        names = [x for x in strs if x]          # drop the "" fillers methods pass
        if s == 0x50:                           # BuildAncestor
            if names:
                entries.append(('ancestor', names[0]))
        elif s == 0x68:                         # BuildMethod
            entries.append(('method', names[0] if names else '?',
                            names[1] if len(names) > 1 else None))
        else:                                   # BuildField (slot 0x58)
            entries.append(('field', names[0] if names else '?',
                            names[1] if len(names) > 1 else None, off))
        strs = []
    return entries


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    cpp = '--cpp' in sys.argv
    if not args:
        raise SystemExit('usage: python tools/reflect.py <Class> [--cpp]')
    cls = args[0]
    elf = Elf(config.TARGET_LIB)
    enums = driver_enums(elf, cls)
    blocks, _ = driver_blocks(elf, cls)
    if not blocks and not enums:
        raise SystemExit(f'{cls}: StaticClassInit registers nothing')

    # one Ghidra run for every callback
    dump = ghidra.decompile(*[f'{cb:x}' for _, cb, _ in blocks]) if blocks else ''

    if cpp:
        print(f'void {cls}::StaticClassInit()\n{{')
    # enum builders come first in the source
    enum_types = _known_enums()
    for ename, members in enums:
        if cpp:
            # cast values to an enum type so DEnumMemberPair's ctor matches MEMBER_RENAME
            cast = ename if ename in enum_types else None
            print(f'\tREFLECTION_ENUMBUILDER_BEGIN({ename});')
            for mname, mval in members:
                v = f'({cast}){mval}' if cast else str(mval)
                print(f'\t\tREFLECTION_ENUMBUILDER_MEMBER_RENAME({mname}, {v});')
            print(f'\tREFLECTION_ENUMBUILDER_END({ename});'
                  + ('' if cast else '   // TODO cast value to the real enum') + '\n')
        else:
            print(f'== enum {ename}  ({len(members)} members)')
            for mname, mval in members:
                print(f'   {mval:>6}  {mname}')
            print()
    for regname, cb, sz in blocks:
        sec = ghidra.function(dump, f'{cb + config.GHIDRA_ADDR_BIAS:x}') or \
              ghidra.function(dump, 'FUN_%08x' % (cb + config.GHIDRA_ADDR_BIAS)) or dump
        ents = parse_callback(sec)
        rtclass = regname == cls
        if cpp:
            print(f'\tREFLECTION_CLASSBUILDER_BEGIN({regname});')
            if rtclass:
                print('\tREFLECTION_CLASSBUILDER_RTCLASS_BIND;\n')
            for e in ents:
                if e[0] == 'ancestor':
                    print(f'\t\tREFLECTION_CLASSBUILDER_ANCESTOR({e[1]});\n')
                elif e[0] == 'field':
                    print(macro_for(e[2] or '???', e[1]))
                elif e[0] == 'method':
                    a = e[2]
                    if a:
                        print(f'\t\tREFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_ONEARG'
                              f'({e[1]}, {e[1]}, {a});')
                    else:
                        print(f'\t\tREFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_NOARGS'
                              f'({e[1]}, {e[1]});')
            print(f'\tREFLECTION_CLASSBUILDER_END({regname});\n')
        else:
            print(f'== {regname}  (sizeof {sz:#x}, callback {cb:#x}, {len(ents)} entries)')
            for e in ents:
                if e[0] == 'field':
                    o = e[3] if isinstance(e[3], str) else f'{e[3]:#x}'
                    print(f'   {o:>7}  {e[2] or "?":<34} {e[1]}')
                elif e[0] == 'method':
                    print(f'   method   {e[2] or "()":<34} {e[1]}')
            print()
    if cpp:
        print('}')


if __name__ == '__main__':
    main()
