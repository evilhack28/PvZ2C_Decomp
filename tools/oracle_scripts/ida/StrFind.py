"""ASCII/UTF-16/UTF-32 occurrences of a needle anywhere in memory (20 per encoding): StrFind <needle>."""

from ida_api import *


def run(args):
    n = args[0]
    for enc, w in (('a', 1), ('u16', 2), ('u32', 4)):
        pat = b''.join(bytes([ord(c) & 0xff]) + b'\0' * (w - 1) for c in n)
        for c, ea in enumerate(find_bytes(pat, min_ea())):
            if c >= 20:
                break
            println('%s %s' % (A(ea), enc))
    println('done ' + n)
