"""Strings matching a regex ('#' stands for '|'), with the functions that reference them."""

import re

from ida_api import *


def run(args):
    rx = re.compile(args[0].replace('#', '|'))
    for ea, v in strings():
        if not rx.fullmatch(v):
            continue
        seen = []
        for frm, _ in refs_to(ea):
            f = fn_containing(frm)
            k = A(frm) if f is None else '%x' % f
            if k not in seen:
                seen.append(k)
        println('RX %s %s -> [%s]' % (A(ea), v, ', '.join(seen)))
