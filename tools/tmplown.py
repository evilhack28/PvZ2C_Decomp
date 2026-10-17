"""Work out which class file each template instantiation belongs to, by who calls it in the game."""
import argparse
import re
import bisect
import collections
import json
import os
import struct
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import config
from lib.pvzelf import Elf
from progress import is_stub

R_RELATIVE, R_GLOB_DAT, R_JUMP_SLOT, R_ABS64 = 1027, 1025, 1026, 257


def build_graph(game):
    funcs = {}
    for n, v, s, sh, t in game.symbols():
        if t == 2 and sh and s:
            funcs.setdefault(v, (s, []))[1].append(n)
    starts = sorted(funcs)
    vt = {}
    for n, v, s, sh, t in game.symbols():
        if t == 1 and sh and s:
            vt[v] = (s, n)
    vstarts = sorted(vt)
    rel = game.dynamic_relocations()
    got = {a: r[0] for a, r in rel.items() if r[1] in (R_GLOB_DAT, R_JUMP_SLOT, R_ABS64) and r[0]}
    ptrs = {a: r[2] for a, r in rel.items() if r[1] == R_RELATIVE}
    edges = collections.defaultdict(set)
    byname = {}
    for v, (s, names) in funcs.items():
        for n in names:
            byname[n] = v

    def fn_at(addr):
        i = bisect.bisect_right(starts, addr) - 1
        return starts[i] if i >= 0 and addr < starts[i] + funcs[starts[i]][0] else None

    def obj_at(addr):
        i = bisect.bisect_right(vstarts, addr) - 1
        return -vstarts[i] if i >= 0 and addr < vstarts[i] + vt[vstarts[i]][0] else None

    for a, t in ptrs.items():
        o = obj_at(a)
        if o is None:
            continue
        if t in funcs:
            edges[o].add(t)
        else:
            t2 = obj_at(t)
            if t2 is not None and t2 != o:
                edges[o].add(t2)

    def data_ref(addr):
        return addr if addr in funcs else obj_at(addr)

    text = game.section('.text')
    base, off, size = text[2], text[3], text[4]
    code = struct.unpack(f'<{size // 4}I', game.data[off:off + size])
    for k, fa in enumerate(starts):
        fs = funcs[fa][0]
        i0 = (fa - base) // 4
        if i0 < 0 or i0 + fs // 4 > len(code):
            continue
        pages = {}
        out = edges[fa]
        for j in range(i0, i0 + fs // 4):
            w = code[j]
            op = w & 0xFC000000
            if op == 0x94000000 or op == 0x14000000:
                d = w & 0x3FFFFFF
                if d & 0x2000000:
                    d -= 0x4000000
                t = fa + (j - i0) * 4 + d * 4
                t = fn_at(t)
                if t is not None and t != fa:
                    out.add(t)
            elif (w & 0x9F000000) == 0x90000000:
                imm = ((w >> 5) & 0x7FFFF) << 2 | ((w >> 29) & 3)
                if imm & 0x100000:
                    imm -= 0x200000
                pages[w & 31] = (((fa + (j - i0) * 4) >> 12) + imm) << 12
            elif (w & 0xFF800000) == 0x91000000 and (w >> 5) & 31 in pages:
                a = pages[(w >> 5) & 31] + ((w >> 10) & 0xFFF)
                r = data_ref(a)
                if r is not None and r != fa:
                    out.add(r)
            elif (w & 0xFFC00000) == 0xF9400000 and (w >> 5) & 31 in pages:
                a = pages[(w >> 5) & 31] + ((w >> 10) & 0xFFF) * 8
                nm = got.get(a)
                if nm in byname and byname[nm] != fa:
                    out.add(byname[nm])
                elif a in ptrs:
                    r = data_ref(ptrs[a])
                    if r is not None and r != fa:
                        out.add(r)
    return funcs, edges


def vt_names(game):
    return {v: (s, n) for n, v, s, sh, t in game.symbols() if t == 1 and sh and s}


_GENERIC_TAIL = ('Functions.cpp', 'Unclassified.cpp', 'RuntimeSymbols.cpp')
SHARED_LIMIT = 5


def generic(unit):
    return not unit or unit.startswith('src/ThirdParty/') or '/EASTL/' in unit or unit.endswith(_GENERIC_TAIL)


def demangle(names):
    import glob
    exe = glob.glob(os.path.join(config.NDK, 'toolchains', 'aarch64-linux-android-4.9', 'prebuilt', '*', 'bin',
                                 'aarch64-linux-android-c++filt.exe'))[0]
    out = subprocess.run([exe], input=chr(10).join(names), capture_output=True, text=True).stdout.split(chr(10))
    return dict(zip(names, out))


def is_template(dem):
    depth, head = 0, []
    for ch in dem:
        if ch == '(' and depth == 0:
            break
        depth += ch == '<'
        depth -= ch == '>'
        head.append(ch)
    return '<' in ''.join(head)


def arg_tokens(dem):
    """Identifiers inside the first template argument list, in order."""
    import re
    i = dem.find('<')
    return re.findall(r'[A-Za-z_][A-Za-z0-9_]*', dem[i:]) if i >= 0 else []


REFL = 'src/SexyAppFramework/Rt/Reflection.cpp'
REFL_TMPL = 'src/SexyAppFramework/Rt/ReflectionTemplates.cpp'
_SKIP = {'Reflection', 'Sexy', 'RClass', 'RType', 'RMethod', 'RSymbol', 'IRefManualSymbolBuilder'}
_HDR = None


def header_home(token):
    """File for a game class with no function of its own: its header's file, else where scaffold would put it."""
    global _HDR
    if _HDR is None:
        import re
        from scaffold import header_index, _norm
        defs = {}
        root = os.path.join(config.HERE, 'include')
        pat = re.compile(r'^\s*(?:struct|class)\s+([A-Za-z_][A-Za-z0-9_]*)\s*(?::[^;{]*)?\{', re.M)
        for d, _, fs in os.walk(root):
            for f in fs:
                if f.endswith('.h'):
                    try:
                        txt = open(os.path.join(d, f), encoding='utf-8', errors='replace').read()
                    except OSError:
                        continue
                    for m in pat.finditer(txt):
                        defs.setdefault(m.group(1), os.path.splitext(f)[0])
                    for m in re.finditer(r'(?:STATE_ENUM_BASE_BEGIN|enum\s+class|enum)\s*\(?\s*([A-Za-z_][A-Za-z0-9_]*)', txt):
                        defs.setdefault(m.group(1), os.path.splitext(f)[0])
        _HDR = (header_index(), _norm, defs)
    hdr, norm, defs = _HDR
    if token in _SKIP or token not in defs or len(token) < 4:
        return None
    h = hdr.get(norm(token)) or hdr.get(norm(defs[token]))
    if not h:
        from scaffold import fallback_path
        h = fallback_path(token, None)
    h = h.replace('//', '/') if h else h
    return h if h and h.startswith(('src/PvZ2/', 'src/SexyAppFramework/')) and not generic(h) else None


def arg_tokens_all(dem, ns):
    out = []
    for n in ns:
        out += arg_tokens(dem[n])
    return out


FREE_BUCKETS = {'src/ThirdParty/Unclassified.cpp', 'src/PvZ2/Data/GlobalFunctions.cpp'}


def tokens_of(dem):
    import re
    return re.findall(r'[A-Za-z_][A-Za-z0-9_]*', dem.replace('non-virtual thunk to ', '').replace('virtual thunk to ', ''))


def cls_home(token, cls_units):
    if token in cls_units:
        h = [u for u in cls_units[token] if not generic(u)]
        return cls_units[token].most_common(1)[0][0] if h else None
    return header_home(token)


def plan(units, game):
    """{symbol: new unit} for every template instantiation whose real owner differs from where it sits."""
    from scaffold import class_ns
    funcs, edges = build_graph(game)
    rev = collections.defaultdict(set)
    for a, ts in edges.items():
        for t in ts:
            rev[t].add(a)
    sym2unit = {s: u for u, d in units.items() for s, _ in d['funcs']}
    names = sorted({n for _, ns in funcs.values() for n in ns})
    dem = demangle(names)
    tmpl = {n: is_template(dem[n]) for n in names}
    anchor = {}
    for a, (_, ns) in funcs.items():
        us = [sym2unit.get(n) for n in ns if not tmpl[n]]
        real = next((u for u in us if not generic(u)), None)
        if real:
            anchor[a] = real
    cls_units = collections.defaultdict(collections.Counter)
    for u, d in units.items():
        if generic(u):
            continue
        for sym, _ in d['funcs']:
            if not tmpl.get(sym, True):
                c = class_ns(sym)[0]
                if c:
                    cls_units[c][u] += 1
    freq = collections.Counter()
    for n in names:
        if tmpl[n]:
            freq.update(set(arg_tokens(dem[n])))
    moves, why = {}, collections.Counter()
    for a, (_, ns) in funcs.items():
        seen, st, own = {a}, [a], set()
        if a in anchor:
            st = []
        while st and len(own) <= SHARED_LIMIT:
            x = st.pop()
            for p in rev.get(x, ()):
                if p in seen:
                    continue
                seen.add(p)
                if p in anchor:
                    if anchor[p]:
                        own.add(anchor[p])
                else:
                    st.append(p)
        def hint_for(n):
            toks = list(dict.fromkeys(arg_tokens(dem[n])))
            cands = []
            for t in toks:
                h = cls_home(t, cls_units)
                if not h and t.endswith('State') and len(t) > 7:
                    h = cls_home(t[:-5], cls_units)
                if h and not generic(h):
                    cands.append((freq[t], h))
            return [h for _, h in sorted(cands, key=lambda x: x[0])]

        for n in ns:
            if not (tmpl[n] and n in sym2unit):
                continue
            hint = hint_for(n)
            if hint:
                target, kind = next((u for u in hint if u in own), hint[0]), 'type'
            elif len(own) == 1:
                target, kind = next(iter(own)), 'caller'
            elif 1 < len(own) <= SHARED_LIMIT:
                target, kind = min(own), 'caller-shared'
            elif sym2unit[n] == REFL:
                target, kind = REFL_TMPL, 'reflection-generic'
            else:
                why['stay'] += 1
                continue
            why[kind] += 1
            if sym2unit[n] != target:
                moves[n] = target
    adj = sorted((a, anchor[a]) for a in anchor)
    akeys = [a for a, _ in adj]
    for a, (_, ns) in funcs.items():
        todo = [n for n in ns if tmpl[n] and n in sym2unit and generic(sym2unit[n]) and n not in moves]
        if not todo:
            continue
        votes, seen, st = collections.Counter(), {a}, [a]
        while st and len(seen) < 30000:
            x = st.pop()
            for p in rev.get(x, ()):
                if p in seen:
                    continue
                seen.add(p)
                if p in anchor:
                    votes[anchor[p]] += 1
                else:
                    st.append(p)
        if votes:
            top = max(votes.values())
            target = min(u for u, c in votes.items() if c == top)
            kind = 'forced-caller'
        else:
            i = bisect.bisect_right(akeys, a) - 1
            target = adj[max(i, 0)][1]
            kind = 'forced-adjacent'
        for n in todo:
            moves[n] = target
            why[kind] += 1
    for n, u in sym2unit.items():
        if n in moves or u not in FREE_BUCKETS:
            continue
        for t in arg_tokens_all(dem, [n]) if False else tokens_of(dem[n]):
            home = cls_home(t, cls_units)
            if home:
                moves[n] = home
                why['free-function'] += 1
                break
    return moves, why


def tracked(rel):
    return bool(subprocess.run(['git', 'ls-files', '--error-unmatch', rel], capture_output=True, cwd=config.HERE).returncode == 0)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--apply', action='store_true')
    args = ap.parse_args()
    game = Elf(config.TARGET_LIB)
    upath = os.path.join(config.HERE, 'units.json')
    data = json.load(open(upath))
    before = os.path.join(config.BUILD, 'tmpl', 'units.before.json')
    if os.path.exists(before):
        data = json.load(open(before))
    units = data['units']
    moves, why = plan(units, game)
    print(f'{len(moves)} symbols move;', dict(why))
    src = {s: u for u, d in units.items() for s, _ in d['funcs']}
    flow = collections.Counter((src[s], t) for s, t in moves.items() if s in src)
    out_of = collections.Counter(src[s] for s in moves if s in src)
    print('biggest sources:', out_of.most_common(8))
    byname = collections.defaultdict(list)
    for u in units:
        byname[os.path.basename(u).lower()].append(u)
    alias = {}
    for t in set(moves.values()):
        if t in units:
            continue
        same = [u for u in byname.get(os.path.basename(t).lower(), []) if u != t]
        if same:
            alias[t] = max(same, key=lambda u: len(units[u]['funcs']))
    from scaffold import area
    for t in set(moves.values()):
        if t not in units and t not in alias and re.fullmatch(r'src/PvZ2/[^/]+\.cpp', t):
            alias[t] = f'src/PvZ2/{area(os.path.basename(t)[:-4])}/{os.path.basename(t)}'
    moves = {sym: alias.get(t, t) for sym, t in moves.items()}
    print(f'{len(alias)} new files folded into an existing file of the same name')
    if not args.apply:
        return
    if not os.path.exists(before):
        json.dump(data, open(before, 'w'))
    size = {s: z for d in units.values() for s, z in d['funcs']}
    for u, d in units.items():
        d.pop('moved_in', None)
        d.pop('moved_out', None)
    for sym, target in moves.items():
        old = src.get(sym)
        if old:
            units[old].setdefault('moved_out', []).append(sym)
            units[old]['funcs'] = [f for f in units[old]['funcs'] if f[0] != sym]
        if target not in units:
            units[target] = {'original': target[4:], 'code': 0, 'funcs': []}
        units[target].setdefault('moved_in', []).append([sym, size[sym]])
        units[target]['funcs'].append([sym, size[sym]])
    for d in units.values():
        d['funcs'].sort(key=lambda f: -f[1])
        d['code'] = sum(z for _, z in d['funcs'])
    json.dump(data, open(upath, 'w'))
    for d, _, fs in os.walk(os.path.join(config.HERE, 'src')):
        for f in fs:
            full = os.path.join(d, f)
            rel = os.path.relpath(full, config.HERE).replace(os.sep, '/')
            if f.endswith('.cpp') and rel not in units and is_stub(full) and not tracked(rel):
                os.remove(full)
    from scaffold import write_stub
    for t in {t for t in moves.values()}:
        if not os.path.exists(os.path.join(config.HERE, t)):
            write_stub(t, units[t]['original'], [(s, z) for s, z in units[t]['funcs']])
            print('stub', t)
    print('units.json rewritten (backup build/tmpl/units.before.json)')


if __name__ == '__main__':
    main()
