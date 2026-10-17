"""A class vtable found from its mangled type-name string (e.g. 12CheatUIPanel), each slot with function size: VtByRtti <name> [slots]."""

from ida_api import *


def run(args):
    want = args[0]
    slots = int(args[1]) if len(args) > 1 else 40
    for ea, s in strings():
        if s != want:
            continue
        for frm, _ in refs_to(ea):
            ti = frm - 8
            println('TYPEINFO %s for %s' % (A(ti), want))
            for hit in find_bytes(ti.to_bytes(8, 'little'), min_ea()):
                vt = hit + 8
                println('VTABLE %s (typeinfo slot at %s)' % (A(vt), A(hit)))
                for i in range(slots):
                    p = vt + 8 * i
                    v = u64(p)
                    f = fn_at(v)
                    println('  +0x%03x %s -> %x (%s bytes)' % (8 * i, A(p), v, '?' if f is None else fsize(f)))
