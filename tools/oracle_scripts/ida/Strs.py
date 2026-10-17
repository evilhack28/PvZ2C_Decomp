"""Defined data in [start,end] with its value: Strs <hexStart> <hexEnd>."""

import ida_bytes
import ida_lines

from ida_api import *


def run(args):
    ea, hi = int(args[0], 16), int(args[1], 16)
    if not ida_bytes.is_data(ida_bytes.get_flags(ea)):
        ea = ida_bytes.next_head(ea, hi + 1)
    while ea != BADADDR and ea <= hi:
        if ida_bytes.is_data(ida_bytes.get_flags(ea)):
            s = string_at(ea)
            line = '"%s"' % s if s is not None else \
                ida_lines.tag_remove(ida_lines.generate_disasm_line(ea, 0) or '').split(';')[0].strip()
            println('%08x  %s' % (ea, line))
        ea = ida_bytes.next_head(ea, hi + 1)
