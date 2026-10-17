"""Clean a .cpp: args (i_arg -> header names), nums (enum literals -> names, byte-verified), layout (sections); tidy.py [args|nums|layout] [--dry] [--report] [file.cpp ...]."""
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import config

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INC = os.path.join(ROOT, 'include')
_hdr_cache = {}


def headers():
    if 'all' not in _hdr_cache:
        out = []
        for d, _, fs in os.walk(INC):
            for f in fs:
                if f.endswith('.h'):
                    p = os.path.join(d, f)
                    out.append((p, open(p, encoding='utf-8', errors='ignore').read()))
        _hdr_cache['all'] = out
    return _hdr_cache['all']


def split_params(s):
    out, depth, cur = [], 0, ''
    for ch in s:
        if ch in '<(':
            depth += 1
        elif ch in '>)':
            depth -= 1
        if ch == ',' and depth == 0:
            out.append(cur.strip())
            cur = ''
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def strip_comments(text):
    """Blank out comments and string literals, keeping every offset."""
    return re.sub(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'',
                  lambda m: re.sub(r'[^\n]', ' ', m.group(0)), text, flags=re.S)


# -- args --

DEF = re.compile(r'^([A-Za-z_][\w:<>,\*&\s]*?)\b(\w+)::(~?\w+)\(([^()]*i_arg[^()]*)\)(\s*const)?\s*$', re.M)


def norm_type(p):
    p = re.sub(r'=.*$', '', p).strip()
    m = re.match(r'^(.*?)(\w+)$', p)
    t = m.group(1) if m and m.group(1).strip() else p
    return re.sub(r'\s+', '', t).replace('constint', 'int')


def pname(p):
    p = re.sub(r'=.*$', '', p).strip()
    m = re.search(r'(\w+)\s*(\[\])?$', p)
    return m.group(1) if m else None


def find_names(cls, meth, params):
    want = [norm_type(re.sub(r'\bi_arg\d*\b', '', p) + ' x') for p in params]
    pat = re.compile(r'\b' + re.escape(meth) + r'\s*\(([^()]*(?:\([^()]*\)[^()]*)*)\)')
    best = None
    for path, text in headers():
        if not re.search(r'\b(class|struct)\s+' + re.escape(cls) + r'\b', text):
            continue
        for m in pat.finditer(text):
            hp = split_params(m.group(1))
            if len(hp) != len(params):
                continue
            ht = [norm_type(p if re.search(r'\w\s*$', p) and ' ' in p.strip() else p + ' x') for p in hp]
            if ht == want:
                names = [pname(p) for p in hp]
                if all(names) and all(n not in ('int', 'float', 'bool') for n in names):
                    best = names
    return best


def tidy_args(path, dry):
    s = open(path, encoding='utf-8', newline='').read()
    if 'i_arg' not in s:
        return 0
    n = 0

    def repl(m):
        nonlocal n
        params = split_params(m.group(4))
        end = s.find(chr(10) + '}', m.end())
        if 'i_arg' in s[m.end():end if end > 0 else len(s)]:
            return m.group(0)
        names = find_names(m.group(2), m.group(3), params)
        if not names:
            return m.group(0)
        n += 1
        new = [re.sub(r'\bi_arg\d*\b', nm, p) for p, nm in zip(params, names)]
        return '%s%s::%s(%s)%s' % (m.group(1), m.group(2), m.group(3), ', '.join(new), m.group(5) or '')

    out = DEF.sub(repl, s)
    if n and not dry:
        open(path, 'w', encoding='utf-8', newline='').write(out)
    return n


# -- nums --

ENUM_CACHE = os.path.join(config.BUILD, 'enum_index.json')
SENTINEL = re.compile(r'(COUNT|MAX|NUM|LAST|FIRST|BEGIN|END|SIZE|TOTAL)$|(Count|Max|Num|Last|First|Begin|End|Size|Total)$')
SCAN = re.compile(r'\b(?:class|struct|union|namespace)\s+(?:\w+\s+)?(\w+)\s*(?:final\s*)?(?::[^;{}()]*)?\{'
                  r'|\benum\s+(class\s+|struct\s+)?(\w+)?\s*(?::\s*[\w:\s]+?)?\s*\{([^{}]*)\}'
                  r'|[{}]')


def _eval(expr, known):
    expr = re.sub(r'\(\s*(?:unsigned\s+)?(?:int|long|short|char|u?int\d+_t)\s*\)', '', expr)
    expr = re.sub(r'\b(0x[0-9a-fA-F]+|\d+)[uUlL]*\b', r'\1', expr)
    expr = re.sub(r'\b[A-Za-z_]\w*(?:::\w+)*\b', lambda m: str(known[m.group(0).split('::')[-1]])
                  if m.group(0).split('::')[-1] in known else m.group(0), expr)
    if not re.fullmatch(r'[\s0-9a-fA-Fx()+\-*|&<>~^]*', expr):
        return None
    try:
        return int(eval(expr, {'__builtins__': {}}))
    except Exception:
        return None


