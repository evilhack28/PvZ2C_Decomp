"""Struct offsets from the headers: off.py <Class> [member ...] | --all (every field) | --game (vs the game's reflected offsets) [--hdr path]."""

import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import config
from lib import hdrindex
from tidy import strip_comments

SKIP = re.compile(r'^\s*(typedef|using|static|friend|enum|class|struct|union|template|public|protected|private)\b')


def header_for(cls, hdr=None):
    hdr = hdr or hdrindex.header_of(cls)
    if hdr is None:
        sys.exit(f'no header defines {cls} -- pass --hdr <path under include/>')
    return re.sub(r'^include/', '', hdr)


def declared_members(cls, hdr):
    """Every non-static data member declared directly in cls's body, in order."""
    text = strip_comments(open(os.path.join(config.HEADERS, hdr), encoding='utf-8', errors='ignore').read())
    m = re.search(r'\b(?:class|struct)\s+(?:\w+\s+)?' + re.escape(cls) + r'\s*(?:final\s*)?(?::[^;{]*)?\{', text)
    if not m:
        return []
    out, depth, stmt = [], 1, ''
    for ch in text[m.end():]:
        if ch == '{':
            depth += 1
        elif ch == '}':
            depth -= 1
            if depth == 0:
                break
            if depth == 1:
                stmt = ''
            continue
        if depth != 1:
            continue
        if ch == ';':
            s = re.sub(r'^\s*#.*$', '', stmt, flags=re.M).strip()
            s = re.sub(r'^(public|protected|private)\s*:', '', s).strip()
            if s and '(' not in s and not SKIP.match(s):
                for part in s.split(','):
                    nm = re.search(r'(\w+)\s*(?:\[[^\]]*\])*\s*(?::\s*\d+)?\s*(?:=.*)?$', part.strip())
                    if nm:
                        out.append(nm.group(1))
            stmt = ''
        elif ch == ':' and depth == 1 and re.search(r'\b(public|protected|private)\s*$', stmt):
            stmt = ''
        else:
            stmt += ch
    return out


def probe(cls, hdr, members):
    """{member: offset} (members that do not compile, e.g. bitfields, are left out) and sizeof."""
    src = os.path.join(config.BUILD, 'offprobe.cpp')
    obj = os.path.join(config.BUILD, 'offprobe.o')
    names = list(dict.fromkeys(members))
    for _ in range(len(names) + 2):
        lines = ['#define private public', '#define protected public', f'#include "{hdr}"', '#include <cstddef>',
                 f'char probe__size[sizeof({cls})] = {{}};']
        lines += [f'char probe_{n}[offsetof({cls}, {n}) + 1] = {{}};' for n in names]
        open(src, 'w').write('\n'.join(lines) + '\n')
        r = subprocess.run([config.GXX, *config.CXXFLAGS, '-w', '-c', src, '-o', obj], capture_output=True, text=True)
        if r.returncode == 0:
            break
        bad = {int(m.group(1)) - 6 for m in re.finditer(r'offprobe\.cpp:(\d+):\d+: error', r.stderr)}
        if not bad or min(bad) < 0:
            sys.exit('\n'.join([l[:200] for l in r.stderr.splitlines() if ' error: ' in l][:8]))
        names = [n for i, n in enumerate(names) if i not in bad]
    else:
        sys.exit('could not get a clean probe')
    from lib.pvzelf import Elf
    syms = {n: s for n, v, s, sh, t in Elf(obj).symbols()}
    return {n: syms['probe_' + n] - 1 for n in names if 'probe_' + n in syms}, syms.get('probe__size')


def game_fields(cls):
    from lib import fields
    from lib.pvzelf import Elf
    elf = Elf(config.TARGET_LIB)
    found = elf.function(f'_ZN{len(cls)}{cls}15StaticClassInitEv')
    fn = found and fields._regfn(elf, found[0], found[1])
    return [(k, o) for k, o in fields.fields(elf, fn) if not k[0].isupper()] if fn else []


def main():
    a = sys.argv[1:]
    hdr = None
    if '--hdr' in a:
        i = a.index('--hdr')
        hdr, a = a[i + 1], a[:i] + a[i + 2:]
    flags = {x for x in a if x.startswith('--')}
    hdr = hdr or next((x for x in a if x.endswith('.h')), None)
    a = [x for x in a if not x.startswith('--') and not x.endswith('.h')]
    if not a:
        sys.exit(__doc__)
    cls, hdr = a[0], header_for(a[0], hdr)
    if '--game' in flags:
        want = game_fields(cls)
        if not want:
            sys.exit(f'{cls}: the game registers no fields')
        ours, size = probe(cls, hdr, [k for k, _ in want if re.fullmatch(r'\w+', k)])
        print(f'{cls}: sizeof {size:#x} in the headers ({hdr})\n')
        print(f'{"field":<34} {"game":>7} {"headers":>8} {"delta":>7}')
        last = None
        for name, off in sorted(want, key=lambda x: x[1]):
            mine = ours.get(name)
            if mine is None:
                print(f'{name:<34} {off:>7x} {"absent":>8}')
                continue
            mark = '' if off - mine == last else '   <-- delta changes'
            last = off - mine
            print(f'{name:<34} {off:>7x} {mine:>8x} {off - mine:>+7d}{mark}')
        return
    members = a[1:] or (declared_members(cls, hdr) if '--all' in flags else [])
    ours, size = probe(cls, hdr, members)
    for n, off in sorted(ours.items(), key=lambda x: x[1]) if '--all' in flags else [(n, ours.get(n)) for n in members]:
        print(f'  {n:<34} {"?" if off is None else hex(off)}')
    print(f'  {"sizeof(" + cls + ")":<34} {size:#x}')


if __name__ == '__main__':
    main()
