"""Compile one translation unit and diff its functions against the game.

    python tools/m.py src/PvZ2/gameNetWork/NetworkData.cpp
    python tools/m.py src/PvZ2/gameNetWork/NetworkData.cpp -f _ZN22S2C_PVP_BigMapMainInfoC2Ev

With no -f it reports every function the object file defines that the game
also has, which is how a translation unit's progress is read.
"""

import argparse
import os
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import asmdiff
import config
from pvzelf import Elf

GREEN, RED, GREY, BOLD, OFF = '\033[32m', '\033[31m', '\033[90m', '\033[1m', '\033[0m'


def build(source):
    os.makedirs(config.BUILD, exist_ok=True)
    obj = os.path.join(config.BUILD, os.path.basename(source).replace('.cpp', '.o'))
    cmd = [config.GXX, *config.CXXFLAGS, '-c', source, '-o', obj]
    done = subprocess.run(cmd, capture_output=True, text=True)
    if done.returncode != 0:
        print(done.stderr.strip()[:8000])
        raise SystemExit(f'{RED}compile failed{OFF}')
    if done.stderr.strip():
        print(f'{GREY}{done.stderr.strip()[:2000]}{OFF}')
    return obj


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('source')
    ap.add_argument('-f', '--function', action='append', default=[])
    ap.add_argument('-v', '--verbose', action='store_true', help='print the diff for every function')
    args = ap.parse_args()

    obj = build(args.source)
    ours = Elf(obj)
    game = Elf(config.TARGET_LIB)

    defined = args.function or sorted({
        n for n, v, s, shndx, t in ours.symbols() if shndx and t == 2 and s
    })

    matched = total_fn = 0
    for name in defined:
        theirs = asmdiff.listing(game, name)
        if theirs is None:
            print(f'{GREY}  ?   {name}  (not in the game){OFF}')
            continue
        mine = asmdiff.listing(ours, name)
        if mine is None:
            print(f'{GREY}  ?   {name}  (not in our object){OFF}')
            continue

        total_fn += 1
        same, total, diff = asmdiff.compare(theirs, mine)
        pct = 100.0 * same / total if total else 0.0
        ok = same == total and len(theirs) == len(mine)
        if ok:
            matched += 1
            print(f'{GREEN}  OK  {name}  {len(theirs)} insns{OFF}')
        else:
            print(f'{RED}  --  {name}  {same}/{total} insns ({pct:.0f}%){OFF}')
        if diff and (args.verbose or not ok):
            for line in diff[:60]:
                colour = GREEN if line.startswith('+') else RED if line.startswith('-') else GREY
                print(f'      {colour}{line}{OFF}')

    print()
    print(f'{BOLD}{matched}/{total_fn} functions match{OFF}')
    return 0 if matched == total_fn and total_fn else 1


if __name__ == '__main__':
    raise SystemExit(main())
