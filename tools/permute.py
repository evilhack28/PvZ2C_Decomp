#!/usr/bin/env python3
"""Hill-climb permuter: mutate one function's source, recompile, keep what scores best vs the game."""

import argparse
import concurrent.futures as cf
import os
import random
import re
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import asmdiff
import config
import wd
from pvzelf import Elf

FLIP = {'<': '>', '>': '<', '<=': '>=', '>=': '<='}
ATOM = re.compile(r'^[\w.:]+(\(.*\))?$|^\(.*\)$', re.S)


def mask(s):
    """Blank string/char literals so operators inside them are ignored."""
    out, i = list(s), 0
    while i < len(s):
        if s[i] in '"\'':
            q, j = s[i], i + 1
            while j < len(s) and s[j] != q:
                j += 2 if s[j] == '\\' else 1
            for k in range(i + 1, min(j, len(s))):
                out[k] = ' '
            i = j
        i += 1
    return ''.join(out)


def operand_end(m, k):
    """True if m[k] ends an operand (so a following +/- is binary)."""
    return k >= 0 and (m[k].isalnum() or m[k] in '_)].')


def left_extent(m, i, mode):
    d, j = 0, i - 1
    while j >= 0:
        c = m[j]
        if c in ')]':
            d += 1
        elif c in '([':
            if d == 0:
                return j + 1
            d -= 1
        elif d == 0:
            if c in ',;?{}':
                return j + 1
            if c == ':' and m[j - 1:j] != ':' and m[j + 1:j + 2] != ':':
                return j + 1
            if c in '&|' and m[j - 1:j] == c:
                return j + 1
            if c == '=':
                return j + 1
            if c in '<>' and m[j + 1:j + 2] != '>' and m[j - 1:j] != '-':
                if not (c == '>' and m[j - 1:j] == '-'):
                    return j + 1
            if c in '+-' and operand_end(m, next((k for k in range(j - 1, -1, -1) if not m[k].isspace()), -1)):
                if mode == 'add':
                    return None
                return j + 1
            if c in '*/%' and mode == 'mul':
                pass
            if c == '!' and m[j + 1:j + 2] != '=':
                pass
        j -= 1
    return 0


def right_extent(m, i, mode):
    d, j = 0, i
    while j < len(m):
        c = m[j]
        if c in '([':
            d += 1
        elif c in ')]':
            if d == 0:
                return j
            d -= 1
        elif d == 0:
            if c in ',;?{}':
                return j
            if c == ':' and m[j + 1:j + 2] != ':' and m[j - 1:j] != ':':
                return j
            if c in '&|' and m[j + 1:j + 2] == c:
                return j
            if c in '=<>' and not (c == '>' and m[j - 1:j] == '-'):
                return j
            if c == '!' and m[j + 1:j + 2] == '=':
                return j
            if c in '+-' and operand_end(m, next((k for k in range(j - 1, -1, -1) if not m[k].isspace()), -1)):
                return j
            if c in '*/%' and mode in ('mul', 'add') and (mode == 'mul' or False):
                return j
        j += 1
    return len(m)


def wrap(t):
    t = t.strip()
    return t if ATOM.match(t) and t.count('(') == t.count(')') else f'({t})'


def swap_at(s, m, i, oplen, mode):
    lo = left_extent(m, i, mode)
    if lo is None:
        return None
    hi = right_extent(m, i + oplen, mode)
    left, right = s[lo:i].strip(), s[i + oplen:hi].strip()
    if not left or not right or left.startswith('return') or left[0] in '!~':
        return None
    return lo, hi, left, right


def m_cmp(s, rng):
    m = mask(s)
    hits = [x for x in re.finditer(r'\s(<=|>=|<|>)\s', m)]
    if not hits:
        return None
    x = rng.choice(hits)
    op = x.group(1)
    r = swap_at(s, m, x.start(1), len(op), 'cmp')
    if not r:
        return None
    lo, hi, left, right = r
    return s[:lo] + f'{right} {FLIP[op]} {left}' + s[hi:]


def m_commute(s, rng):
    m = mask(s)
    hits = [x for x in re.finditer(r'\s(\*|\+|==|!=)\s', m)]
    if not hits:
        return None
    x = rng.choice(hits)
    op = x.group(1)
    mode = {'*': 'mul', '+': 'add'}.get(op, 'cmp')
    r = swap_at(s, m, x.start(1), len(op), mode)
    if not r:
        return None
    lo, hi, left, right = r
    lead = s[lo:i_first_nonspace(s, lo)]
    return s[:lo] + lead + f'{wrap(right)} {op} {wrap(left)}' + s[hi:]


def i_first_nonspace(s, lo):
    k = lo
    while k < len(s) and s[k].isspace():
        k += 1
    return k


def block_end(m, i):
    d = 0
    for k in range(i, len(m)):
        if m[k] == '{':
            d += 1
        elif m[k] == '}':
            d -= 1
            if d == 0:
                return k
    return None


