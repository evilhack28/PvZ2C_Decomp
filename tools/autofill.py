"""Auto-write missing methods, ctors and dtors into a .cpp (patching headers when needed), keeping only what compiles to OK (autofill.py <file.cpp> [--min N] [--dry])."""

import argparse
import datetime
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from lib import asmdiff
import config
from lib import fastcc
import guess as G
from lib import ctorinit
from lib import foldcopy
from lib import hdrindex
import progress as P
from lib.pvzelf import Elf

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), os.pardir)
CD = re.compile(r'^_ZN(?:\d+[A-Za-z_]\w*?)*?(C[12]|D[012])E')


def write(path, text):
    # an unchanged header keeps its mtime, so its precompiled header stays valid
    if os.path.exists(path) and read(path) == text:
        return
    open(path, 'w', encoding='utf-8', newline='').write(text)


def read(path):
    return open(path, encoding='utf-8', errors='replace', newline='').read()


def compile_obj(src, obj):
    o, err = fastcc.compile_file(src, obj, force=True, pch=True)
    return o is not None, [l for l in err.splitlines() if 'error:' in l]


def header_path(cls):
    rel = hdrindex.header_of(cls)
    return os.path.join(ROOT, rel) if rel else None


def header_text(cls):
    p = header_path(cls)
    return read(p) if p else ''


def class_of_cd(sym):
    """Class name if sym is a plain constructor/destructor symbol."""
    if not CD.match(sym):
        return None
    comps = P._components(sym)
    return comps[-1][0] if comps else None


def split_params(text):
    out, depth, cur = [], 0, ''
    for c in text:
        if c in '<(':
            depth += 1
        elif c in '>)':
            depth -= 1
        if c == ',' and depth == 0:
            out.append(cur.strip())
            cur = ''
        else:
            cur += c
    if cur.strip():
        out.append(cur.strip())
    return out


def find_inline(text, cls, name):
    """(ret, params, start, end) of a unique inline definition of cls::name in a header, or None."""
    body = ctorinit.class_body(text, cls)
    if not body:
        return None
    base = text.index(body)
    pat = re.compile(r'^([ \t]*)((?:virtual|static|inline|explicit)\s+)*([\w:<>,\*&\s]+?)\s*[\*&]?\s*\b' + re.escape(name) +
                     r'\s*\(([^)]*)\)\s*(const)?\s*(override)?\s*\{', re.M)
    found = list(pat.finditer(body))
    if len(found) != 1 or 'static' in (found[0].group(2) or ''):
        return None
    m = found[0]
    depth, end = 0, None
    for j in range(m.end() - 1, len(body)):
        if body[j] == '{':
            depth += 1
        elif body[j] == '}':
            depth -= 1
            if depth == 0:
                end = j + 1
                break
    if end is None:
        return None
    params = [re.sub(r'\s*=.*$', '', x) for x in split_params(m.group(4))]
    sig = body[m.start():m.end() - 1].rstrip()
    ret = re.sub(r'\b(virtual|static|inline|explicit)\b', '', sig.split(name + '(')[0].replace('\r', '').split('\n')[-1]).strip()
    return ret, params, base + m.start(), base + end, sig + ';'


def declify(text, cls, name):
    f = find_inline(text, cls, name)
    if not f:
        return None
    _, _, s, e, sig = f
    return text[:s] + sig + text[e:]


def class_text(cls):
    """The class body from its header, or the whole header when the body cannot be isolated."""
    h = header_text(cls)
    return ctorinit.class_body(h, cls) or h


def decl_for(cls, name, nparams):
    hdr = class_text(cls)
    pat = re.compile(r'^[ \t]*((?:virtual|static|inline|explicit)\s+)*([\w:<>,\*&\s]+?)\s*[\*&]?\s*\b' + re.escape(name) +
                     r'\s*\(([^)]*)\)\s*(const)?\s*(override)?\s*;', re.M)
    for m in pat.finditer(hdr):
        params = [re.sub(r'\s*=.*$', '', p) for p in split_params(m.group(3))]
        if len(params) == nparams and 'static' not in (m.group(1) or ''):
            ret = m.group(0).split(name + '(')[0]
            ret = re.sub(r'\b(virtual|static|inline|explicit)\b', '', ret.replace(chr(13), '').split(chr(10))[-1]).strip()
            return ret, params
    return None