def _parse_body(body):
    vals, cur, known = {}, -1, {}
    for item in split_params(body.replace('\n', ' ')):
        m = re.match(r'(\w+)\s*(?:=\s*(.+))?$', item.strip())
        if not m:
            continue
        name, expr = m.groups()
        cur = _eval(expr, known) if expr else (None if cur is None else cur + 1)
        if cur is not None:
            vals[name] = known[name] = cur
    return vals


def build_enums():
    idx = {}
    for path, raw in headers():
        text, stack = strip_comments(raw), []
        for m in SCAN.finditer(text):
            tok = m.group(0)
            if m.group(1):
                stack.append(m.group(1))
            elif tok.startswith('enum'):
                if m.group(3):
                    idx.setdefault(m.group(3), []).append({
                        'scope': [s for s in stack if s], 'scoped': bool(m.group(2)),
                        'values': _parse_body(m.group(4)), 'header': os.path.relpath(path, ROOT)})
            elif tok == '{':
                stack.append(None)
            elif stack:
                stack.pop()
    os.makedirs(config.BUILD, exist_ok=True)
    json.dump(idx, open(ENUM_CACHE, 'w'))
    return idx


def enums():
    if 'enums' not in _hdr_cache:
        fresh = os.path.exists(ENUM_CACHE) and os.path.getmtime(ENUM_CACHE) > os.path.getmtime(INC)
        _hdr_cache['enums'] = json.load(open(ENUM_CACHE)) if fresh else build_enums()
    return _hdr_cache['enums']


def enum_for(type_name):
    """The one enum a (maybe qualified) type name means, or None if unknown/ambiguous."""
    parts = type_name.replace(' ', '').split('::')
    cands = [e for e in enums().get(parts[-1], []) if e['scope'][-len(parts) + 1:] == parts[:-1] or len(parts) == 1]
    distinct = {json.dumps(e['values'], sort_keys=True) for e in cands}
    return cands[0] if len(distinct) == 1 and cands[0]['values'] else None


def spellings(enum, type_name, value, cls):
    names = [n for n, v in enum['values'].items() if v == value]
    names = [n for n in names if not SENTINEL.search(n)] or names
    if not names:
        return []
    scope = enum['scope'] + ([type_name.split('::')[-1]] if enum['scoped'] else [])
    # shortest spelling first; one that names another enum's constant fails the byte check
    last = len(scope) - 1 if enum['scoped'] else len(scope)
    return ['::'.join(scope[i:] + [names[0]]) for i in range(last, -1, -1)]


def _class_text(cls, depth=0):
    from lib import hdrindex
    hdr = hdrindex.header_of(cls)
    if not hdr or depth > 6:
        return ''
    text = strip_comments(open(os.path.join(ROOT, hdr), encoding='utf-8', errors='ignore').read())
    m = re.search(r'\b(?:class|struct)\s+(?:\w+\s+)?' + re.escape(cls) + r'\s*(?:final\s*)?(:[^;{]*)?\{', text)
    out = text
    if m and m.group(1):
        for base in re.findall(r'(?:public|protected|private)?\s*([\w:]+)', m.group(1)[1:]):
            if base not in ('public', 'protected', 'private', 'virtual'):
                out += _class_text(base.split('::')[-1], depth + 1)
    return out


def type_of(expr, cls, body):
    """Declared type of `m_x`, `local`, `GetX()` or `this->m_x` seen from a method of cls."""
    expr = re.sub(r'^this->', '', expr.strip())
    getter = re.fullmatch(r'(\w+)\(\)', expr)
    name = getter.group(1) if getter else expr
    if not re.fullmatch(r'\w+', name):
        return None
    if not getter and not name.startswith('m_'):
        decl = re.findall(r'(?:^|[(,;{\s])((?:const\s+)?[A-Za-z_][\w:]*)\s+' + re.escape(name) + r'\s*[=;,)\[]', body)
        decl = [d.replace('const ', '') for d in decl if d not in NOT_TYPES]
        if decl:
            return decl[-1]
    if not cls:
        return None
    pat = (r'([A-Za-z_][\w:]*)\s+' + re.escape(name) + r'\s*\(\s*(?:void)?\s*\)') if getter else \
          (r'([A-Za-z_][\w:]*)\s+' + re.escape(name) + r'\s*[;=\[:]')
    hits = [t for t in re.findall(pat, _class_text(cls)) if t not in NOT_TYPES]
    return hits[0] if hits else None


