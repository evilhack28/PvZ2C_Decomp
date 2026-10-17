"""Capstone arm64 text rewritten to Ghidra's instruction syntax, so IDA ports can reuse the Java regexes."""

import re
import struct

from capstone import CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN, Cs

_cs = Cs(CS_ARCH_ARM64, CS_MODE_LITTLE_ENDIAN)
_PADDED = re.compile(r'^(b|bl|b\.\w+|cbz|cbnz|tbz|tbnz)$')
_UNPADDED = re.compile(r'^(adr|adrp|ldr|ldrsw|prfm)$')
_SHIFT = re.compile(r'^(LSL|LSR|ASR|ROR|MSL|[US]XT[BHWX])\b')
_COND = {'lo': 'cc', 'hs': 'cs'}


def _num(s):
    v = int(s, 0)
    return v - (1 << 64) if v >= 1 << 63 else v


def _hex(v):
    return '%s0x%x' % ('-' if v < 0 else '', abs(v))


def _split(op_str):
    parts, depth, cur = [], 0, ''
    for ch in op_str:
        depth += ch in '[{'
        depth -= ch in ']}'
        if ch == ',' and depth == 0:
            parts.append(cur.strip())
            cur = ''
        else:
            cur += ch
    return parts + [cur.strip()] if cur.strip() else parts


def _mem(p, word):
    inner = p[1:p.index(']')]
    tail = p[p.index(']'):]
    f = [x.strip() for x in inner.split(',')]
    if (word >> 27) & 7 == 7 and (word >> 24) & 3 == 0 and (word >> 21) & 1 and (word >> 10) & 3 == 2:
        # register offset: Ghidra's text follows the encoding, not the alias capstone picks
        option, s, size, simd = (word >> 13) & 7, (word >> 12) & 1, word >> 30, (word >> 26) & 1
        name = {2: 'UXTW', 3: 'LSL', 6: 'SXTW', 7: 'SXTX'}.get(option, '?')
        amt = f[2].partition('#')[2] if len(f) > 2 else ''
        if s and amt:
            ext = ', %s #%s' % (name, _hex(int(amt, 0)))
        elif simd and option == 3 and not s:
            return '[%s,%s%s' % (f[0], f[1], tail)
        elif size == 0 and not simd and not s:
            ext = ', %s ' % name
        else:
            ext = ', %s #0x0' % name
        return '[%s, %s%s%s' % (f[0], f[1], ext, tail)
    out = [f[0]]
    for x in f[1:]:
        if x.startswith('#'):
            out.append('#' + _hex(_num(x[1:])))
        else:
            out.append(x)
    return '[' + ', '.join(out) + tail


def _float_bits(reg, val):
    if reg[0] == 'd':
        return '0x%x' % struct.unpack('<Q', struct.pack('<d', val))[0]
    return '0x%x' % struct.unpack('<I', struct.pack('<f', val))[0]


def _rewrite(mn, ops, word):
    if mn == 'mov' and (word >> 23) & 0x3f == 0x24 and (word >> 29) & 3 == 1:
        mn = 'orr'                                         # ORR (immediate) from the zero register
        ops = [ops[0], ('x' if word >> 31 else 'w') + 'zr', ops[1]]
    elif mn == 'bfi':
        mn = 'bfm'
        ops = ops[:2] + ['#%d' % ((word >> 16) & 0x3f), '#%d' % ((word >> 10) & 0x3f)]
    out = []
    prev_imm = False
    for i, p in enumerate(ops):
        last = i == len(ops) - 1
        if last and p.startswith('#') and _PADDED.match(mn):
            out.append('0x%08x' % int(p[1:], 0))
        elif last and p.startswith('#') and _UNPADDED.match(mn) and not any(o.startswith('[') for o in ops):
            out.append('0x%x' % int(p[1:], 0))
        elif mn == 'fmov' and p.startswith('#'):
            out.append(_float_bits(ops[0], float(p[1:])))
        elif p in ('#0.0', '#0.00000000'):
            out.append('#0.0')
        elif p.startswith('['):
            out.append(_mem(p, word))
        elif _SHIFT.match(p.upper()):
            kind, _, amt = p.partition(' ')
            if amt:
                n = int(amt[1:], 0)
                amt = ' #%d' % n if prev_imm else ('  #' if 'XT' in kind.upper() else ' #') + _hex(n)
            else:
                amt = ' '
            out.append(kind.upper() + amt)
        elif p.startswith('#'):
            v = _num(p[1:])
            if v < 0 and ops[0].startswith('w') and mn in ('mov', 'orr'):
                v &= 0xffffffff
            out.append('#' + _hex(v))
            prev_imm = True
            continue
        elif p in _COND:
            out.append(_COND[p])
        elif p.startswith('{'):
            out.append(re.sub(r'\.(\d*[bhsdq])\b', lambda m: '.' + m.group(1).upper(), p.replace(', ', ',')))
        else:
            p = re.sub(r'\.(\d*[bhsdq])\b', lambda m: '.' + m.group(1).upper(), p)
            out.append(re.sub(r'\[(\d+)\]', lambda m: '[' + _hex(int(m.group(1))) + ']', p))
        prev_imm = False
    if mn.startswith('b.') and mn[2:] in _COND:
        mn = 'b.' + _COND[mn[2:]]
    text = ''
    for i, p in enumerate(out):
        glue = text and (_SHIFT.match(p) or (p.startswith('#') and out[i - 1].endswith(']')))
        text += (', ' if glue else (',' if text else '')) + p
    return mn, text


def insn(code, ea):
    """(mnemonic, Ghidra-style text) of the 4-byte instruction `code` at `ea`."""
    word = int.from_bytes(code[:4], 'little')
    for i in _cs.disasm(code[:4], ea):
        mn, ops = _rewrite(i.mnemonic, _split(i.op_str), word)
        return mn, (mn + ' ' + ops) if ops else mn
    return '??', '?? 0x%08x' % word