def decl_unique(cls, name):
    """The one declaration of cls::name whatever its parameters, or None if absent or overloaded."""
    hdr = class_text(cls)
    pat = re.compile(r'^[ \t]*((?:virtual|static|inline|explicit)\s+)*([\w:<>,\*&\s]+?)\s*[\*&]?\s*\b' + re.escape(name) +
                     r'\s*\(([^)]*)\)\s*(const)?\s*(override)?\s*;', re.M)
    found = list(pat.finditer(hdr))
    if len(found) != 1 or 'static' in (found[0].group(1) or ''):
        return None
    m = found[0]
    params = [re.sub(r'\s*=.*$', '', x) for x in split_params(m.group(3))]
    ret = re.sub(r'\b(virtual|static|inline|explicit)\b', '', m.group(0).split(name + '(')[0].replace(chr(13), '').split(chr(10))[-1]).strip()
    return ret, params


def name_params(params):
    out = []
    for i, p in enumerate(params):
        nm = 'i_arg' if len(params) == 1 else 'i_arg%d' % i
        if ' ' in p and re.search(r'\w+$', p) and not re.search(r'[*&]$', p) and not p.endswith('>'):
            p = re.sub(r'\s*\w+$', '', p)
        out.append('%s %s' % (p, nm))
    return out


def insert_member(text, cls, decl):
    m = re.search(r'^\s*(class|struct)\s+(?:\w+\s+)?' + re.escape(cls) + r'\s*(?:final\s*)?(?::[^;{]*)?\{', text, re.M)
    if not m:
        return None
    pre = 'public:\n' if m.group(1) == 'class' else ''
    return text[:m.end()] + '\n' + pre + '\t' + decl + '\n' + text[m.end():]


def ctor_dtor_candidates(todo, gsyms):
    """[(kind, cls, syms, cpp, header_decl_or_None)] for default ctors and dtors."""
    groups = {}
    for s in todo:
        c = class_of_cd(s)
        if c:
            groups.setdefault((c, 'D' if 'D' in CD.match(s).group(1) else 'C'), []).append(s)
    out = []
    for (cls, kind), syms in groups.items():
        h = header_text(cls)
        if not h:
            continue
        if kind == 'D':
            declared = re.search(r'~' + cls + r'\s*\(\s*\)\s*(?:override)?\s*;', h)
            inline = re.search(r'~' + cls + r'\s*\(\s*\)\s*(?:override)?\s*\{', h)
            if inline:
                continue
            virt = any(n.startswith('_ZTV%d%s' % (len(cls), cls)) for n in gsyms)
            decl = None if declared else ('virtual ~%s();' % cls if virt else '~%s();' % cls)
            out.append((kind, cls, syms, '%s::~%s()\n{\n}\n' % (cls, cls), decl))
        else:
            has_any = re.search(r'(?<![~\w])' + cls + r'\s*\(', h)
            declared = re.search(r'(?<![~\w])' + cls + r'\s*\(\s*\)\s*;', h)
            if has_any and not declared:
                continue
            c2 = [x for x in syms if 'C2E' in x] or syms
            inits = ctorinit.body_lines(cls, c2[0])
            out.append((kind, cls, syms, '%s::%s()\n{\n%s}\n' % (cls, cls, inits), None if declared else '%s();' % cls))
    return out


def todo_symbols(obj):
    ours = Elf(obj)
    defined, strong = set(), set()
    for n, v, s, sh, t, b in ours.symbols_full():
        if sh and t == 2 and s:
            defined.add(n)
            if b == 1:
                strong.add(n)
    _, _, gnames = P._game()
    owners = {}
    for n in defined:
        o = P.owned_prefixes(n)
        if o and (n in strong or o.zn in P.EXTRA_OWNED):
            owners[o.zn] = o
    todo = set()
    for o in owners.values():
        for n in P._range(gnames, o.zn) + P._range(gnames, o.znk):
            if n not in defined:
                todo.add(n)
    return sorted(todo)