NOT_TYPES = {'return', 'const', 'else', 'case', 'new', 'delete', 'goto', 'typedef', 'virtual', 'static', 'inline'}
WORTH = re.compile(r'(?i)state|type|mode|kind|reason|phase|cond|flag|tag|status|action|result|stage|category|rarity|^case')
LIT = r'(-?(?:0x[0-9a-fA-F]+|\d+))[uU]?'
OPERAND = r'((?:this->)?\w+(?:\(\))?)'
SITES = [
    re.compile(r'\(\s*([A-Z][\w:]*)\s*\)\s*' + LIT + r'\b'),
    re.compile(OPERAND + r'\s*(?:==|!=)\s*' + LIT + r'\b'),
    re.compile(LIT + r'\s*(?:==|!=)\s*' + OPERAND + r'(?!\w|\()'),
    re.compile(OPERAND + r'\s*=\s*' + LIT + r'\s*;'),
]
FUNC = re.compile(r'^[^\s#/].*?\b(\w+)::~?\w+\s*\([^;]*$', re.M)


def find_sites(text):
    """[(start, end, type_name, value, cls)] for each enum-typed literal, plus [(line, snippet)] left unresolved."""
    clean = strip_comments(text)
    funcs = [(m.start(), m.group(1)) for m in FUNC.finditer(clean)]

    def owner(pos):
        prev = [f for f in funcs if f[0] <= pos]
        return prev[-1] if prev else (0, None)

    sites, left = [], []

    def add(pos_lit, lit, type_name, cls, snippet):
        e = enum_for(type_name) if type_name else None
        val = int(lit, 0)
        if e and any(v == val for v in e['values'].values()):
            sites.append((pos_lit, pos_lit + len(lit), type_name, val, cls, e))
        elif type_name or WORTH.search(snippet):
            left.append((clean.count('\n', 0, pos_lit) + 1, snippet.strip(), type_name))

    for i, rx in enumerate(SITES):
        for m in rx.finditer(clean):
            start, cls = owner(m.start())
            body = clean[start:m.start()]
            if i == 0:
                if m.group(1) in ('int', 'unsigned', 'float', 'double', 'char', 'bool', 'long', 'short', 'size_t'):
                    continue
                if not enum_for(m.group(1)):
                    continue
                sites.append((m.start(), m.end(), m.group(1), int(m.group(2), 0), cls, enum_for(m.group(1))))
                continue
            opnd, lit = (m.group(2), m.group(1)) if i == 2 else (m.group(1), m.group(2))
            if opnd in ('nullptr', 'NULL', 'true', 'false') or re.fullmatch(r'\d+', opnd):
                continue
            t = type_of(opnd, cls, body)
            if t and not enum_for(t):
                continue
            add(m.start(2 if i != 2 else 1), lit, t, cls, m.group(0))
    for m in re.finditer(r'\bswitch\s*\(\s*' + OPERAND + r'\s*\)\s*\{', clean):
        start, cls = owner(m.start())
        t = type_of(m.group(1), cls, clean[start:m.start()])
        if t and not enum_for(t):
            continue
        depth, j = 1, m.end()
        while depth and j < len(clean):
            depth += {'{': 1, '}': -1}.get(clean[j], 0)
            j += 1
        for c in re.finditer(r'\bcase\s+' + LIT + r'\s*:', clean[m.end():j]):
            add(m.end() + c.start(1), c.group(1), t, cls, c.group(0))
    seen, out = set(), []
    for s in sorted(sites, key=lambda s: s[0]):
        if not any(a < s[1] and s[0] < b for a, b in seen):
            seen.add((s[0], s[1]))
            out.append(s)
    return out, left


def signature(obj):
    """Everything code-relevant in an object: defined symbols, section bytes and relocations."""
    from lib.pvzelf import Elf
    e = Elf(obj)
    syms = sorted((n, s, t) for n, v, s, sh, t in e.symbols() if sh and n)
    secs = []
    for sh in e._sh:
        nm = sh[-1]
        if not nm or nm.startswith(('.debug', '.comment', '.note', '.rela', '.rel.', '.symtab', '.strtab', '.shstrtab')):
            continue
        secs.append((nm, e.section_bytes(nm) if sh[1] != 8 else sh[4], sorted(e.relocations(nm).items())))
    return syms, secs


