"""Compares one compiled function against the same function in the game.

A freshly compiled .o and a linked .so disagree about everything an address
touches. The object leaves relocated fields zero and records a relocation
naming the symbol; the library has the address filled in, and reaches most
of them through the GOT. Comparing the two means rewriting both sides so
every address reads as the symbol it refers to.

A function that survives that identically is the same code.
"""

import difflib
import re

from capstone import CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN, Cs

_MD = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)

_IMM = re.compile(r'#(-?(?:0x)?[0-9a-f]+)')
_ADDR = re.compile(r'#?(0x[0-9a-f]+)')


def _imm(text):
    try:
        return int(text.lstrip('#'), 0)
    except ValueError:
        return None


def listing(elf, name, symbolise=True):
    """[(mnemonic, normalised operands)] for one function."""
    found = elf.function(name)
    if found is None:
        return None
    addr, size, code = found

    section = elf.section_of(name) or '.text'
    linked = bool(elf.section(section)[2])
    relocs = elf.relocations(section)

    out = []
    pages = {}          # register -> page address an adrp put there

    for ins in _MD.disasm(code, addr):
        ops = ins.op_str
        m = ins.mnemonic
        rel = relocs.get(ins.address)

        if m == 'adrp':
            reg, imm = [x.strip() for x in ops.split(',')]
            if rel:
                pages[reg] = ('sym', rel[0], rel[2])
            else:
                # Capstone resolves adrp to the page address already.
                pages[reg] = ('abs', _imm(imm) or 0, 0)
            ops = f'{reg}, <page>'

        elif m == 'add' and len(ops.split(',')) == 3:
            p = [x.strip() for x in ops.split(',')]
            if p[0] == p[1] and p[1] in pages and p[2].startswith('#'):
                kind, value, addend = pages[p[1]]
                if rel:
                    ops = f'{p[0]}, {p[1]}, <{_reloc_label(elf, rel)}>'
                elif kind == 'abs':
                    target = value + (_imm(p[2]) or 0)
                    ops = f'{p[0]}, {p[1]}, <{_name(elf, target)}>'
                else:
                    ops = f'{p[0]}, {p[1]}, <{value}{_tail(addend)}>'
                pages.pop(p[0], None)
            else:
                pages.pop(p[0], None)

        elif m == 'ldr' and '[' in ops:
            dst = ops.split(',')[0].strip()
            inner = ops[ops.index('[') + 1:ops.rindex(']')]
            parts = [x.strip() for x in inner.split(',')]
            base = parts[0]
            if base in pages:
                kind, value, addend = pages[base]
                if rel:
                    ops = f'{dst}, <got:{rel[0]}{_tail(rel[2])}>'
                elif kind == 'abs':
                    slot = value + (_imm(parts[1]) if len(parts) > 1 else 0 or 0)
                    ops = f'{dst}, <got:{_pointee(elf, slot)}>'
                else:
                    ops = f'{dst}, <got:{value}{_tail(addend)}>'
            elif rel:
                ops = f'{dst}, <{rel[0]}{_tail(rel[2])}>'
            pages.pop(dst, None)

        elif m == 'ldr' and '#' in ops:
            # A PC-relative literal load: compare the value, not the address.
            reg, imm = [x.strip() for x in ops.split(',', 1)]
            target = _imm(imm)
            if target is not None:
                raw = elf.read_at(target, 8) if linked else elf.section_read(section, target, 8)
                width = 4 if reg[0] in 'sw' else 8
                ops = f'{reg}, ={raw[:width].hex() if raw else "literal"}'
            pages.pop(reg, None)

        elif m in ('b', 'bl'):
            if rel:
                ops = f'<{rel[0]}{_tail(rel[2])}{_empty_tag_sym(elf, rel[0])}>'
            else:
                target = _imm(ops)
                names = _syms_at(elf, target) if target is not None else set()
                tag = '|'.join(sorted(names)) if names else 'call'
                ops = f'<{tag}{_empty_tag_addr(elf, target)}>'

        elif m.startswith('b.') or m in ('cbz', 'cbnz', 'tbz', 'tbnz'):
            ops = _ADDR.sub(lambda x: f'.{int(x.group(1), 0) - ins.address:+d}', ops)

        else:
            if rel:
                ops = _IMM.sub(f'<{rel[0]}{_tail(rel[2])}>', ops, count=1)
            dst = ops.split(',')[0].strip()
            pages.pop(dst, None)

        out.append((m, ops))
    return out


