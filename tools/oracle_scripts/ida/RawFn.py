"""Raw disassembly of a function + the data/type at each address it references: RawFn <name|addr>."""

import re

from ida_api import *


def run(args):
    arg = args[0]
    f = fn_containing(toaddr(arg)) if re.fullmatch(r'[0-9a-fA-F]+', arg) else None
    if f is None:
        f = next((g for g in functions() if arg in (fname(g), sname(g))), None)
    if f is None:
        println('not found: ' + arg)
        return
    println('=== %s  @ %s  size=%d ===' % (fname(f), A(f), fsize(f)))
    for ea, _, t in insns(f):
        note = ''
        for to, _ in refs_from(ea):
            note += '   ; ' + A(to)
            s = name(to)
            if s:
                note += ' ' + s
            d = data_at(to)
            if d:
                note += ' [' + d[0] + (' = %s' % d[1] if d[1] is not None else '') + ']'
        println('  %s  %-28s%s' % (A(ea), t, note))