def tidy_nums(path, dry, report):
    from lib import fastcc
    text = open(path, encoding='utf-8', newline='').read()
    sites, left = find_sites(text)
    if report:
        for ln, snip, t in left:
            print(f'  {os.path.basename(path)}:{ln}: {snip}' + (f'   ({t})' if t else ''))
    if not sites:
        return 0
    obj, err = fastcc.compile_file(path, pch=True)
    if obj is None:
        print('  does not compile, skipped:', path)
        return 0
    want = signature(obj)
    tmp = os.path.join(config.BUILD, 'tidy', os.path.basename(path)[:-4] + '.o')

    def apply(chosen):
        out, last = [], 0
        for (s, e, *_), sp in sorted(chosen, key=lambda c: c[0][0]):
            out += [text[last:s], sp]
            last = e
        return ''.join(out + [text[last:]])

    def same(chosen):
        o, _ = fastcc.compile_text(path, apply(chosen), tmp)
        return o is not None and signature(o) == want

    plan = [(s, spellings(s[5], s[2], s[3], s[4])) for s in sites]
    plan = [(s, sp) for s, sp in plan if sp]
    chosen = [(s, sp[0]) for s, sp in plan]
    if not same(chosen):
        chosen = []
        for s, sp in plan:
            for name in sp:
                if same(chosen + [(s, name)]):
                    chosen.append((s, name))
                    break
    for (s, e, t, v, *_), name in chosen:
        print(f'  {os.path.basename(path)}:{text.count(chr(10), 0, s) + 1}: {text[s:e]} -> {name}')
    if chosen and not dry:
        open(path, 'w', encoding='utf-8', newline='').write(apply(chosen))
    return len(chosen)


# -- layout --

SECTION = '/////////////// %s ///////////////'


def blocks(text):
    out, cur, depth = [], [], 0
    for ln in text.split('\n'):
        cur.append(ln)
        depth += ln.count('{') - ln.count('}')
        if depth == 0 and (ln.startswith('}') or ln.rstrip().endswith(';') or ln.startswith('#include') or ln.startswith('RT_CLASS')):
            out.append('\n'.join(cur).strip('\n'))
            cur = []
    if ''.join(cur).strip():
        out.append('\n'.join(cur).strip('\n'))
    return [b for b in out if b.strip()]


def classify(b):
    m = re.search(r'(\w+)::(~?)(\w+)\(', b.split('\n{')[0] if '\n{' in b else b)
    if b.startswith('RT_CLASS') or (m and m.group(3) in ('StaticClassInit', 'StaticNew', 'StaticGetClass', 'GetClass', 'IsAbstract')):
        return 'Reflection'
    if m and (m.group(2) or m.group(1) == m.group(3)):
        return 'Lifecycle'
    if m and re.match(r'(Get|Set|Is|Has)[A-Z]', m.group(3)) and b.count('\n') <= 6:
        return 'Accessors'
    return 'Logic'


def tidy_layout(path, dry):
    raw = open(path, encoding='utf-8', newline='').read()
    nl = '\r\n' if '\r\n' in raw else '\n'
    text = raw.replace('\r\n', '\n')
    if '////////' in text:
        return 0
    ls = text.split('\n')
    end = 0
    for i, ln in enumerate(ls):
        if ln.startswith('#include'):
            end = i
        elif ln.strip() and not ln.startswith('//'):
            break
    head_end = len('\n'.join(ls[:end + 1]))
    head, bs = text[:head_end], blocks(text[head_end:])
    incs = [b for b in bs if b.startswith('#include')]
    groups = {}
    for b in bs:
        if not b.startswith('#include'):
            groups.setdefault(classify(b), []).append(b)
    out = head + ('\n' + '\n'.join(incs) if incs else '')
    for g in ['Lifecycle', 'Reflection', 'Accessors', 'Logic']:
        if g in groups:
            out += '\n\n' + SECTION % g + '\n\n' + '\n\n'.join(groups[g])
    if not dry:
        open(path, 'w', encoding='utf-8', newline='').write((out.rstrip('\n') + '\n').replace('\n', nl))
    return 1


def main():
    args = sys.argv[1:]
    mode = args.pop(0) if args and args[0] in ('args', 'nums', 'layout') else None
    dry, report = '--dry' in args, '--report' in args
    files = [os.path.abspath(a) for a in args if not a.startswith('--')]
    if not files:
        if mode == 'layout':
            sys.exit('layout needs files')
        for d, _, fs in os.walk(os.path.join(ROOT, 'src')):
            files += [os.path.join(d, f) for f in fs if f.endswith('.cpp')]
    tot = {'args': 0, 'nums': 0, 'layout': 0}
    for f in sorted(files):
        if mode in (None, 'args'):
            tot['args'] += tidy_args(f, dry)
        if mode in (None, 'nums'):
            tot['nums'] += tidy_nums(f, dry, report)
        if mode == 'layout' or (mode is None and len(files) < 20):
            tot['layout'] += tidy_layout(f, dry)
    print(' '.join(f'{k} {v}' for k, v in tot.items() if mode in (None, k)) + (' (dry run)' if dry else ''))


if __name__ == '__main__':
    main()
