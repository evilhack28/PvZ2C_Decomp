"""Compile every real .cpp under src/, diff every function against the
library, print one number.

    py -3 tools/progress.py [FILTER] [--todo] [--report P] [--check P] [--cache]

`--cache` skips recompiling unchanged units and `--jobs` raises the worker
count; a full tree pass goes from ~5 min to ~30 s with both.

Per file, scope is: every method the game gives a class the file owns (has a
strong symbol for). Scaffold stubs get their scope from units.json.
"""

import argparse
import bisect
import concurrent.futures
import datetime
import glob
import json
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import asmdiff
import config
from pvzelf import Elf

_TTY = sys.stdout.isatty() and not os.environ.get('NO_COLOR')
GREEN, RED, YELLOW, GREY, BOLD, OFF = (
    ('\033[32m', '\033[31m', '\033[33m', '\033[90m', '\033[1m', '\033[0m')
    if _TTY else ('', '', '', '', '', ''))

_COMP = re.compile(r'(\d+)')
_CACHE = False


def pretty(sym):
    """Mangled -> Name::method / Name::Name / Name::~Name, no demangler."""
    s = sym
    if s.startswith('_ZNK'):
        s = s[4:]
    elif s.startswith('_ZN'):
        s = s[3:]
    else:
        return sym
    parts, i = [], 0
    while i < len(s) and s[i].isdigit():
        m = _COMP.match(s, i)
        n = int(m.group(1))
        parts.append(s[m.end():m.end() + n])
        i = m.end() + n
    if not parts:
        return sym
    tail = s[i:i + 2]
    if tail[:1] == 'C':
        parts.append(parts[-1])
    elif tail[:1] == 'D':
        parts.append('~' + parts[-1])
    elif tail == 'aS':
        parts.append('operator=')
    return '::'.join(parts)


def sources():
    root = os.path.join(config.HERE, 'src')
    return sorted(p.replace(os.sep, '/')
                  for p in glob.glob(f'{root}/**/*.cpp', recursive=True))


def _newest_input():
    """Latest mtime of config.py, the compiler + every header (a cached .o older than this is stale)."""
    newest = os.path.getmtime(os.path.join(config.HERE, 'tools', 'config.py'))
    if os.path.exists(config.GXX):
        newest = max(newest, os.path.getmtime(config.GXX))
    for root, _dirs, files in os.walk(os.path.join(config.HERE, 'include')):
        for fn in files:
            if fn.endswith('.h'):
                newest = max(newest, os.path.getmtime(os.path.join(root, fn)))
    return newest


_NEWEST_INPUT = None
STUB = 'stub'


def is_stub(source):
    """True if every non-blank line is a // comment (a scaffold placeholder)."""
    try:
        with open(source, encoding='utf-8', errors='replace') as f:
            for line in f:
                s = line.strip()
                if s and not s.startswith('//'):
                    return False
    except OSError:
        return False
    return True


def compile_one(source):
    global _NEWEST_INPUT
    if is_stub(source):
        return source, STUB, None
    os.makedirs(config.BUILD, exist_ok=True)
    obj = os.path.join(config.BUILD, os.path.relpath(source, config.HERE)
                       .replace(os.sep, '__').replace('/', '__').replace('.cpp', '.o'))
    if _CACHE and os.path.exists(obj):
        if _NEWEST_INPUT is None:
            _NEWEST_INPUT = _newest_input()
        omt = os.path.getmtime(obj)
        if omt > os.path.getmtime(source) and omt > _NEWEST_INPUT:
            return source, obj, None
    done = subprocess.run([config.GXX, *config.CXXFLAGS, '-c', source, '-o', obj],
                          capture_output=True, text=True)
    if done.returncode != 0:
        errs = [l for l in done.stderr.splitlines() if ' error: ' in l]
        return source, None, errs[:8] or [done.stderr.strip()[:400]]
    return source, obj, None


_NAMESPACES = {'Sexy', 'std', 'EA', 'eastl', '__gnu_cxx', 'EATech', '__cxxabiv1'}


def _components(sym):
    """[(name, end_offset)] for the length-prefixed parts of _ZN..."""
    s = sym
    off = 4 if s.startswith('_ZNK') else 3 if s.startswith('_ZN') else 0
    if not off:
        return []
    out = []
    i = off
    while i < len(s) and s[i].isdigit():
        m = _COMP.match(s, i)
        n = int(m.group(1))
        out.append((s[m.end():m.end() + n], m.end() + n))
        i = m.end() + n
    return out


