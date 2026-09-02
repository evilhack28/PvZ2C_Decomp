"""Regenerate the src/ tree: one stub .cpp per translation unit, plus
units.json (unit -> [[symbol, size], ...]).

    py -3 tools/scaffold.py [--dry-run]

A class is placed by: library class families, then a source-tree manifest,
then a same-named header. What matches nothing is listed separately.
regroup() then splits any folder with 4+ files sharing a prefix into a
sub-folder. Handwritten files (HANDWRITTEN) are never touched.
"""

import argparse
import collections
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import config
from pvzelf import Elf
from progress import owned_prefixes, pretty, is_stub, _NAMESPACES

TREE = os.path.join(config.HERE, 'docs', 'original-source-tree.txt')
UNITS = os.path.join(config.HERE, 'units.json')
UNPLACED = os.path.join(config.HERE, 'docs', 'unplaced-symbols.txt')

HANDWRITTEN = {
    'src/PvZ2/plants/Iceburg/Plant_Iceburg.cpp',
    'src/PvZ2/plants/Iceburg/PlantAnimRig_Iceburg.cpp',
    'src/PvZ2/plants/Jalapeno/Plant_Jalapeno.cpp',
    'src/PvZ2/net/gameNetWork/NetworkData.cpp',
    'src/PvZ2/net/gameNetWork/PVPDatas.cpp',
}

# header/source subdir -> where it lands under src/
_SUBDIR_MOVE = {
    'gameNetWork': 'net/gameNetWork',
    'iCloud': 'net/icloud', 'logServer': 'net/log', 'LogCollector': 'net/log',
    'NoticeBoard': 'net/noticeboard', 'wechat': 'net/wechat',
    'OriginMobile': 'net/originmobile',
}

CO_SUFFIXES = ('PropertySheet', 'Properties', 'Props', 'PropSheet', 'Type',
               'Definition', 'Handler')
INCLUDE_MAP = {'PvZ': 'PvZ2', 'SexyAppFramework': 'SexyAppFramework'}

_UI = ('UI', 'Widget', 'Dialog', 'Screen', 'Drawer', 'ListView', 'Button',
       'Popup', 'HUD', 'Panel', 'View', 'Bar', 'Meter', 'Cell', 'Slider',
       'TextEntry', 'Overlay', 'Tab', 'Toast', 'Tooltip')


def _norm(s):
    return s.replace('_', '').lower()


def unit_paths():
    for line in open(TREE):
        line = line.strip()
        if line and not line.startswith('#'):
            yield 'src/' + line


