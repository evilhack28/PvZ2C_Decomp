"""Grep every symbol name for a substring: Grep <needle> [limit]."""

import ida_nalt

from ida_api import *


def run(args):
    needle = args[0] if args else 'LostCityStage'
    limit = int(args[1]) if len(args) > 1 else 400
    println("=== %s base=%s funcs=%d  grep='%s' ==="
            % (ida_nalt.get_root_filename(), A(image_base()), function_count(), needle))
    n = 0
    for ea, nm in symbols():
        fn = fn_at(ea) is not None
        # Ghidra lists the demangled symbol and keeps the mangled one as a label
        rows = [('Function' if fn else 'Label', nm)]
        if raw_name(ea) != nm:
            rows.append(('Label', raw_name(ea)))
        for kind, s in rows:
            if needle not in s:
                continue
            println('  %012x %-8s%s %s' % (ea, kind, ' FUNC' if fn else '', s))
            n += 1
            if n >= limit:
                break
        if n >= limit:
            println('  ...(truncated at %d)' % limit)
            break
    println('total: %d' % n)
