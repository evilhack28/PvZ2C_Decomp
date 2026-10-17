"""The name of the function containing each hex address argument."""

from ida_api import *


def run(args):
    for a in args:
        f = fn_containing(toaddr(a))
        println('FN %s %s' % (a, '?' if f is None else fname(f)))
