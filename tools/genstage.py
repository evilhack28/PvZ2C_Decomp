#!/usr/bin/env python3
"""Scaffold a <Name>Stage.cpp -- RT_CLASS boilerplate for the two stage classes (genstage.py <Name>)."""

import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)

TEMPLATE = '''//
//  {name}Stage.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-02.
//

#include "{name}Stage.h"

#include "ReflectionBuilder.h"

{classes}'''

CLASS_BLOCK = '''RT_CLASS_IMPLEMENT({cls});
void {cls}::StaticClassInit()
{{
	REFLECTION_CLASSBUILDER_BEGIN({cls});
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR({base});

	REFLECTION_CLASSBUILDER_END({cls});
}}
'''


def parse_header(name):
    """[(class, base, [override decls]), ...] for the two stage classes."""
    path = os.path.join(ROOT, 'include', 'PvZ', f'{name}Stage.h')
    text = open(path).read()
    out = []
    for m in re.finditer(r'class\s+(\w+)\s*:\s*public\s+([\w:]+)\s*\{(.*?)\n\};', text, re.S):
        cls, base, body = m.group(1), m.group(2), m.group(3)
        if cls not in (f'{name}Stage', f'{name}StageProperties'):
            continue
        overrides = []
        for line in body.splitlines():
            m2 = re.match(r'\s*(?:virtual\s+)?'
                          r'((?:[\w:]+(?:<[^>]*>)?[ \t]*[\*&]?[ \t]+)+'  # return type
                          r'(\w+)[ \t]*\([^;{]*\))'                      # name + params
                          r'[ \t]*(?:const[ \t]*)?override[ \t]*;', line)
            if m2:
                overrides.append((re.sub(r'\s+', ' ', m2.group(1)).strip(), m2.group(2)))
        out.append((cls, base, [s for s, _ in overrides], [n for _, n in overrides]))
    return out


def main(argv):
    if not argv:
        print(__doc__)
        return 2
    name = re.sub(r'Stage$', '', argv[0])
    classes = parse_header(name)
    if len(classes) != 2:
        sys.exit(f'{name}Stage.h: found {len(classes)} stage classes, expected 2')

    blocks = [CLASS_BLOCK.format(cls=cls, base=base) for cls, base, _, _ in classes]
    todo = []
    for cls, base, sigs, names in classes:
        for sig, nm in zip(sigs, names):
            m = re.match(r'void\s+' + re.escape(nm) + r'\s*\((.*)\)\s*$', sig)
            args = [a.split()[-1].lstrip('*&') for a in m.group(1).split(',') if a.strip()] if m else []
            if m:
                # a void override with no real body forwards to the base
                blocks.append(f'\nvoid {cls}::{nm}({m.group(1)})\n'
                              f'{{\n\t{base}::{nm}({", ".join(args)});\n}}\n')
            else:
                blocks.append(f'\n// TODO {cls}::{sig}\n')
                todo.append(f'{cls}::{sig}')

    out = TEMPLATE.format(name=name, classes='\n'.join(blocks))
    dest = os.path.join(ROOT, 'src', 'PvZ2', 'stages', f'{name}Stage.cpp')
    open(dest, 'w').write(out)
    print(f'wrote {os.path.relpath(dest, ROOT)}')
    for t in todo:
        print(f'  TODO  {t}')


if __name__ == '__main__':
    raise SystemExit(main(sys.argv[1:]))
