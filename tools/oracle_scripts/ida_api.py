"""Ghidra-flavoured helpers over idalib for the IDA ports in oracle_scripts/ida (run inside the IDA worker)."""

import re

import ida_bytes
import ida_funcs
import ida_hexrays
import ida_ida
import ida_nalt
import ida_name
import ida_segment
import ida_xref
import idautils
import idc

import asmtext
import config

BADADDR = idc.BADADDR
BIAS = config.GHIDRA_ADDR_BIAS              # IDA address = ref-lib address + BIAS (see config.py)
_hexrays = None
_segbytes = {}


def println(*a):
    print(*a, flush=False)


def A(ea):
    """An address the way Ghidra's Address.toString prints it."""
    return '%08x' % ea


def toaddr(s):
    return int(s[2:] if s.lower().startswith('0x') else s, 16)


# ---- names ----

def _demangle(raw):
    for fl in (lambda: ida_ida.inf_get_short_demnames(), lambda: idc.get_inf_attr(idc.INF_SHORT_DN)):
        try:
            dem = idc.demangle_name(raw, fl())
            break
        except Exception:
            dem = None
    return dem


def _strip_args(dem):
    depth = 0
    for i, ch in enumerate(dem):
        if ch == '<':
            depth += 1
        elif ch == '>':
            depth -= 1
        elif ch == '(' and depth == 0 and not dem[:i].endswith('operator'):
            return dem[:i]
    return dem


def name(ea):
    """Qualified name without arguments, like Ghidra's getName(true)."""
    raw = ida_name.get_name(ea)
    if not raw:
        return None
    dem = _demangle(raw)
    return _strip_args(dem) if dem else raw


def raw_name(ea):
    return ida_name.get_name(ea) or None


def symbols():
    """(ea, qualified name) for every named address."""
    for ea, raw in idautils.Names():
        dem = _demangle(raw)
        yield ea, (_strip_args(dem) if dem else raw)


def lookup(w):
    """A hex address or a (mangled, short or qualified) name -> address, else None."""
    w = w.strip()
    if re.fullmatch(r'(0x)?[0-9a-fA-F]+', w):
        return toaddr(w)
    ea = ida_name.get_name_ea(BADADDR, w)
    if ea != BADADDR:
        return ea
    for ea, n in symbols():
        if n == w:
            return ea
    leaf = w.rsplit('::', 1)[-1]
    return next((ea for ea, n in symbols() if n.rsplit('::', 1)[-1] == leaf), None)


# ---- functions ----

def fn_containing(ea):
    f = ida_funcs.get_func(ea)
    return f.start_ea if f else None


def fn_at(ea):
    f = ida_funcs.get_func(ea)
    return ea if f and f.start_ea == ea else None


def fn_by_name(w):
    ea = lookup(w)
    return fn_containing(ea) if ea is not None else None


def fsize(f):
    """Bytes in the function body, chunks included (Ghidra getBody().getNumAddresses())."""
    return sum(e - s for s, e in idautils.Chunks(f))


def fname(f):
    return name(f) or 'FUN_%08x' % f


def sname(f):
    """The last `::` component of fname, like Ghidra's getName()."""
    n, depth = fname(f), 0
    for i in range(len(n) - 1, 0, -1):
        depth += (n[i] == '>') - (n[i] == '<')
        if depth == 0 and n[i - 1:i + 1] == '::':
            return n[i + 1:]
    return n


def functions(start=0, end=BADADDR):
    return idautils.Functions(start, end)


def function_count():
    return ida_funcs.get_func_qty()


def prototype(f):
    return idc.get_type(f) or idc.guess_type(f) or '?'


# ---- instructions ----

def is_code(ea):
    return ida_bytes.is_code(ida_bytes.get_flags(ea))


def insn(ea):
    """(mnemonic, Ghidra-style text) at ea."""
    return asmtext.insn(ida_bytes.get_bytes(ea, 4) or b'\0\0\0\0', ea)


def text(ea):
    return insn(ea)[1]


def insns(f):
    """(ea, mnemonic, text) for every instruction of function f, in address order."""
    for s, e in sorted(idautils.Chunks(f)):
        for ea in idautils.Heads(s, e):
            if is_code(ea):
                mn, t = insn(ea)
                yield ea, mn, t


