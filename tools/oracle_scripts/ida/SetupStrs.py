"""The biggest function referencing a string, and every string it references in order: SetupStrs <needle>."""

from ida_api import *


def _cstr(ea):
    out = ''
    for b in read(ea, 80):
        if b == 0:
            break
        if b < 32 or b > 126:
            return None
        out += chr(b)
    return out if len(out) > 1 else None


def run(args):
    best = None
    for hit in find_bytes(b'\0' + args[0].encode() + b'\0'):
        for frm, _ in refs_to(hit + 1):
            f = fn_containing(frm)
            if f is not None and (best is None or fsize(f) > fsize(best)):
                best = f
    if best is None:
        println('NOFUNC')
        return
    println('FUNC %s size %d' % (A(best), fsize(best)))
    nref = ninst = 0
    for ea, _, _ in insns(best):
        ninst += 1
        for to, kind in refs_from(ea):
            nref += 1
            if not is_call(kind):
                s = _cstr(to)
                if s is not None:
                    println('S ' + s)
    println('inst %d refs %d' % (ninst, nref))