def m_ifelse(s, rng):
    m = mask(s)
    hits = list(re.finditer(r'\bif \(', m))
    rng.shuffle(hits)
    for x in hits:
        p, d = x.end() - 1, 0
        for k in range(p, len(m)):
            d += m[k] == '('
            d -= m[k] == ')'
            if d == 0:
                break
        cond = s[p + 1:k]
        b = re.compile(r'\s*\{').match(m, k + 1)
        if not b:
            continue
        b1 = m.index('{', k)
        e1 = block_end(m, b1)
        e = re.compile(r'\s*else\s*\{').match(m, e1 + 1) if e1 else None
        if not e:
            continue
        b2 = m.index('{', e1)
        e2 = block_end(m, b2)
        if not e2:
            continue
        then, els = s[b1:e1 + 1], s[b2:e2 + 1]
        c = cond[2:-1] if cond.startswith('!(') and cond.endswith(')') else f'!({cond})'
        return s[:x.start()] + f'if ({c}) ' + els + ' else ' + then + s[e2 + 1:]
    return None


def pure(t):
    return not re.search(r'\w\s*\(|->|\[|\+\+|--|=', t.replace('==', '').replace('!=', '').replace('<=', '').replace('>=', ''))


def m_andor(s, rng):
    m = mask(s)
    hits = list(re.finditer(r'(&&|\|\|)', m))
    rng.shuffle(hits)
    for x in hits:
        i = x.start()
        lo = left_extent(m, i, 'cmp')
        hi = right_extent(m, i + 2, 'cmp')
        if lo is None:
            continue
        # extents stop at the same logical op, so only single-op conditions qualify
        left, right = s[lo:i].strip(), s[i + 2:hi].strip()
        if not left or not right or not pure(left) or not pure(right):
            continue
        return s[:lo] + f'{right} {x.group(1)} {left}' + s[hi:]
    return None


def m_incr(s, rng):
    hits = list(re.finditer(r'\b(\w+)\+\+|\+\+(\w+)\b', s))
    if not hits:
        return None
    x = rng.choice(hits)
    n = x.group(1) or x.group(2)
    tail = s[x.end():x.end() + 1]
    if tail not in ')' and tail != ';':
        return None
    return s[:x.start()] + (f'++{n}' if x.group(1) else f'{n}++') + s[x.end():]


def m_declswap(s, rng):
    lines = s.split('\n')
    pat = re.compile(r'^\s+[\w:<>*& ]+\s+(\w+)\s*=\s*(.+);\s*$')
    idx = [k for k in range(len(lines) - 1) if pat.match(lines[k]) and pat.match(lines[k + 1])]
    rng.shuffle(idx)
    for k in idx:
        a, b = pat.match(lines[k]), pat.match(lines[k + 1])
        if pure(a.group(2)) and pure(b.group(2)) and not re.search(rf'\b{a.group(1)}\b', b.group(2)) \
                and not re.search(rf'\b{b.group(1)}\b', a.group(2)):
            lines[k], lines[k + 1] = lines[k + 1], lines[k]
            return '\n'.join(lines)
    return None


def m_inline(s, rng):
    lines = s.split('\n')
    pat = re.compile(r'^(\s+)(float|int|double|size_t|bool|auto)\s+(\w+)\s*=\s*(.+);\s*$')
    idx = [k for k in range(len(lines)) if pat.match(lines[k])]
    rng.shuffle(idx)
    for k in idx:
        g = pat.match(lines[k])
        name, expr = g.group(3), g.group(4)
        uses = [j for j in range(len(lines)) if j != k and re.search(rf'\b{name}\b', lines[j])]
        if len(uses) == 1 and uses[0] == k + 1 and pure(expr):
            lines[k + 1] = re.sub(rf'\b{name}\b', f'({expr})' if not ATOM.match(expr) else expr, lines[k + 1])
            del lines[k]
            return '\n'.join(lines)
    return None


def m_temp(s, rng):
    lines = s.split('\n')
    pat = re.compile(r'\(([\w .*/+-]*[*/+-][\w .*/+-]*)\)')
    idx = [k for k in range(len(lines)) if lines[k].strip().startswith(('i_g->', 'return', 'float', 'int')) and pat.search(lines[k])]
    rng.shuffle(idx)
    for k in idx:
        x = pat.search(lines[k])
        e = x.group(1)
        if not pure(e) or re.search(r'\bm_|\bthis\b', e):
            continue
        ind = re.match(r'\s*', lines[k]).group(0)
        n = f't{rng.randrange(1000)}'
        lines[k] = lines[k][:x.start()] + n + lines[k][x.end():]
        lines.insert(k, f'{ind}auto {n} = {e};')
        return '\n'.join(lines)
    return None


MUTATORS = [m_cmp, m_cmp, m_commute, m_commute, m_ifelse, m_andor, m_incr, m_declswap, m_inline, m_temp]


def mutate(fn, rng):
    for _ in range(20):
        out = fn
        for _ in range(rng.choice([1, 1, 1, 2, 2, 3])):
            r = rng.choice(MUTATORS)(out, rng)
            if r and r != out:
                out = r
        if out != fn:
            return out
    return None