def category(s):
    """Folder under src/PvZ2/ for a flat or header file, or None to keep it flat."""
    if s.startswith('Plant_'):
        return 'plants/' + s[6:]
    if s.startswith('PlantAnimRig_'):
        return 'plants/' + s[13:]
    if s in ('Plant', 'PlantType', 'PlantAnimRig', 'PlantFramework',
             'PlantDefinition', 'PlantProps', 'PlantModule', 'PlantBoost',
             'PlantPropertySheet'):
        return 'plants'
    if s.startswith('ZombieAnimRig_'):
        return 'zombies/' + s[14:]
    if s.startswith('Zomboss'):
        return 'zombies/zomboss'
    if s in ('Zombie', 'ZombieType', 'ZombieAnimRig', 'ZombieAction'):
        return 'zombies'
    if s.startswith('Zombie'):
        return 'zombies/' + s[6:].split('Props')[0].split('PropertySheet')[0]
    if s.startswith('Effect') or s in ('StandaloneEffect', 'ScoreEffect'):
        return 'effects'
    if s.startswith(('GridItem', 'GridSquare')):
        return 'griditems'
    if s.startswith('Powerup') or s == 'BasePowerup':
        return 'powerups'
    if s.startswith('StarChallenge'):
        return 'challenges/star'
    if s.endswith('Challenge') or s.startswith('Challenge'):
        return 'challenges'
    if 'DangerRoom' in s:
        return 'dangerroom'
    if s.startswith('Collectable'):
        return 'collectables'
    if s.startswith('Card'):
        return 'cardgame'
    if s.startswith(('Rift', 'AdaptorRift')) or ('Rift' in s and s.endswith(
            ('Module', 'UI', 'Screen', 'Meter'))):
        return 'PVP/rift'
    if s.startswith(('Joust', 'AdaptorJoust')):
        return 'PVP/joust'
    if s.startswith(('Arena', 'NewPVP', 'NewerPVP', 'PVPMap', 'PvpMap')):
        return 'PVP'
    if s.startswith(('PVZ1Mode', 'PVZ1Dashboard')):
        return 'pvz1mode'
    if s.startswith('PVZ2UnchartedMode'):
        return 'unchartedmode'
    if s.startswith('EASquared'):
        return 'easquared'
    if s.startswith('Dino'):
        return 'dinosaur'
    if s.startswith('Penny'):
        return 'pennyperk'
    if s.startswith('TwoYear'):
        return 'events/anniversary'
    if s.startswith('Present'):
        return 'events/present'
    if s.startswith(('Festival', 'SpringGift', 'Christmas', 'NationalDay',
                     'LanternRiddles', 'IceYear')) or (
            s.startswith('Active') and s != 'ActiveCenter'):
        return 'events'
    if s.startswith('Seed'):
        return 'seedbank'
    if s.startswith('WorldMap') or s in ('UniverseMap', 'WorldData'):
        return 'worldmap'
    if s.startswith(('Board', 'Lawn', 'MiniBoard')):
        return 'board'
    if s.startswith(('Level', 'CustomLevel')):
        return 'level'
    if s.startswith('Intro') or 'Tutorial' in s:
        return 'tutorials'
    if s.endswith('Minigame'):
        return 'minigames'
    if s.endswith('Module'):
        return 'modules'
    if s.endswith('Stage'):
        return 'stages'
    if s.endswith('Cursor'):
        return 'cursors'
    if s.endswith(('Projectile', 'Missile')) or s in ('Bomb', 'Projectile'):
        return 'projectiles'
    if s.endswith('WaveAction'):
        return 'waveactions'
    if s.startswith('Component'):
        return 'components'
    if s.endswith(('Subsystem', 'SubSystem')):
        return 'subsystems'
    if s.startswith(('ICloud', 'iCloud')):
        return 'net/icloud'
    if 'Wechat' in s or 'WeChat' in s:
        return 'net/wechat'
    if s.startswith('NoticeBoard'):
        return 'net/noticeboard'
    if s.startswith(('TGALog', 'LogCollector', 'LogServer')) or s.endswith('LogMgr'):
        return 'net/log'
    if s.endswith(('Network', 'NetworkTable')) or s.startswith(
            ('PVZPackage', 'PVZVersion', 'PVZRecharge', 'PVZRemote')) or s in (
            'ContentDownloader', 'MagentoService', 'NetworkHelper',
            'OnlineDataPersistor', 'PurchaseBroker'):
        return 'net'
    if s.startswith('HotUI'):
        return 'ui/hotui'
    if s.startswith('Adaptor'):
        return 'ui/adaptors'
    if s.startswith(('UI', 'PVZ2UI', 'PVZUI')) or s.endswith(_UI) or s in (
            'MainMenu', 'StoreUI'):
        return 'ui'
    if 'NameMapper' in s or s.endswith('Mapper'):
        return 'mappers'
    if s.endswith(('Mgr', 'Manager')):
        return 'managers'
    if s.endswith(('Config', 'PropertySheet')):
        return 'data'
    if s.startswith('Cheat') or s.endswith('Cheats'):
        return 'debug'
    return None


def relocate(repo_path):
    parts = repo_path.split('/')
    stem = os.path.splitext(parts[-1])[0]
    if parts[:2] == ['src', 'PvZ2'] and len(parts) == 3:
        cat = category(stem)
        if cat:
            return f'src/PvZ2/{cat}/{parts[-1]}'
    if len(parts) >= 4 and parts[2] in _SUBDIR_MOVE:
        parts[2] = _SUBDIR_MOVE[parts[2]]
        return '/'.join(parts)
    return repo_path


