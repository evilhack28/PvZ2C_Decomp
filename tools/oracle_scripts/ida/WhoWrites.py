"""Every function that references the given addresses, decompiled: WhoWrites 06ad56c8,06ad5700."""

from ida_api import *


def run(args):
    funcs = []
    for s in args[0].split(','):
        t = int(s.strip(), 16)
        println('refs to %s:' % A(t))
        for frm, kind in refs_to(t):
            f = fn_containing(frm)
            println('  %s  %s  in %s' % (A(frm), kind, fname(f) if f is not None else '(none)'))
            if f is not None and f not in funcs:
                funcs.append(f)
    for f in funcs:
        println('\n========== %s  @ %s ==========' % (fname(f), A(f)))
        c = decompile(f)
        if c is not None:
            println(c)