class Owner:
    __slots__ = ('zn', 'znk', 'toplevel')

    def __init__(self, zn, znk, toplevel):
        self.zn, self.znk, self.toplevel = zn, znk, toplevel

    @property
    def prefixes(self):
        return (self.zn, self.znk)


def owned_prefixes(sym):
    """Owner(_ZN.., _ZNK.., toplevel) for sym's class, or None if sym is not
    a plain class method (namespace, template instantiation, lib type)."""
    comps = _components(sym)
    if not comps:
        return None
    marker = sym[comps[-1][1]:comps[-1][1] + 1]
    class_comps = comps if marker in ('C', 'D') else comps[:-1]
    if not class_comps:
        return None
    cls = class_comps[-1][0]
    if len(cls) < 3 or not cls[0].isupper() or cls in _NAMESPACES:
        return None
    if marker == 'I':                          # template: ...Class I<args> E
        return None
    body = sym[3 if sym.startswith('_ZN') else 4:class_comps[-1][1]]
    toplevel = len(class_comps) == 1 or class_comps[0][0] not in _NAMESPACES
    return Owner(f'_ZN{body}', f'_ZNK{body}', toplevel)


def _range(sorted_names, prefix):
    lo = bisect.bisect_left(sorted_names, prefix)
    hi = bisect.bisect_left(sorted_names, prefix + '￿', lo)
    return sorted_names[lo:hi]


# Structs whose every method emits weak (no strong symbol to key on); named
# here so their file still gets a scope. `<len><name>` mangled form.
EXTRA_OWNED = {
    '_ZN12DefenderInfo', '_ZN18S2C_PVP_BigMapInfo', '_ZN20S2C_PVP_DefenderInfo',
    '_ZN21S2C_PVP_BigMapPVPInfo',
}


def analyse(source, obj, game, game_syms, game_names, manifest_unit=None):
    """-> rows [(state, same, total, bytes, label)]. state: ok / near / todo.

    Scope = every game method of a class this file owns (has a strong symbol
    for, or is in EXTRA_OWNED). A stub's scope comes from units.json.
    """
    if obj == STUB:
        funcs = (manifest_unit or {}).get('funcs', [])
        rows = [('todo', 0, 0, size, pretty(sym)) for sym, size in funcs]
        rows.sort(key=lambda r: (-r[3], r[4]))
        return rows

    ours = Elf(obj)
    strong, defined = set(), set()
    for n, v, s, sh, t, b in ours.symbols_full():
        if sh and t == 2 and s:
            defined.add(n)
            if b == 1:               # STB_GLOBAL
                strong.add(n)

    by_class = {}   # Owner.zn -> [Owner, our syms, our strong syms]
    for n in defined:
        o = owned_prefixes(n)
        if not o:
            continue
        slot = by_class.setdefault(o.zn, [o, [], []])
        slot[1].append(n)
        if n in strong:
            slot[2].append(n)

    scope = {}
    for zn, (o, mine, mine_strong) in by_class.items():
        owned = bool(mine_strong) or zn in EXTRA_OWNED
        if not owned:
            continue
        for name in _range(game_names, o.zn) + _range(game_names, o.znk):
            scope[name] = game_syms[name][1]
    our_funcs = defined

    rows = []
    for sym, size in scope.items():
        if sym not in our_funcs:
            rows.append(('todo', 0, 0, size, pretty(sym)))
            continue
        th = asmdiff.listing(game, sym)
        mn = asmdiff.listing(ours, sym)
        if th is None or mn is None:
            rows.append(('todo', 0, 0, size, pretty(sym)))
            continue
        same, tot, _ = asmdiff.compare(th, mn)
        ok = same == tot and len(th) == len(mn)
        rows.append(('ok' if ok else 'near', same, tot, size, pretty(sym)))
    rows.sort(key=lambda r: (r[0] == 'ok', r[0] == 'near', -r[3], r[4]))
    return rows


_GAME = None


def _game():
    """The reference library, parsed once per process."""
    global _GAME
    if _GAME is None:
        g = Elf(config.TARGET_LIB)
        syms = {}
        for n, v, s, sh, t in g.symbols():
            if t == 2 and sh and s:
                syms.setdefault(n, (v, s))
        _GAME = (g, syms, sorted(syms))
    return _GAME