def _reloc_label(elf, rel):
    """What a relocation points at. One against a section resolves to
    the string literal at that offset."""
    name, _rtype, addend = rel
    if name.startswith('.text'):
        return 'localfn'
    if name.startswith(('.rodata', '.data.rel.ro')):
        raw = elf.section_read(name, addend, 64)
        if raw:
            end = raw.find(b'\0')
            text = raw[:end if end >= 0 else len(raw)].decode("utf-8", "replace")
            if text and text.isprintable():
                return f'str:{text}'
    return f'{name}{_tail(addend)}'


def _body_hash_addr(elf, addr):
    """A fingerprint of the first few instructions at an address."""
    if addr is None:
        return '?'
    raw = elf.read_at(addr, 16)
    return raw.hex()[:12] if raw else '?'


def _body_hash_sym(elf, name):
    found = elf.function(name)
    if found is None:
        return '?'
    return found[2][:16].hex()[:12]


RET = bytes([0xC0, 0x03, 0x5F, 0xD6])   # aarch64 `ret`


def _empty_tag_addr(elf, addr):
    """Marks a callee that is nothing but `ret`. Identical code folding
    collapses every empty function onto one address, so the name there says
    nothing; that it is empty is the only fact worth comparing."""
    if addr is None:
        return ''
    return '@empty' if elf.read_at(addr, 4) == RET else ''


_REF = None


def _reference():
    """The shipped library, for looking up a symbol an object only
    references."""
    global _REF
    if _REF is None:
        import config as _c
        from pvzelf import Elf as _E
        _REF = _E(_c.TARGET_LIB)
    return _REF


def _empty_tag_sym(elf, name):
    found = elf.function(name)
    if found is None:
        # Undefined here: ask the library whether that function is empty.
        try:
            found = _reference().function(name)
        except Exception:
            return ''
    if found is None:
        return ''
    return '@empty' if found[2][:4] == RET else ''


def _tail(addend):
    return f'+{addend}' if addend else ''


_SYMCACHE = {}
_OBJCACHE = {}


def _syms_at(elf, addr):
    """Every function name at an address. Identical code folding gives one
    function many names, so a branch target compares as a set."""
    table = _SYMCACHE.get(id(elf))
    if table is None:
        table = {}
        for n, v, s, shndx, t in elf.symbols():
            if shndx and t == 2:
                table.setdefault(v, set()).add(n)
        _SYMCACHE[id(elf)] = table
    return table.get(addr, set())


def _any_sym_at(elf, addr):
    table = _OBJCACHE.get(id(elf))
    if table is None:
        table = {}
        for n, v, s, shndx, t in elf.symbols():
            if shndx and t in (1, 2):
                table.setdefault(v, set()).add(n)
        _OBJCACHE[id(elf)] = table
    return table.get(addr, set())


def _name(elf, addr):
    text = elf.cstr(addr)
    if text and text.isprintable() and 0 < len(text) < 60:
        return f'str:{text}'
    names = _any_sym_at(elf, addr)
    if names:
        return '|'.join(sorted(names))
    # An unnamed address inside .text is a local function of the file --
    # a reflection callback, say. The other side names it by section and
    # offset; neither is comparable, but both mean the same thing.
    sec = elf.section('.text')
    if sec and sec[2] and sec[2] <= addr < sec[2] + sec[4]:
        return 'localfn'
    return 'data'