def header_index():
    idx = {}
    root = os.path.join(config.HERE, 'include')
    for dirpath, _d, files in os.walk(root):
        rel = os.path.relpath(dirpath, root).replace(os.sep, '/')
        top = rel.split('/')[0]
        if top not in INCLUDE_MAP:
            continue
        sub = INCLUDE_MAP[top] if rel == top else \
            '/'.join([INCLUDE_MAP[top]] + rel.split('/')[1:])
        for fn in files:
            if not fn.endswith('.h'):
                continue
            stem = fn[:-2]
            cat = category(stem)
            if cat and sub == 'PvZ2':
                target = f'src/PvZ2/{cat}/{stem}.cpp'
            else:
                segs = sub.split('/')
                if len(segs) >= 2 and segs[1] in _SUBDIR_MOVE:
                    segs[1] = _SUBDIR_MOVE[segs[1]]
                target = f'src/{"/".join(segs)}/{stem}.cpp'
            idx.setdefault(_norm(stem), target)
    return idx


def entities(classes, prefix):
    return sorted({c[len(prefix):] for c in classes
                   if c.startswith(prefix) and len(c) > len(prefix)
                   and c[len(prefix)].isupper()})


def build_families(classes):
    """Plant<X>/Zombie<X> -> a folder per entity; GridItem/Effect/Powerup grouped."""
    place = {}

    plant_x = set(entities(classes, 'PlantAnimRig_'))
    plant_x |= {c[5:] for c in classes
                if c.startswith('Plant') and len(c) > 5 and c[5].isupper()
                and 'PlantType' + c[5:] in classes}
    plant_x = {x for x in plant_x if x and x[0].isupper()}
    for x in sorted(plant_x, key=len, reverse=True):
        d = f'src/PvZ2/plants/{x}'
        main = f'{d}/Plant_{x}.cpp'
        for c in (f'Plant{x}', f'PlantType{x}', f'Plant{x}Props',
                  f'Plant{x}PropertySheet', f'PlantProps{x}'):
            place.setdefault(c, main)
        place[f'PlantAnimRig_{x}'] = f'{d}/PlantAnimRig_{x}.cpp'

    zomb_x = set(entities(classes, 'ZombieAnimRig_'))
    zomb_x |= {c[6:] for c in classes
               if c.startswith('Zombie') and len(c) > 6 and c[6].isupper()
               and (c + 'Props' in classes or f'Zombie{c[6:]}PropertySheet' in classes)}
    zomb_x = {x for x in zomb_x if x and x[0].isupper()
              and not x.startswith(('AnimRig', 'Type', 'Condition', 'Action',
                                    'Spawn', 'Attrib', 'Props', 'Skill'))}
    for x in sorted(zomb_x, key=len, reverse=True):
        d = f'src/PvZ2/zombies/{x}'
        main = f'{d}/Zombie{x}.cpp'
        for c in (f'Zombie{x}', f'Zombie{x}Props', f'Zombie{x}PropertySheet',
                  f'ZombieType{x}'):
            place.setdefault(c, main)
        place[f'ZombieAnimRig_{x}'] = f'{d}/ZombieAnimRig_{x}.cpp'

    for c in list(classes):
        if c.startswith('GridItem') and not c.startswith('GridItemType'):
            base = c
            for suf in CO_SUFFIXES:
                if base.endswith(suf) and len(base) > len('GridItem') + len(suf):
                    base = base[:-len(suf)]
                    break
            place.setdefault(c, f'src/PvZ2/griditems/{base}.cpp')
    for x in entities(classes, 'Effect_'):
        place[f'Effect_{x}'] = f'src/PvZ2/effects/Effect_{x}.cpp'
    for x in entities(classes, 'EffectAnimRig_'):
        place[f'EffectAnimRig_{x}'] = f'src/PvZ2/effects/EffectAnimRig_{x}.cpp'
    for c in list(classes):
        if c.startswith('Powerup') and c not in ('Powerup', 'PowerupType', 'PowerupManager'):
            place.setdefault(c, f'src/PvZ2/powerups/{c}.cpp')
    return place


