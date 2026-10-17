"""The value/symbol at each 8-byte slot within +-0x40 of each hex address, and the code referencing it."""

from ida_api import *


def run(args):
    for a in args:
        ad = int(a, 16)
        for d in range(-0x40, 0x41, 8):
            x = ad + d
            s = name(x)
            sb = '  %s val=%x%s' % (A(x), u64(x), '' if s is None else ' sym=' + s)
            for frm, kind in refs_to(x):
                c = fn_containing(frm)
                sb += ' <-%s@%s%s' % (kind, A(frm), '' if c is None else ':' + fname(c))
            println(sb)
