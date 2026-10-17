"""Every reference to each hex address argument, with the containing function."""

from ida_api import *


def run(args):
    for a in args:
        ad = int(a, 16)
        f = fn_at(ad)
        println('TARGET %s %s' % (a, '(no function)' if f is None else fname(f)))
        for frm, kind in refs_to(ad):
            c = fn_containing(frm)
            println('  %s from %s in %s' % (kind, A(frm), '(data)' if c is None else fname(c)))