def class_name(sym):
    o = owned_prefixes(sym)
    if not o or not o.toplevel:
        return None
    body, i, last = o.zn[3:], 0, None
    while i < len(body) and body[i].isdigit():
        j = i
        while body[j].isdigit():
            j += 1
        n = int(body[i:j])
        last = body[j:j + n]
        i = j + n
    return last


STUB = '''// {orig}
//
// {n} function(s){bytes} to reconstruct. Generated by tools/scaffold.py.
// Replace this banner with real code; drop a TODO line as its function matches.
//
// classes: {classes}
//
{todo}'''

STUB_TODO_CAP = 80


def write_stub(path, orig, funcs):
    full = os.path.join(config.HERE, path)
    os.makedirs(os.path.dirname(full), exist_ok=True)
    funcs = sorted(funcs, key=lambda f: -f[1])
    classes = sorted({class_name(s) or '?' for s, _ in funcs}) or ['(unknown)']
    lines = [f'// TODO {size:6d} B  {pretty(sym):<52s} {sym}'
             for sym, size in funcs[:STUB_TODO_CAP]]
    if len(funcs) > STUB_TODO_CAP:
        lines.append(f'// ... and {len(funcs) - STUB_TODO_CAP} more (units.json)')
    open(full, 'w').write(STUB.format(
        orig=orig, n=len(funcs) or '?',
        bytes=f', {sum(s for _, s in funcs)} B' if funcs else '',
        classes=', '.join(classes),
        todo='\n'.join(lines) + ('\n' if lines else '')))


_W = re.compile(r'[A-Z][a-z0-9]*|[A-Z]+(?![a-z])|[0-9]+')
_STOP = {'of', 'the', 'and', 'for', 'base', 'data', 'new', 'sub', 'get', 'set'}


def _cluster(stems, min_group=4):
    """{stem: token} for stems sharing their first 2-3 words, group of 4+ but < 70%."""
    words = {s: _W.findall(s) for s in stems}
    words = {s: w for s, w in words.items() if len(w) >= 3}
    n = len(words)
    if n < 6:
        return {}
    tok_files = {}
    for s, w in words.items():
        for take in (3, 2):
            if len(w) > take:
                tok = ''.join(w[:take])
                if len(tok) >= 6:
                    tok_files.setdefault(tok, set()).add(s)
    keep = {t: fs for t, fs in tok_files.items() if min_group <= len(fs) <= 0.7 * n}
    out = {}
    for s in stems:
        c = [(len(fs), len(t), t) for t, fs in keep.items() if s in fs]
        if c:
            out[s] = max(c)[2]
    return out


def regroup(per_file):
    """Split any folder with a 4+ shared-prefix group into a sub-folder, a few passes."""
    for _ in range(3):
        by_dir = {}
        for path in per_file:
            by_dir.setdefault(path.rsplit('/', 1)[0], []).append(path)
        moves = {}
        for d, paths in by_dir.items():
            seg = d.split('/')
            if d.count('/') - 1 >= 4 or len(paths) < 10:
                continue
            if len(seg) >= 4 and seg[2] in ('plants', 'zombies'):
                continue
            fname = seg[-1].lower().rstrip('s')
            stems = [p.rsplit('/', 1)[1][:-4] for p in paths]
            sub = _cluster(stems)
            fw = [_W.findall(s) for s in stems]
            common = 0
            for i in range(min((len(w) for w in fw), default=0)):
                top, cnt = collections.Counter(
                    w[i] for w in fw if len(w) > i).most_common(1)[0]
                if cnt >= 0.8 * len(fw):
                    common += 1
                else:
                    break
            for p in paths:
                tok = sub.get(p.rsplit('/', 1)[1][:-4])
                if p in HANDWRITTEN or not tok:
                    continue
                name = ''.join(_W.findall(tok)[common:]).lower()
                if len(name) < 3 or name in _STOP or name.rstrip('s') == fname:
                    continue
                moves[p] = f'{d}/{name}/{p.rsplit("/", 1)[1]}'
        if not moves:
            break
        for old, new in moves.items():
            per_file[new] = per_file.pop(old)
    return per_file


