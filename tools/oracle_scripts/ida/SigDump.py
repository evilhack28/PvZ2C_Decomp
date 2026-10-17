"""Ref-lib address, size and prototype for each Class::method argument (exact name match)."""

from ida_api import *


def run(args):
    want = set(args)
    for f in functions():
        if fname(f) in want:
            println('SIG %x %d %s' % (f - BIAS, fsize(f), prototype(f)))