def next_insn(ea):
    ea = ida_bytes.next_head(ea, BADADDR)
    while ea != BADADDR and not is_code(ea):
        ea = ida_bytes.next_head(ea, BADADDR)
    return None if ea == BADADDR else ea


def prev_insn(ea):
    ea = ida_bytes.prev_head(ea, 0)
    while ea != BADADDR and not is_code(ea):
        ea = ida_bytes.prev_head(ea, 0)
    return None if ea == BADADDR else ea


def insn_containing(ea):
    h = ida_bytes.get_item_head(ea)
    return h if is_code(h) else None


# ---- references ----

_KIND = {ida_xref.fl_CN: 'UNCONDITIONAL_CALL', ida_xref.fl_CF: 'UNCONDITIONAL_CALL',
         ida_xref.fl_JN: 'UNCONDITIONAL_JUMP', ida_xref.fl_JF: 'UNCONDITIONAL_JUMP',
         ida_xref.dr_O: 'DATA', ida_xref.dr_R: 'READ', ida_xref.dr_W: 'WRITE'}


def is_call(kind):
    return kind.endswith('CALL')


def refs_from(ea):
    """[(to, kind)] leaving ea, ordinary flow excluded."""
    return [(x.to, _KIND.get(x.type, 'DATA')) for x in idautils.XrefsFrom(ea, 0) if x.type != ida_xref.fl_F]


def refs_to(ea):
    """[(from, kind)] reaching ea, ordinary flow excluded."""
    return [(x.frm, _KIND.get(x.type, 'DATA')) for x in idautils.XrefsTo(ea, 0) if x.type != ida_xref.fl_F]


# ---- data ----

def string_at(ea):
    """The defined string literal at ea, else None (Ghidra getDataAt(..).getValue() instanceof String)."""
    if ea is None or not ida_bytes.is_strlit(ida_bytes.get_flags(ea)):
        return None
    b = idc.get_strlit_contents(ea, -1, idc.get_str_type(ea))
    return b.decode('utf-8', 'replace') if b is not None else None


def strings():
    """(ea, text) for every defined string, in address order."""
    out = [(ea, s) for ea in (i.ea for i in idautils.Strings()) for s in [string_at(ea)] if s is not None]
    return sorted(out)


def data_at(ea):
    """(type name, value) of the defined item at ea, else None."""
    fl = ida_bytes.get_flags(ea)
    if ida_bytes.is_strlit(fl):
        return 'string', string_at(ea)
    if ida_bytes.is_qword(fl):
        return 'pointer' if ida_bytes.is_off0(fl) else 'qword', '%x' % u64(ea)
    if ida_bytes.is_dword(fl):
        return 'dword', '%x' % u32(ea)
    if ida_bytes.is_data(fl):
        return 'undefined%d' % ida_bytes.get_item_size(ea), None
    return None


def read(ea, n):
    return ida_bytes.get_bytes(ea, n) or b''


def u32(ea):
    return ida_bytes.get_dword(ea)


def u64(ea):
    return ida_bytes.get_qword(ea)


def segments():
    for s in idautils.Segments():
        seg = ida_segment.getseg(s)
        yield seg.start_ea, seg.end_ea, ida_segment.get_segm_name(seg)


def find_bytes(pat, start=0):
    """Every address >= start where pat occurs in a loaded segment."""
    for s, e, _ in segments():
        if e <= start:
            continue
        if s not in _segbytes:
            _segbytes[s] = read(s, e - s)
        data, i = _segbytes[s], max(0, start - s)
        while True:
            i = data.find(pat, i)
            if i < 0:
                break
            yield s + i
            i += 1


def min_ea():
    return ida_ida.inf_get_min_ea()


def image_base():
    return ida_nalt.get_imagebase()


# ---- decompiler ----

def decompile(f):
    """Hex-Rays C for function f, or None with the reason printed."""
    global _hexrays
    if _hexrays is None:
        _hexrays = bool(ida_hexrays.init_hexrays_plugin())
    if not _hexrays:
        return None
    try:
        return str(ida_hexrays.decompile(f))
    except ida_hexrays.DecompilationFailure as e:
        println('// <decomp failed: %s>' % e)
        return None
