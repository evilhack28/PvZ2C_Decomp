"""Instruction window around an address: Win <hex> [beforeInsns] [afterInsns]."""

from ida_api import *


def run(args):
    b = int(args[1]) if len(args) > 1 else 20
    f = int(args[2]) if len(args) > 2 else 20
    i = insn_containing(toaddr(args[0]))
    for _ in range(b):
        p = prev_insn(i)
        if p is None:
            break
        i = p
    for _ in range(b + f):
        if i is None:
            break
        println('%08x  %s' % (i, text(i)))
        i = next_insn(i)
