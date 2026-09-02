"""Minimal ELF reader: sections, symbols, relocations, and function bytes.

Handles both the 32-bit and 64-bit game libraries and the relocatable .o
files the toolchain produces, because the differ needs to read a function
out of either one.
"""

import struct


class Elf:
    def __init__(self, path):
        self.path = path
        self.data = open(path, 'rb').read()
        d = self.data
        if d[:4] != b'\x7fELF':
            raise ValueError(f'{path}: not an ELF')
        self.is64 = d[4] == 2
        self.machine = struct.unpack('<H', d[18:20])[0]

        if self.is64:
            shoff = struct.unpack('<Q', d[0x28:0x30])[0]
            shentsize = struct.unpack('<H', d[0x3A:0x3C])[0]
            shnum = struct.unpack('<H', d[0x3C:0x3E])[0]
            shstrndx = struct.unpack('<H', d[0x3E:0x40])[0]
        else:
            shoff = struct.unpack('<I', d[0x20:0x24])[0]
            shentsize = struct.unpack('<H', d[0x2E:0x30])[0]
            shnum = struct.unpack('<H', d[0x30:0x32])[0]
            shstrndx = struct.unpack('<H', d[0x32:0x34])[0]

        raw = d[shoff:shoff + shentsize * shnum]
        self._sh = []
        for i in range(shnum):
            o = i * shentsize
            b = raw[o:o + shentsize]
            name, stype = struct.unpack('<II', b[0:8])
            if self.is64:
                addr, off, size = struct.unpack('<QQQ', b[0x10:0x28])
                link, = struct.unpack('<I', b[0x28:0x2C])
                entsize, = struct.unpack('<Q', b[0x38:0x40])
            else:
                addr, off, size = struct.unpack('<III', b[0x0C:0x18])
                link, = struct.unpack('<I', b[0x18:0x1C])
                entsize, = struct.unpack('<I', b[0x24:0x28])
            self._sh.append([name, stype, addr, off, size, link, entsize])

        shstr = self._sh[shstrndx]
        st = d[shstr[3]:shstr[3] + shstr[4]]
        self.sections = {}
        for i, s in enumerate(self._sh):
            nm = st[s[0]:st.index(b'\0', s[0])].decode()
            s.append(nm)
            self.sections[nm] = i

    # ── sections ─────────────────────────────────────────────────────────

    def section(self, name):
        i = self.sections.get(name)
        return None if i is None else self._sh[i]

    def section_read(self, section_name, addr, n):
        """n bytes at an offset inside a named section."""
        s = self.section(section_name)
        if s is None:
            return None
        return self.data[s[3] + addr:s[3] + addr + n]

    def section_bytes(self, name):
        s = self.section(name)
        return b'' if s is None else self.data[s[3]:s[3] + s[4]]

    # ── symbols ──────────────────────────────────────────────────────────

    def _symtab(self):
        for nm in ('.symtab', '.dynsym'):
            s = self.section(nm)
            if s is not None:
                strtab = self._sh[s[5]]
                return s, self.data[strtab[3]:strtab[3] + strtab[4]]
        raise ValueError(f'{self.path}: no symbol table')

    def symbols(self):
        """Yields (name, value, size, shndx, type)."""
        for name, value, size, shndx, typ, _bind in self.symbols_full():
            yield name, value, size, shndx, typ

    def symbols_full(self):
        """Yields (name, value, size, shndx, type, bind).

        bind is 0 local, 1 global, 2 weak. A weak function symbol in one of
        our objects is a template instantiation or an inline from a header,
        not code this translation unit set out to define."""
        sec, strs = self._symtab()
        blob = self.data[sec[3]:sec[3] + sec[4]]
        step = 24 if self.is64 else 16
        for i in range(len(blob) // step):
            o = i * step
            if self.is64:
                nameoff, info, _other, shndx = struct.unpack('<IBBH', blob[o:o + 8])
                value, size = struct.unpack('<QQ', blob[o + 8:o + 24])
            else:
                nameoff, value, size = struct.unpack('<III', blob[o:o + 12])
                info, _other, shndx = struct.unpack('<BBH', blob[o + 12:o + 16])
            end = strs.index(b'\0', nameoff)
            yield (strs[nameoff:end].decode('utf-8', 'replace'),
                   value, size, shndx, info & 0xF, info >> 4)

    _func_index = None

    def _function_index(self):
        """{name: (value, size, shndx)} keeping the largest-size definition.

        Built once. `function()` is called per-symbol by the differ, and a
        linear scan of a 380k-symbol .dynsym each time is minutes of work
        across a whole-project run."""
        if self._func_index is None:
            idx = {}
            for nm, value, size, shndx, styp in self.symbols():
                if shndx == 0 or not nm:
                    continue
                cur = idx.get(nm)
                if cur is None or size > cur[1]:
                    idx[nm] = (value, size, shndx)
            self._func_index = idx
        return self._func_index

    def function(self, name):
        """(address, size, bytes) for a function symbol, or None."""
        best = self._function_index().get(name)
        if best is None:
            return None
        addr, size, shndx = best
        sec = self._sh[shndx]
        # A relocatable object addresses from the section start; a linked
        # library addresses from the load address.
        off = sec[3] + (addr if sec[2] == 0 else addr - sec[2])
        return addr, size, self.data[off:off + size]

    def section_of(self, name):
        for nm, value, size, shndx, styp in self.symbols():
            if nm == name and shndx != 0:
                return self._sh[shndx][-1]
        return None

    # ── relocations ──────────────────────────────────────────────────────

    def relocations(self, section_name):
        """{offset: (symbol name, type, addend)} for one section."""
        out = {}
        sec, strs = self._symtab()
        symblob = self.data[sec[3]:sec[3] + sec[4]]
        step = 24 if self.is64 else 16

        def symname(idx):
            o = idx * step
            nameoff, = struct.unpack('<I', symblob[o:o + 4])
            name = strs[nameoff:strs.index(b'\0', nameoff)].decode('utf-8', 'replace')
            if name:
                return name
            # A relocation against a section carries no symbol name of its
            # own; what it points at is that section plus the addend.
            if self.is64:
                info, shndx = struct.unpack('<BxH', symblob[o + 4:o + 8])
            else:
                info, shndx = struct.unpack('<BxH', symblob[o + 12:o + 16])
            if (info & 0xF) == 3 and shndx < len(self._sh):
                return self._sh[shndx][-1]
            return name

        if section_name == '.dyn':
            candidates = ('.rela.dyn', '.rel.dyn')
        else:
            candidates = (f'.rela{section_name}', f'.rel{section_name}')
        for want in candidates:
            s = self.section(want)
            if s is None:
                continue
            blob = self.data[s[3]:s[3] + s[4]]
            has_addend = want.startswith('.rela')
            esize = (24 if has_addend else 16) if self.is64 else (12 if has_addend else 8)
            for i in range(len(blob) // esize):
                o = i * esize
                if self.is64:
                    off, info = struct.unpack('<QQ', blob[o:o + 16])
                    addend = struct.unpack('<q', blob[o + 16:o + 24])[0] if has_addend else 0
                    sym, rtype = info >> 32, info & 0xFFFFFFFF
                else:
                    off, info = struct.unpack('<II', blob[o:o + 8])
                    addend = struct.unpack('<i', blob[o + 8:o + 12])[0] if has_addend else 0
                    sym, rtype = info >> 8, info & 0xFF
                out[off] = (symname(sym), rtype, addend)
        return out

    _dynrel = None

    def dynamic_relocations(self):
        """{address: (symbol name, type, addend)} from .rela.dyn.

        A GOT slot in a linked library is empty in the file; what it will
        hold is in the dynamic relocation for that address."""
        if self._dynrel is not None:
            return self._dynrel
        self._dynrel = self.relocations('.dyn')
        return self._dynrel

    def read_at(self, addr, n):
        """n bytes at a virtual address in a linked image."""
        for s in self._sh:
            if s[2] and s[2] <= addr < s[2] + s[4] and s[1] != 8:
                off = s[3] + (addr - s[2])
                return self.data[off:off + n]
        return None

    def cstr(self, addr):
        """The C string at a virtual address in a linked image."""
        for s in self._sh:
            if s[2] and s[2] <= addr < s[2] + s[4] and s[1] != 8:
                off = s[3] + (addr - s[2])
                end = self.data.index(b'\0', off)
                return self.data[off:end].decode('utf-8', 'replace')
        return None