def _rows_for(job):
    """analyse() in a worker: the reference ELF cannot be pickled, so rebuild it."""
    source, obj, rel, manifest_unit = job
    game, game_syms, game_names = _game()
    return source, analyse(source, obj, game, game_syms, game_names, manifest_unit)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('filter', nargs='?', help='only files whose path contains this')
    ap.add_argument('--todo', action='store_true', help='hide matched functions')
    ap.add_argument('--report', metavar='PATH',
                    help='write a splat-schema progress report (measures + units)')
    ap.add_argument('--check', metavar='PATH', help='compare to a baseline report, exit 1 on regression')
    ap.add_argument('--jobs', type=int, default=min(8, (os.cpu_count() or 4)))
    ap.add_argument('--quiet', action='store_true', help='totals only')
    ap.add_argument('--all', action='store_true',
                    help='list functions for every unit, scaffold stubs included')
    ap.add_argument('--cache', action='store_true', default=True,
                    help='skip recompiling a file whose sources are older than its object')
    ap.add_argument('--no-cache', dest='cache', action='store_false',
                    help='recompile every unit from scratch')
    args = ap.parse_args()

    global _CACHE
    _CACHE = args.cache

    files = [s for s in sources() if not args.filter or args.filter.lower() in s.lower()]
    if not files:
        print('no source files')
        return 0

    manifest = {'units': {}, 'unplaced': {}}
    mpath = os.path.join(config.HERE, 'units.json')
    if os.path.exists(mpath):
        manifest = json.load(open(mpath))

    game, game_syms, game_names = _game()

    objs, fails = {}, {}
    with concurrent.futures.ThreadPoolExecutor(max_workers=args.jobs) as ex:
        for source, obj, errs in ex.map(compile_one, files):
            if obj:
                objs[source] = obj
            else:
                fails[source] = errs

    # analyse is pure Python (capstone + diffing) and holds the GIL, so it
    # needs processes, not the threads the compile step uses.
    todo = [(s, objs[s], os.path.relpath(s, config.HERE).replace(os.sep, '/'),
             manifest['units'].get(os.path.relpath(s, config.HERE).replace(os.sep, '/')))
            for s in files if s not in fails]
    analysed = {}
    if len(todo) > 1 and args.jobs > 1:
        with concurrent.futures.ProcessPoolExecutor(max_workers=args.jobs) as ex:
            for source, rows in ex.map(_rows_for, todo):
                analysed[source] = rows
    else:
        for job in todo:
            source, rows = _rows_for(job)
            analysed[source] = rows

    units = []
    t_ok = t_near = t_todo = 0
    b_ok = b_all = 0

    for source in files:
        rel = os.path.relpath(source, config.HERE).replace(os.sep, '/')
        if source in fails:
            print(f'{RED}COMPILE FAILED{OFF}  {rel}')
            for e in fails[source]:
                print(f'    {e}')
            units.append({'name': rel, 'error': fails[source],
                          'total_code': 0, 'matched_code': 0, 'matched_code_percent': 0.0,
                          'total_functions': 0, 'matched_functions': 0,
                          'matched_functions_percent': 0.0, 'fuzzy_match_percent': 0.0,
                          'functions': []})
            continue

        rows = analysed[source]
        n_ok = sum(1 for r in rows if r[0] == 'ok')
        n_near = sum(1 for r in rows if r[0] == 'near')
        n_todo = sum(1 for r in rows if r[0] == 'todo')
        bo = sum(r[3] for r in rows if r[0] == 'ok')
        allb = sum(r[3] for r in rows)
        fuzzy = sum(size * (1.0 if state == 'ok' else (same / tot if tot else 0.0))
                    for state, same, tot, size, _ in rows)

        t_ok += n_ok; t_near += n_near; t_todo += n_todo
        b_ok += bo; b_all += allb

        pct = 100.0 * bo / allb if allb else 0.0
        stub = objs[source] is STUB
        tag = f'{GREY}stub{OFF} ' if stub else ''
        if not rows:
            print(f'{GREY}    -   {n_ok}/{len(rows):<4d} fn  (unmapped)      {tag}{rel}{OFF}')
        else:
            colour = GREEN if pct == 100 else (GREY if not n_ok else YELLOW)
            print(f'{colour}{pct:5.1f}%{OFF}  {n_ok}/{len(rows):<4d} fn  {bo}/{allb} B   '
                  f'{tag}{BOLD}{rel}{OFF}')

        u = {
            'name': rel,
            'total_code': allb, 'matched_code': bo,
            'matched_code_percent': round(pct, 2),
            'total_functions': len(rows), 'matched_functions': n_ok,
            'matched_functions_percent': round(100.0 * n_ok / len(rows), 2) if rows else 0.0,
            'fuzzy_match_percent': round(100.0 * fuzzy / allb, 2) if allb else 0.0,
        }
        if n_ok or n_near:                    # detail only for started units
            u['functions'] = [
                {'name': label, 'size': size, 'matched': state == 'ok',
                 'fuzzy_match_percent': round(100.0 * same / tot, 2) if tot else 0.0}
                for state, same, tot, size, label in rows]
        units.append(u)

        if not args.quiet and (args.all or args.filter or n_ok or n_near):
            for state, same, tot, size, label in rows:
                if state == 'ok' and args.todo:
                    continue
                if state == 'ok':
                    print(f'     {GREEN}OK  {OFF} {size:5d} B  {label}')
                elif state == 'near':
                    print(f'     {YELLOW}{same:3d}/{tot:<4d}{OFF}{size:5d} B  {label}')
                else:
                    print(f'     {GREY}--   {size:5d} B  {label}{OFF}')

    pct = 100.0 * b_ok / b_all if b_all else 0.0
    n_fn = t_ok + t_near + t_todo
    total_fuzzy = sum(u['fuzzy_match_percent'] * u['total_code'] for u in units)

    started = [u for u in units if u['matched_functions']]
    s_ok = sum(u['matched_code'] for u in started)
    s_all = sum(u['total_code'] for u in started)
    unplaced = manifest.get('unplaced', {})

    report = {
        'generated': datetime.datetime.now(datetime.timezone.utc).isoformat(timespec='seconds'),
        'measures': {
            'total_functions': n_fn, 'matched_functions': t_ok,
            'matched_functions_percent': round(100.0 * t_ok / n_fn, 2) if n_fn else 0.0,
            'total_code': b_all, 'matched_code': b_ok,
            'matched_code_percent': round(pct, 2),
            'fuzzy_match_percent': round(total_fuzzy / b_all, 2) if b_all else 0.0,
            'started_units': len(started), 'total_units': len(units),
            'started_code': s_all, 'started_matched_code': s_ok,
            'started_percent': round(100.0 * s_ok / s_all, 2) if s_all else 0.0,
            'unplaced_functions': unplaced.get('functions', 0),
            'unplaced_code': unplaced.get('code', 0),
            'compile_failures': len(fails),
        },
        'units': units,
    }

    print()
    print(f'{BOLD}started  {s_ok}/{s_all} B  '
          f'{100.0 * s_ok / s_all if s_all else 0:.1f}%   in {len(started)}/{len(units)} units{OFF}')
    print(f'{BOLD}overall  {b_ok}/{b_all} B  {pct:.2f}%   '
          f'({t_ok}/{n_fn} functions placed'
          + (f', {unplaced["functions"]} unplaced' if unplaced.get('functions') else '')
          + f'){OFF}'
          + (f'   {RED}{len(fails)} compile failure(s){OFF}' if fails else ''))

    if args.report:
        with open(args.report, 'w') as f:
            json.dump(report, f, indent=2)
        print(f'wrote {args.report}')

    rc = 1 if fails else 0
    if args.check:
        base = json.load(open(args.check))
        rc = max(rc, regressions(base, report, args.check))
    return rc


def regressions(base, now, baseline_path):
    """Nonzero if any unit matches fewer bytes than the baseline."""
    was = {u['name']: u for u in base.get('units', [])}
    bad = 0
    for u in now['units']:
        b = was.get(u['name'])
        if b is None:
            continue
        if u.get('error') or u['matched_code'] < b.get('matched_code', 0):
            print(f'{RED}REGRESSION{OFF}  {u["name"]}: '
                  f'{b.get("matched_code", 0)} -> {u["matched_code"]} bytes matched')
            bad = 1
    for name in set(was) - {u['name'] for u in now['units']}:
        print(f'{RED}REGRESSION{OFF}  {name}: unit gone from the tree')
        bad = 1
    if not bad:
        print(f'{GREEN}no regressions against {os.path.basename(baseline_path)}{OFF}')
    return bad


if __name__ == '__main__':
    raise SystemExit(main())
