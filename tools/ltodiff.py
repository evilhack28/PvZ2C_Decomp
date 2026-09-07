"""ltodiff.py <src.cpp>... [-f sym...] -- compile the TUs with -flto, LTO-link a .so, diff its functions vs the game.

For the block-layout / register-allocation near-misses that only close under
whole-program codegen (see docs/ea-build-config.md). Single-TU `wd.py` can't
reproduce those; this can, once enough of the tree builds together.
"""

import argparse
import glob
import os
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import asmdiff
import config
from pvzelf import Elf

GREEN, RED, BOLD, OFF = '\033[32m', '\033[31m', '\033[1m', '\033[0m'


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('sources', nargs='+', help='.cpp files (or globs)')
    ap.add_argument('-f', '--func', nargs='+', default=[],
                    help='only diff these mangled symbols (default: all defined & in game)')
    ap.add_argument('--keep', action='store_true', help='keep the .lto.so')
    ap.add_argument('-a', '--all', action='store_true', help='full diff for each mismatch')
    args = ap.parse_args()

    srcs = []
    for s in args.sources:
        srcs += sorted(glob.glob(s)) if any(c in s for c in '*?[') else [s]
    srcs = [os.path.abspath(s) for s in srcs if s.endswith('.cpp')]
    if not srcs:
        sys.exit('no .cpp sources')

    out = os.path.join(config.BUILD, 'lto')
    os.makedirs(out, exist_ok=True)
    ltoflags = ['-flto', '-ffat-lto-objects']

    objs = []
    for s in srcs:
        o = os.path.join(out, os.path.basename(s) + '.lto.o')
        r = subprocess.run([config.GXX, *config.CXXFLAGS, *ltoflags, '-c', s, '-o', o],
                           capture_output=True, text=True)
        if r.returncode != 0:
            print('\n'.join(l for l in r.stderr.splitlines() if 'error:' in l)[:3000]
                  or r.stderr[-3000:])
            sys.exit(f'{RED}compile failed: {os.path.basename(s)}{OFF}')
        objs.append(o)

    so = os.path.join(out, 'out.lto.so')
    link = [config.GXX, *config.CXXFLAGS, *ltoflags, '-shared', '-nostdlib',
            '-Wl,--defsym=__dso_handle=0', '-Wl,--unresolved-symbols=ignore-all',
            '-Wl,-z,notext', *objs, '-o', so]
    r = subprocess.run(link, capture_output=True, text=True)
    if r.returncode != 0:
        print(r.stderr[-4000:])
        sys.exit(f'{RED}LTO link failed{OFF}')

    game_elf = Elf(config.TARGET_LIB)
    ours_elf = Elf(so)

    wanted = args.func
    if not wanted:
        ours_syms = {n for n, v, s, sh, t in ours_elf.symbols() if sh and t == 2}
        game_syms = {n for n, v, s, sh, t in game_elf.symbols() if t == 2}
        wanted = sorted(ours_syms & game_syms)

    nok = 0
    for sym in wanted:
        g = asmdiff.listing(game_elf, sym)
        o = asmdiff.listing(ours_elf, sym)
        if g is None:
            print(f'  {sym}  {RED}not in game{OFF}'); continue
        if o is None:
            print(f'  {sym}  {RED}not in .so{OFF}'); continue
        same, total, _ = asmdiff.compare(g, o)
        ok = same == total and len(g) == len(o)
        nok += ok
        tag = f'{GREEN}OK{OFF}' if ok else f'{RED}{same}/{total} ({100*same//max(total,1)}%){OFF}'
        cn = '' if len(g) == len(o) else f'  [game {len(g)}, ours {len(o)}]'
        print(f'{BOLD}{sym}{OFF}  {tag}{cn}')

    print(f'\n{nok}/{len(wanted)} OK')
    if not args.keep and os.path.exists(so):
        os.remove(so)


if __name__ == '__main__':
    main()
