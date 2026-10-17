"""Decompile functions by name or hex address: Decomp "A::b,C::d,03d003cc"."""

import re

from ida_api import *


def run(args):
    for w in ','.join(args).split(','):
        w = w.strip()
        f = fn_containing(toaddr(w)) if re.fullmatch(r'[0-9a-fA-F]+', w) else None
        if f is None:
            f = next((g for g in functions() if fname(g) == w), None) or fn_by_name(w)
        if f is None:
            println('\n// >>> not found: ' + w)
            continue
        println('\n// ===== %s  @ %s  (%d b) =====' % (fname(f), A(f), fsize(f)))
        c = decompile(f)
        if c is not None:
            println(c)