def method_candidates(todo, gelf, gs, minconf):
    out = []
    for sym in todo:
        if class_of_cd(sym):
            continue
        _, body, conf, why = G.guess(gelf, gs, sym)
        comps = P._components(sym)
        if body and len(comps) >= 2 and '/*+' in body:
            offs = ctorinit.offsets(comps[-2][0])
            body = re.sub(r'/\*\+(0x[0-9a-f]+)\*/', lambda mm: offs.get(int(mm.group(1), 16), '/*?*/'), body)
        if not body or conf < minconf or '/*' in body or '//' in body or 'i_on' in body:
            continue
        if len(comps) < 2:
            continue
        cls, meth = comps[-2][0], comps[-1][0]
        rest = sym[comps[-1][1]:]
        d = decl_for(cls, meth, 0) if rest in ('Ev', 'v', '') else None
        if not d:
            d = decl_unique(cls, meth)
        hop = None
        if not d:
            fi = find_inline(header_text(cls), cls, meth)
            if not fi:
                continue
            d, hop = (fi[0], fi[1]), ('declify', meth)
        ret, params = d
        if ret.endswith('&') and re.fullmatch(r'\{\n\treturn &[\w.%]+;\n\}', body):
            body = body.replace('return &', 'return ')
        if re.fullmatch(r'\{\n\treturn [\w%]+;\n\}', body) and re.fullmatch(r'(?:const\s+)?[A-Z]\w*', ret):
            body = body.replace('return ', 'return (%s)' % ret)
        if 'i_arg' in body and len(params) != 1:
            continue
        if '%M' in body:
            def sub(mm):
                return ctorinit.offsets(cls).get(int(mm.group(1), 16), '@@')
            body = re.sub(r'%(M0x[0-9a-f]+)%', lambda mm: ctorinit.offsets(cls).get(int(mm.group(1)[1:], 16), '@@'), body)
            if '@@' in body:
                continue
        body = re.sub(r'\t(\w+) = ([2-9]|\d\d+);', lambda mm: '\t%s = (decltype(%s))%s;' % (mm.group(1), mm.group(1), mm.group(2)), body)
        if '__TAIL__' in body:
            body = body.replace('__TAIL__', '' if ret == 'void' or ret.endswith(' void') else 'return')
        const = ' const' if sym.startswith('_ZNK') else ''
        inc = ''
        tm = re.search(r'(\w+)::\w+\(\)', body)
        if tm and header_path(tm.group(1)):
            inc = '#include "%s"\n' % os.path.basename(header_path(tm.group(1)))
        out.append(('M', cls, [sym], '%s%s %s::%s(%s)%s\n%s\n' % (inc, ret, cls, meth, ', '.join(name_params(params)), const, body), hop))
    return out


def field_lines(cls, base=''):
    """Full StaticClassInit body for cls: one BEGIN/END block per reflected type the game registers (None if a member is missing)."""
    from lib import fields as F
    e = Elf(config.TARGET_LIB)
    blocks = F.blocks(e, '_ZN%d%s15StaticClassInitEv' % (len(cls), cls))
    if not blocks:
        return ''
    out = ''
    for name, fnaddr, size in blocks:
        h = header_text(name)
        body = ctorinit.class_body(h, name) if h else None
        h = body or h or header_text(cls)
        lines = ''
        for key, typ, off in F.fields_typed(e, fnaddr):
            var = ctorinit.find_member(name, key) or ctorinit.find_member(cls, key)
            if not var:
                return None
            if var == key:
                lines += '\t\tREFLECTION_CLASSBUILDER_FIELD(%s, %s);\n' % (typ, key)
            else:
                lines += '\t\tREFLECTION_CLASSBUILDER_FIELD_DIFF_NAME(%s, %s, %s);\n' % (typ, var, key)
        if name == cls:
            out += ('\tREFLECTION_CLASSBUILDER_BEGIN(%s);\n\tREFLECTION_CLASSBUILDER_RTCLASS_BIND;\n\n'
                    '\t\tREFLECTION_CLASSBUILDER_ANCESTOR(%s);\n\n%s\tREFLECTION_CLASSBUILDER_END(%s);\n' % (cls, base, lines, cls))
        else:
            out += '\tREFLECTION_CLASSBUILDER_BEGIN(%s);\n%s\tREFLECTION_CLASSBUILDER_END(%s);\n\n' % (name, lines, name)
    return out