def clean_stubs():
    root = os.path.join(config.HERE, 'src')
    for dirpath, _d, files in os.walk(root):
        for fn in files:
            p = os.path.join(dirpath, fn)
            rel = os.path.relpath(p, config.HERE).replace(os.sep, '/')
            if fn.endswith('.cpp') and rel not in HANDWRITTEN and is_stub(p):
                os.remove(p)
    for dirpath, dirs, files in os.walk(root, topdown=False):
        if not dirs and not files:
            os.rmdir(dirpath)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--dry-run', action='store_true')
    args = ap.parse_args()

    game = Elf(config.TARGET_LIB)
    per_class = {}
    for n, v, s, sh, t in game.symbols():
        if t == 2 and sh and s:
            c = class_name(n)
            if c and c not in _NAMESPACES:
                per_class.setdefault(c, []).append((n, s))
    classes = set(per_class)

    place = build_families(classes)
    old = list(unit_paths())
    old_by_norm = {}
    for p in old:
        stem = os.path.splitext(os.path.basename(p))[0]
        for suf in ('',) + CO_SUFFIXES:
            old_by_norm.setdefault(_norm(stem + suf), relocate(p))
    hdr = header_index()

    unplaced, per_file = {}, {}
    for c, funcs in per_class.items():
        probe = c
        for suf in CO_SUFFIXES:
            if probe.endswith(suf):
                probe = probe[:-len(suf)]
                break
        target = (place.get(c) or place.get(probe)
                  or old_by_norm.get(_norm(c)) or old_by_norm.get(_norm(probe))
                  or hdr.get(_norm(c)) or hdr.get(_norm(probe)))
        if target:
            per_file.setdefault(target, []).extend(funcs)
        else:
            unplaced[c] = funcs
    for p in old:
        per_file.setdefault(relocate(p), [])
    regroup(per_file)

    placed = sum(len(v) for v in per_file.values())
    up = sum(len(v) for v in unplaced.values())
    print(f'{len(per_file)} units, {placed} functions placed, '
          f'{len(unplaced)} classes / {up} functions unplaced')
    if args.dry_run:
        return

    clean_stubs()
    origin = {relocate(p): p[4:] for p in old}
    made, manifest = 0, {}
    for path, funcs in sorted(per_file.items()):
        manifest[path] = {
            'original': origin.get(path, path[4:]),
            'code': sum(s for _, s in funcs),
            'funcs': [[s, sz] for s, sz in sorted(funcs, key=lambda f: -f[1])],
        }
        if path in HANDWRITTEN or os.path.exists(os.path.join(config.HERE, path)):
            continue
        write_stub(path, origin.get(path, path[4:]), funcs)
        made += 1

    json.dump({'units': manifest,
               'unplaced': {'classes': len(unplaced), 'functions': up,
                            'code': sum(sz for v in unplaced.values() for _, sz in v)}},
              open(UNITS, 'w'))
    with open(UNPLACED, 'w') as f:
        f.write('# Game classes not yet tied to a file. Add a filename to '
                'docs/original-source-tree.txt and re-run scaffold.py.\n\n')
        for c in sorted(unplaced, key=lambda c: -sum(s for _, s in unplaced[c])):
            b = sum(s for _, s in unplaced[c])
            f.write(f'{c}\t{len(unplaced[c])} fn\t{b} B\n')

    print(f'wrote {made} stubs, units.json ({len(manifest)} units)')


if __name__ == '__main__':
    main()