def find_fn(text, cls, method):
    pat = re.compile(rf'^[^\s/#][^\n]*\b{re.escape(cls)}::{re.escape(method)}\s*\(', re.M)
    x = pat.search(text)
    if not x:
        sys.exit(f'no definition of {cls}::{method} in the source')
    end = re.compile(r'\n\}\r?\n').search(text, x.start()).end()
    return x.start(), end


def evaluate(job):
    src_dir, stem, tag, full, mangled, build_dir = job
    path = os.path.join(src_dir, f'{stem}.pm{tag}.cpp')
    obj = os.path.join(build_dir, f'pm{tag}.o')
    try:
        with open(path, 'w', encoding='utf-8', newline='') as f:
            f.write(full)
        done = subprocess.run([config.GXX, *config.CXXFLAGS, '-c', path, '-o', obj], capture_output=True, text=True)
        if done.returncode != 0:
            return None
        ours = asmdiff.listing(Elf(obj), mangled)
        return ours
    finally:
        for p in (path,):
            if os.path.exists(p):
                os.remove(p)


def rank(game, ours):
    if ours is None:
        return (-1, 0)
    same, total, _ = asmdiff.compare(game, ours)
    return (same - abs(len(game) - len(ours)), -abs(len(game) - len(ours)))


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('cls')
    ap.add_argument('method')
    ap.add_argument('--symbol', help='mangled name when Class/method is ambiguous')
    ap.add_argument('--jobs', type=int, default=12)
    ap.add_argument('--minutes', type=float, default=10)
    ap.add_argument('--variants', help='file of whole-function variants split by ===== lines; just score them')
    ap.add_argument('--seed', type=int, default=None)
    ap.add_argument('--apply', action='store_true', help='write the best variant into the source file')
    args = ap.parse_args()

    mangled, source = wd.resolve(args.symbol or args.cls, None if args.symbol else args.method)
    text = open(source, encoding='utf-8', newline='').read()
    a, b = find_fn(text, args.cls, args.method)
    crlf = '\r\n' in text
    orig = text[a:b].replace('\r\n', '\n')
    enc = (lambda t: t.replace('\n', '\r\n')) if crlf else (lambda t: t)
    game = asmdiff.listing(Elf(config.TARGET_LIB), mangled)
    src_dir, stem = os.path.dirname(source), os.path.splitext(os.path.basename(source))[0]
    build_dir = os.path.join(config.BUILD, 'pm')
    os.makedirs(build_dir, exist_ok=True)
    rng = random.Random(args.seed)

    def job(tag, fn):
        return (src_dir, stem, tag, text[:a] + enc(fn) + text[b:], mangled, build_dir)

    base = rank(game, evaluate(job('base', orig)))
    pool = {orig: base}
    print(f'{mangled}: baseline score {base[0]} of {len(game)}', flush=True)
    if args.variants:
        parts = [v.strip('\n') + '\n' for v in open(args.variants, encoding='utf-8').read().split('\n=====\n')]
        with cf.ThreadPoolExecutor(args.jobs) as ex:
            res = list(ex.map(evaluate, [job(f'v{i}', v) for i, v in enumerate(parts)]))
        for i, r in enumerate(res):
            print(f'variant {i}: {rank(game, r)[0]}/{len(game)}')
        return
    best, seen, gen, deadline = orig, {orig}, 0, time.time() + args.minutes * 60
    with cf.ThreadPoolExecutor(args.jobs) as ex:
        while time.time() < deadline and pool[best][0] < len(game):
            gen += 1
            ranked = sorted(pool, key=lambda k: pool[k], reverse=True)[:6]
            batch, tries = [], 0
            while len(batch) < args.jobs and tries < 400:
                tries += 1
                parent = ranked[min(int(rng.expovariate(1.2)), len(ranked) - 1)]
                child = mutate(parent, rng)
                if child and child not in seen:
                    seen.add(child)
                    batch.append(child)
            if not batch:
                print('search space exhausted', flush=True)
                break
            results = list(ex.map(evaluate, [job(f'{gen}_{i}', c) for i, c in enumerate(batch)]))
            for c, r in zip(batch, results):
                sc = rank(game, r)
                if sc[0] >= 0 and (len(pool) < 6 or sc >= min(pool.values())):
                    pool[c] = sc
            for k in sorted(pool, key=lambda k: pool[k], reverse=True)[6:]:
                del pool[k]
            top = max(pool, key=lambda k: pool[k])
            if pool[top] > pool[best]:
                best = top
                print(f'gen {gen}: {pool[best][0]}/{len(game)}', flush=True)
            elif gen % 10 == 0:
                print(f'gen {gen}: still {pool[best][0]}/{len(game)}  ({len(seen)} tried)', flush=True)

    out = os.path.join(build_dir, f'{args.cls}_{args.method}.best.cpp')
    open(out, 'w', encoding='utf-8', newline='').write(best)
    print(f'best {pool[best][0]}/{len(game)} (baseline {base[0]}) -> {out}')
    if args.apply and pool[best] > base:
        open(source, 'w', encoding='utf-8', newline='').write(text[:a] + enc(best) + text[b:])
        print('applied to', source)


if __name__ == '__main__':
    main()
