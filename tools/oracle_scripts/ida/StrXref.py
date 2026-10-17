"""For each substring argument, matching strings and the functions that reference them."""

from ida_api import *


def run(args):
    for ea, s in strings():
        for n in args:
            if n not in s:
                continue
            seen = []
            for frm, _ in refs_to(ea):
                f = fn_containing(frm)
                if f is not None and '%x(%d)' % (f, fsize(f)) not in seen:
                    seen.append('%x(%d)' % (f, fsize(f)))
            println('STR [%s] @%s "%s" -> %s'
                    % (n, A(ea), s[:60].replace('\n', ' '), ','.join(seen) or '(no xref)'))
            break