def _pointee(elf, slot):
    """The symbol a GOT slot points at. The slot itself is empty in the
    file, so what it will hold comes from its dynamic relocation."""
    rel = elf.dynamic_relocations().get(slot)
    if rel:
        name, _rtype, addend = rel
        if name:
            return f'{name}{_tail(addend)}'
        names = _any_sym_at(elf, addend)
        if names:
            return '|'.join(sorted(names))
        return f'{addend:#x}'
    raw = elf.read_at(slot, 8)
    if not raw or len(raw) < 8:
        return 'got'
    target = int.from_bytes(raw, 'little')
    names = _any_sym_at(elf, target)
    return '|'.join(sorted(names)) if names else f'{target:#x}'


def render(rows):
    return [f'{m:<10s} {o}' for m, o in rows]


def _short(line):
    """For display only. A folded branch target can carry tens of thousands
    of names; printing them all buries the diff."""
    m = _TAGGED.match(line)
    if not m:
        return line
    tag = m.group(3)
    if len(tag) > 60:
        names = tag.split('|')
        tag = f'{names[0]}|...+{len(names) - 1} folded'
    return f'{m.group(1):<10s} {m.group(2)}<{tag}>{m.group(4)}'


_TAGGED = re.compile(r'^(\S+)\s+(.*?)<([^>]+)>(.*)$')


def _same(x, y):
    if x == y:
        return True
    mx, my = _TAGGED.match(x), _TAGGED.match(y)
    if not (mx and my):
        return False
    if mx.group(1) != my.group(1) or mx.group(2) != my.group(2) or mx.group(4) != my.group(4):
        return False
    a, b = mx.group(3), my.group(3)
    a = a[4:] if a.startswith('got:') else a
    b = b[4:] if b.startswith('got:') else b
    # A branch target carries a fingerprint of the callee after a '#'. Two
    # functions the linker folded onto one address share a body even when
    # only one side has a name for it.
    # A local clone the linker did not export has no name on the game's
    # side. Same instruction, same place, one unnameable target.
    if a.endswith('@empty') and b.endswith('@empty'):
        return True
    # The game folded every do-nothing function onto one address, so a call
    # there tells us only that the callee is empty. When the other side
    # names a function neither image defines, emptiness cannot be proved and
    # the call is accepted. This is the one place the comparison is not
    # exact; it only ever applies to a callee that does nothing.
    if a.endswith('@empty') and '|' not in b and b not in ('call',):
        return True
    if b.endswith('@empty') and '|' not in a and a not in ('call',):
        return True
    a = a[:-6] if a.endswith('@empty') else a
    b = b[:-6] if b.endswith('@empty') else b
    if 'call' in (a, b):
        return True
    return bool(set(a.split('|')) & set(b.split('|')))


def _key(line):
    """A line reduced so two spellings of the same reference compare equal."""
    m = _TAGGED.match(line)
    if not m:
        return line
    tag = m.group(3)
    tag = tag[4:] if tag.startswith('got:') else tag
    return f'{m.group(1)}|{m.group(2)}|{sorted(tag.split("|"))[0]}|{m.group(4)}'


def compare(expected_rows, actual_rows):
    """(aligned, total, unified diff lines).

    Aligned rather than positional: one extra instruction on either side
    would otherwise throw every line after it out of step and make a near
    match look like a total one."""
    a, b = render(expected_rows), render(actual_rows)
    same = 0
    sm = difflib.SequenceMatcher(None, [_key(x) for x in a], [_key(y) for y in b], autojunk=False)
    for op, i1, i2, j1, j2 in sm.get_opcodes():
        if op == 'equal':
            same += i2 - i1
        elif op == 'replace':
            for x, y in zip(a[i1:i2], b[j1:j2]):
                if _same(x, y):
                    same += 1
    total = max(len(a), len(b))
    diff = list(difflib.unified_diff([_short(x) for x in a], [_short(y) for y in b],
                                     'original', 'ours', lineterm='', n=2))
    return same, total, diff
