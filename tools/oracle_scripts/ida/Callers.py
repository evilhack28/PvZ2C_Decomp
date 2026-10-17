"""The functions that call each address given as an argument."""

from ida_api import *


def run(args):
    for h in args:
        m = {}
        for frm, _ in refs_to(toaddr(h)):
            f = fn_containing(frm)
            m.setdefault(frm if f is None else f, []).append(frm)
        println('//===== callers of %s (%d functions)' % (h, len(m)))
        for k in sorted(m):
            println('  %s  sites=[%s]' % (A(k), ', '.join(A(x) for x in m[k])))