def rt_candidates(todo):
    """RT_CLASS_IMPLEMENT + a field-less StaticClassInit for classes whose header uses RT_CLASS_DEFINE."""
    out, seen = [], set()
    for sym in todo:
        comps = P._components(sym)
        if len(comps) < 2 or comps[-1][0] not in ('StaticClassInit', 'StaticGetClass', 'StaticNew'):
            continue
        cls = comps[-2][0]
        if cls in seen:
            continue
        m = re.search(r'RT_CLASS_DEFINE(_ABSTRACT)?\(\s*' + re.escape(cls) + r'\s*,\s*([\w:]+)', header_text(cls))
        if not m:
            continue
        seen.add(cls)
        fl = field_lines(cls, m.group(2))
        names = {}
        for x in todo:
            cc = P._components(x)
            if len(cc) > 1 and cc[-2][0] == cls:
                names.setdefault(cc[-1][0], []).append(x)
        rt = [x for n in ('StaticGetClass', 'StaticNew', 'IsAbstract', 'GetClass') for x in names.get(n, [])]
        impl = '#include "ReflectionBuilder.h"\n\nRT_CLASS_IMPLEMENT%s(%s);\n' % (m.group(1) or '', cls)
        out.append(('R', cls, rt, impl, None))
        if fl is not None and names.get('StaticClassInit'):
            text = 'void %s::StaticClassInit()\n{\n%s}\n' % (cls, fl)
            out.append(('I', cls, names['StaticClassInit'], text, None))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('source')
    ap.add_argument('--min', type=int, default=60)
    ap.add_argument('--dry', action='store_true')
    args = ap.parse_args()
    src = os.path.abspath(args.source)
    orig0 = orig = read(src)
    obj = os.path.join(config.BUILD, 'autofill_%d.o' % os.getpid())
    os.makedirs(config.BUILD, exist_ok=True)
    stub = P.is_stub(src)
    funcs = []
    if stub:
        rel = os.path.relpath(src, ROOT).replace(os.sep, '/')
        funcs = json.load(open(os.path.join(ROOT, 'units.json')))['units'].get(rel, {}).get('funcs', [])
        cls_all = set()
        for f, _ in funcs:
            c = class_of_cd(f)
            comps = P._components(f)
            cls_all.add(c or (comps[-2][0] if len(comps) > 1 else None))
        heads = sorted({os.path.basename(hdrindex.header_of(c)) for c in cls_all if c and hdrindex.header_of(c)})
        head = ('//\n//  %s\n//\n//  Base PvZ2C (arm64-v8a, 3.5.7).\n//  Reconstructed by %s on %s.\n//\n\n'
                % (os.path.basename(src), config.AUTHOR, datetime.date.today()))
        orig = head + '#include "SexyAppFramework/Common.h"\n\n' + ''.join('#include "%s"\n' % h for h in heads)
    write(src, orig)
    # the base file is the shared cached object unless it is a fresh stub
    base, err = fastcc.compile_file(src, pch=True)
    ok, errs = base is not None, [l for l in (err or '').splitlines() if 'error:' in l]
    if not ok:
        write(src, orig0)
        sys.exit('base file does not compile:\n' + '\n'.join(errs[:3]))

    game, gsyms, _ = P._game()
    gelf = Elf(config.TARGET_LIB)
    gs = G.load_syms(gelf)
    todo = sorted({f for f, _ in funcs}) if stub else todo_symbols(base)
    cands = ctor_dtor_candidates(todo, gsyms) + rt_candidates(todo) + method_candidates(todo, gelf, gs, args.min)
    have = {x for c in cands for x in c[2]}
    rest = [x for x in todo if x not in have]
    cands += [('F', cls, [sym], text + '\n', None) for sym, cls, text in foldcopy.candidates(rest)]
    if not cands:
        write(src, orig0)
        print('nothing to fill')
        return
    if args.dry:
        write(src, orig0)
        for c in cands:
            print(c[3])
        return

    backups = {}

    def apply(active):
        want = dict(backups)
        text = orig.rstrip('\n') + '\n\n' + '\n'.join(c[3] for c in active)
        for c in active:
            if c[4]:
                hp = header_path(c[1])
                cur = want[hp] if hp in want else backups.setdefault(hp, read(hp))
                new = declify(cur, c[1], c[4][1]) if isinstance(c[4], tuple) else insert_member(cur, c[1], c[4])
                if new:
                    want[hp] = new
        for p, t in want.items():
            write(p, t)
        write(src, text)
        return text

    def restore_headers():
        for p, t in backups.items():
            write(p, t)

    active = list(cands)
    for _ in range(12):
        text = apply(active)
        ok, errs = compile_obj(src, obj)
        if ok:
            break
        if os.environ.get('AF_DEBUG'):
            print('\n'.join(e[-160:] for e in errs[:6]))
        bad, recast = set(), {}
        base_lines = len(orig.rstrip('\n').split('\n')) + 2
        pos = base_lines
        spans = []
        for c in active:
            n = c[3].count('\n')
            spans.append((pos, pos + n + 1, c))
            pos += n + 1
        for e in errs:
            m = re.search(r'([^:\s][^:]*):(\d+):\d+: error', e)
            if not m:
                continue
            f, ln = m.group(1), int(m.group(2))
            if os.path.abspath(f) == src:
                for lo, hi, c in spans:
                    if lo <= ln < hi:
                        if 'invalid conversion from' in e and 'decltype' not in c[3] and re.search(r'	\w+ = \d+;', c[3]):
                            recast[id(c)] = (c[0], c[1], c[2], re.sub(r'\t(\w+) = (\d+);', r'\t\1 = (decltype(\1))\2;', c[3]), c[4])
                        else:
                            bad.add(id(c))
            else:
                for c in active:
                    if c[4]:
                        bad.add(id(c))
        if not bad and not recast:
            bad = {id(c) for c in active}
        active = [recast.get(id(c), c) for c in active if id(c) not in bad]
        if not active:
            break
    if not active or not ok:
        restore_headers()
        write(src, orig0)
        print('no candidate compiled')
        return

    if os.environ.get('AF_KEEP'):
        print('kept all drafts for inspection')
        return
    for _ in range(3):
        ours = Elf(obj)
        good = []
        for c in active:
            allok = True
            for sym in c[2]:
                th, mn = asmdiff.listing(game, sym), asmdiff.listing(ours, sym)
                if th is None:
                    continue
                if mn is None:
                    allok = False
                    break
                same, tot, _ = asmdiff.compare(th, mn)
                if not (same == tot and len(th) == len(mn)):
                    if os.environ.get('AF_DEBUG'):
                        print('  miss %d/%d (game %d ours %d) %s' % (same, tot, len(th), len(mn), P.pretty(sym)))
                    allok = False
                    break
            if allok:
                good.append(c)
        if len(good) == len(active):
            break
        active = good
        if not active:
            break
        apply(active)
        ok, _ = compile_obj(src, obj)
        if not ok:
            active = []
            break

    if not active:
        restore_headers()
        write(src, orig0)
        print('0/%d drafts OK' % len(cands))
        return
    print('%d/%d drafts OK:' % (len(active), len(cands)))
    for c in active:
        print('  ' + c[1] + ('::~' if c[0] == 'D' else '::ctor' if c[0] == 'C' else ' ') + ('' if c[0] != 'M' else P.pretty(c[2][0]).split('::')[-1]) + ('  [header patched]' if c[4] else ''))


if __name__ == '__main__':
    main()
