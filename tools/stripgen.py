"""Take every compiler-generated template instantiation out of units.json and score only developer-written functions."""
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import config
import tmplown
from progress import is_stub


def main():
    base = os.path.join(config.BUILD, 'tmpl', 'units.before.json')
    data = json.load(open(base))
    units = data['units']
    syms = sorted({s for d in units.values() for s, _ in d['funcs']})
    dem = tmplown.demangle(syms)
    gen = sorted(s for s in syms if tmplown.is_template(dem[s]))
    genset = set(gen)
    gone = 0
    for u in list(units):
        d = units[u]
        d.pop('moved_in', None)
        d.pop('moved_out', None)
        keep = [f for f in d['funcs'] if f[0] not in genset]
        gone += len(d['funcs']) - len(keep)
        d['funcs'] = keep
        d['code'] = sum(z for _, z in keep)
    data['generated'] = gen
    json.dump(data, open(os.path.join(config.HERE, 'units.json'), 'w'))
    for d_, _, fs in os.walk(os.path.join(config.HERE, 'src')):
        for f in fs:
            full = os.path.join(d_, f)
            rel = os.path.relpath(full, config.HERE).replace(os.sep, '/')
            if f.endswith('.cpp') and is_stub(full) and not tmplown.tracked(rel) and not units.get(rel, {}).get('funcs'):
                os.remove(full)
    print(f'{len(gen)} generated symbols removed ({gone} entries) from units.json; {sum(len(d["funcs"]) for d in units.values())} developer functions left')


if __name__ == '__main__':
    main()
