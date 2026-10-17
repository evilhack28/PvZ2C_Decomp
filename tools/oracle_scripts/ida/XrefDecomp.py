"""Functions referencing each address, decompiled: XrefDecomp <hex,...> [maxLines]."""

from ida_api import *


def run(args):
    hi = int(args[1]) if len(args) > 1 else 60
    seen = []
    for h in args[0].split(','):
        for frm, _ in refs_to(toaddr(h)):
            f = fn_containing(frm)
            println('REF %s from %s in %s' % (h, A(frm), 'none' if f is None else '%s@%s' % (sname(f), A(f))))
            if f is not None and f not in seen:
                seen.append(f)
    for f in seen:
        c = decompile(f)
        println('//===== %s@%s' % (sname(f), A(f)))
        if c is not None:
            println('\n'.join(c.split('\n')[:hi]))
