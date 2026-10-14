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
from lib.pvzelf import Elf
from progress import owned_prefixes, pretty, is_stub, _NAMESPACES

TREE = os.path.join(config.HERE, 'docs', 'original-source-tree.txt')
UNITS = os.path.join(config.HERE, 'units.json')
UNPLACED = os.path.join(config.HERE, 'docs', 'unplaced-symbols.txt')

from lib.layout import studio  # noqa: E402

HANDWRITTEN = {
    'src/PvZ2/plants/Iceburg/Plant_Iceburg.cpp',
    'src/PvZ2/plants/Iceburg/PlantAnimRig_Iceburg.cpp',
    'src/PvZ2/plants/Jalapeno/Plant_Jalapeno.cpp',
    'src/PvZ2/net/gameNetWork/NetworkData.cpp',
    'src/PvZ2/net/gameNetWork/PVPDatas.cpp',
}
HANDWRITTEN = {studio(p) for p in HANDWRITTEN}

# header/source subdir -> where it lands under src/
_SUBDIR_MOVE = {'gameNetWork': 'net/gameNetWork'}

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
    """Per-entity folder under src/PvZ2/ for plants and zombies only; everything else mirrors its header."""
    c = _category(s)
    if c in (None, 'plants', 'zombies', 'zombies/zomboss'):
        return None
    return c if c.split('/')[0] in ('plants', 'zombies') else None


def _category(s):
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
        return 'zombies/' + s[6:].split('Props')[0].split('PropertySheet')[0].lstrip('_')
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
    return canon(_relocate(repo_path))


def _relocate(repo_path):
    parts = repo_path.split('/')
    stem = os.path.splitext(parts[-1])[0]
    if parts[:2] == ['src', 'PvZ2'] and len(parts) == 3:
        cat = category(stem)
        if cat:
            return f'src/PvZ2/{cat}/{parts[-1]}'
        t = _hdr().get(_norm(stem))
        if t and t.startswith('src/PvZ2/'):
            return t
    if len(parts) >= 4 and parts[2] in _SUBDIR_MOVE:
        parts[2] = _SUBDIR_MOVE[parts[2]]
        return '/'.join(parts)
    return repo_path


_HDR = {}
_ENT_PRE = ('PlantAnimRig_', 'Plant_', 'ZombieAnimRig_', 'Zombie_', 'Zombie')


def canon(path):
    return studio(_canon(path))


def _canon(path):
    """Respell a src path's file stem (and entity folder) to the header's exact casing."""
    parts = path.split('/')
    stem = parts[-1][:-4]
    t = _hdr().get(_norm(stem))
    if not t or t.startswith('src/SexyAppFramework'):
        return path
    hs = t.rsplit('/', 1)[1][:-4]
    if hs == stem:
        return path
    parts[-1] = hs + '.cpp'
    if len(parts) >= 5 and parts[2] in ('plants', 'zombies'):
        for pre in _ENT_PRE:
            if stem.startswith(pre) and stem[len(pre):].lstrip('_') == parts[3]:
                parts[3] = hs[len(pre):].lstrip('_')
                break
    return '/'.join(parts)


def _hdr():
    if not _HDR:
        _HDR.update(header_index())
    return _HDR


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
            if _norm(stem) not in idx or target.count('/') < idx[_norm(stem)].count('/'):
                idx[_norm(stem)] = target
    return idx


def entities(classes, prefix):
    return sorted({c[len(prefix):] for c in classes
                   if c.startswith(prefix) and len(c) > len(prefix)
                   and c[len(prefix)].isupper()})


def _ent_dir(x, prefixes):
    """Entity folder spelled as its main header, else as the class names."""
    for pre in prefixes:
        t = _hdr().get(_norm(pre + x))
        if t:
            hs = t.rsplit('/', 1)[1][:-4]
            if hs.startswith(pre) and _norm(hs[len(pre):]) == _norm(x):
                return hs[len(pre):]
    return x


def build_families(classes):
    """Plant<X>/Zombie<X> -> a folder per entity; GridItem/Effect/Powerup grouped."""
    place = {}

    plant_x = set(entities(classes, 'PlantAnimRig_'))
    plant_x |= {c[5:] for c in classes
                if c.startswith('Plant') and len(c) > 5 and c[5].isupper()
                and 'PlantType' + c[5:] in classes}
    plant_x = {x for x in plant_x if x and x[0].isupper()}
    for x in sorted(plant_x, key=len, reverse=True):
        d = f'src/PvZ2/plants/{_ent_dir(x, ("Plant_", "Plant"))}'
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
        d = f'src/PvZ2/zombies/{_ent_dir(x, ("Zombie_", "Zombie")).lstrip("_")}'
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
            place.setdefault(c, f'src/PvZ2/{base}.cpp')
    for x in entities(classes, 'Effect_'):
        place[f'Effect_{x}'] = f'src/PvZ2/Effect_{x}.cpp'
    for x in entities(classes, 'EffectAnimRig_'):
        place[f'EffectAnimRig_{x}'] = f'src/PvZ2/EffectAnimRig_{x}.cpp'
    for c in list(classes):
        if c.startswith('Powerup') and c not in ('Powerup', 'PowerupType', 'PowerupManager'):
            place.setdefault(c, f'src/PvZ2/{c}.cpp')

    # Cheats.h / CheatUI.h / PVZCheats.h: class names don't normalize-match
    # any of the three filenames, so the generic rules below never place them.
    for c in ('Cheat', 'CheatToggle', 'CheatToggleAction', 'CheatCommand',
              'CheatManager'):
        place.setdefault(c, 'src/PvZ2/Cheats.cpp')
    for c in ('CheatUILine', 'CheatUILineSeparator', 'CheatUILineToggle',
              'CheatUILineCommand', 'CheatAdjusterWidget', 'CheatUILineAdjuster',
              'CheatUILineFolder', 'CheatUIPanel'):
        place.setdefault(c, 'src/PvZ2/CheatUI.cpp')
    for c in ('CheatGameSpawnZombieCommand', 'CheatGameSpawnCreatureCommand',
              'CheatGameSpawnCollectable', 'CheatGameStartLevelCommand',
              'CheatDangerRoomStartLevelCommand', 'CheatGameSpawnPlantCommand',
              'CheatGameStartNarrative', 'CheatGameFeatureToggle',
              'CheatGameProfileLockToggle', 'CheatGameUnlockToEvent',
              'CheatAutoTestStartLevelCommand', 'CheatPlantsVsZombiesStartWorldCommand',
              'CheatAutoTestStartUnlockLevelCommand', 'CheatVariable'):
        place.setdefault(c, 'src/PvZ2/PVZCheats.cpp')
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


def class_ns(sym):
    """(class, outer namespace or None) for a plain class method, namespaced classes included."""
    o = owned_prefixes(sym)
    if not o:
        return None, None
    body, i, parts = o.zn[3:], 0, []
    while i < len(body) and body[i].isdigit():
        j = i
        while body[j].isdigit():
            j += 1
        n = int(body[i:j])
        parts.append(body[j:j + n])
        i = j + n
    return (parts[-1], parts[0] if len(parts) > 1 else None) if parts else (None, None)


_STD_SUB = {'t': 'std', 'a': 'allocator', 'b': 'basic_string', 's': 'string', 'i': 'istream', 'o': 'ostream', 'd': 'iostream'}
_LIB_NS = {'std': 'std', 'eastl': 'eastl', '__gnu_cxx': 'gnu_cxx', '__cxxabiv1': 'cxxabi', 'EA': 'EA', 'EATech': 'EA'}


def lead_names(sym):
    """(outer namespace or None, name or None, free) from the leading names of any mangled symbol."""
    if not sym.startswith('_Z'):
        return 'c', sym, True
    nested = sym.startswith('_ZN')
    i = 4 if sym.startswith('_ZNK') else 3 if nested else 2
    ns = None
    if sym[i:i + 1] == 'S' and sym[i + 1:i + 2] in _STD_SUB:
        ns, i = 'std', i + 2
        if sym[i - 1] != 't':
            return ns, _STD_SUB[sym[i - 1]], False
    comps = []
    while i < len(sym) and sym[i].isdigit():
        j = i
        while sym[j].isdigit():
            j += 1
        n = int(sym[i:j])
        comps.append(sym[j:j + n])
        i = j + n
        if not nested:
            break
    if not comps:
        return ns or 'misc', None, False
    if ns is None and comps[0] in _LIB_NS or comps[0] in ('Sexy', 'AK'):
        ns = comps[0]
        comps = comps[1:]
    if not comps:
        return ns, None, True
    free = len(comps) == 1 and sym[i:i + 1] != 'I' and not nested or (nested and len(comps) == 1 and sym[i:i + 1] == 'E')
    return ns, comps[0], free


def nonclass_home(sym, hdr):
    """File for a symbol that is no plain class method: templates by their template name, free functions grouped per namespace."""
    ns, name, free = lead_names(sym)
    ns = _LIB_NS.get(ns, ns)
    if free or not name:
        base = {'Sexy': 'src/SexyAppFramework/SexyFunctions', 'EA': 'src/SexyAppFramework/EATech/EAFunctions',
                None: 'src/PvZ2/Data/GlobalFunctions', 'c': 'src/ThirdParty/c/RuntimeSymbols',
                'misc': 'src/ThirdParty/misc/Unclassified'}.get(ns)
        return (base or f'src/ThirdParty/{ns}/{ns}Functions') + '.cpp'
    if ns == 'Sexy':
        return hdr.get(_norm(name)) or f'src/SexyAppFramework/Templates/{name}.cpp'
    if ns == 'EA':
        return f'src/SexyAppFramework/EATech/{name}.cpp'
    if ns in _LIBS:
        return f'src/ThirdParty/{ns}/{name}.cpp'
    return hdr.get(_norm(name)) or fallback_path(name, None)


_LIBS = {'std', 'eastl', 'gnu_cxx', 'cxxabi', 'c', 'misc', 'EA', 'AK', 'FEAST', 'Lua', 'open_vcdiff',
         'EATextSquish', 'fastdelegate'}
_AREAS = [
    ('Gameplay/Zombies', ('Zomboss', 'Zombie')),
    ('Gameplay/Subsystems', ('SubSystem', 'Launcher')),
    ('Gameplay/GridItems', ('GridItem', 'GridSquare')),
    ('Gameplay/Waves', ('Wave', 'Spawn')),
    ('Gameplay/Combat', ('Projectile', 'Damage', 'Bomb', 'Missile')),
    ('Gameplay/Effects', ('Effect', 'AnimRig', 'Anim')),
    ('Gameplay/Level', ('Level', 'Stage', 'Challenge', 'Mode', 'Board', 'Tile')),
    ('Network', ('Network', 'S2C', 'C2S', 'Msg', 'Message', 'Http', 'Web', 'Server', 'PVP', 'Router')),
    ('Profile', ('Profile', 'PlayerInfo', 'Save', 'Avatar')),
    ('Managers', ('Mgr', 'Manager', 'Module', 'Handler', 'Listener')),
    ('UI', ('UI', 'Dialog', 'Dlg', 'Panel', 'Screen', 'Widget', 'Button', 'Tab', 'Display', 'Window', 'View')),
    ('Data', ('Props', 'Propert', 'Config', 'Table', 'Info', 'Mapper', 'Data', 'Param', 'Def')),
    ('Activities', ('Activity', 'Reward', 'Lottery', 'Gift', 'Recharge', 'Daily', 'Penny', 'Shop', 'Store',
                    'Pack', 'Sign', 'Event', 'Task', 'Rift', 'Artifact', 'Uncharted', 'Dave', 'World')),
]


def area(name):
    """Folder under src/PvZ2 for a game class, by the words in its name; Gameplay/Misc when none fits."""
    for folder, keys in _AREAS:
        if any(k in name for k in keys):
            return folder
    return 'Gameplay/Misc'


_HEAD = re.compile(r'S2C|C2S|PVZ2|PVZ|PVP|UI(?=[A-Z])|[A-Z][a-z0-9]+|[A-Z]+(?![a-z])|_*[a-z][a-z0-9]*')


def _tokens(stem):
    out = []
    for part in stem.split('_'):
        while part:
            m = _HEAD.match(part)
            w = m.group(0) if m else part
            out.append(w)
            part = part[len(w):]
    return out


def split_dir(d, keys, real, limit=30, min_group=4, taken=None):
    """{key: new key} - a folder over `limit` files is split by the next word of the names, recursively."""
    if len(keys) <= limit:
        return {}
    skip = {x.lower().rstrip('s') for x in d.split('/')[-4:]}
    groups, lead = {}, {}
    for k in keys:
        toks = _tokens(k.rsplit('/', 1)[1][:-4])
        i, joined, last = 0, '', 0
        while i < len(toks) - 1:
            joined += toks[i].lower()
            i += 1
            if joined.rstrip('s') in skip:
                last = i
        i = last
        lead[k] = toks[i][0].upper()
        if i < len(toks) - 1:
            groups.setdefault(toks[i], []).append(k)
    moves = {}
    for w, ks in sorted(groups.items()):
        if len(ks) < min_group or any(k in real for k in ks) or w.lower().rstrip('s') in skip:
            continue
        sub = f'{d}/{w}'
        if taken and sub.lower() in taken:
            continue
        inner = {k: f'{sub}/{k.rsplit("/", 1)[1]}' for k in ks}
        deeper = split_dir(sub, list(inner.values()), real, limit, min_group, taken)
        for k, nk in inner.items():
            moves[k] = deeper.get(nk, nk)
    rest = [k for k in keys if k not in moves]
    if len(rest) > limit:
        tails = {}
        for k in rest:
            toks = _tokens(k.rsplit('/', 1)[1][:-4])
            if len(toks) > 1:
                tails.setdefault(toks[-1], []).append(k)
        for w, ks in sorted(tails.items()):
            sub = f'{d}/{w}'
            if len(ks) < 8 or any(k in real for k in ks) or w.lower().rstrip('s') in skip or (taken and sub.lower() in taken):
                continue
            inner = {k: f'{sub}/{k.rsplit("/", 1)[1]}' for k in ks}
            deeper = split_dir(sub, list(inner.values()), real, limit, min_group, taken)
            for k, nk in inner.items():
                moves[k] = deeper.get(nk, nk)
    rest = [k for k in keys if k not in moves and k not in real]
    letters = collections.Counter(lead[k] for k in rest)
    if len(rest) > 2 * limit and len(letters) >= 6 and max(letters.values()) <= len(rest) // 2:
        for k in rest:
            letter = lead[k]
            if f'{d}/{letter}'.lower() not in (taken or ()):
                moves[k] = f'{d}/{letter}/{k.rsplit("/", 1)[1]}'
    return moves


def fallback_path(c, ns):
    """Home for a class nothing else placed: library classes by namespace, framework and game classes by area."""
    if ns == 'Sexy':
        return f'src/SexyAppFramework/{c}.cpp'
    if ns == 'EA':
        return f'src/SexyAppFramework/EATech/{c}.cpp'
    if ns in _LIBS:
        return f'src/ThirdParty/{ns}/{c}.cpp'
    cat = category(c)
    return f'src/PvZ2/{cat}/{c}.cpp' if cat else f'src/PvZ2/{area(c)}/{c}.cpp'


STUB = '''// {orig}
//
// {n} function(s){bytes} to reconstruct. Generated by tools/scaffold.py.
// Replace this banner with real code; drop a TODO line as its function matches.
//
// classes: {classes}
//
{todo}'''

STUB_TODO_CAP = 80

CLASS_FILES = {
    'Magento': 'src/PvZ2/MagentoService.cpp',
    'MagentoProductProps': 'src/PvZ2/MagentoService.cpp',
    'MagentoCategoryProps': 'src/PvZ2/MagentoService.cpp',
    'PlantGiftMagentoProps': 'src/PvZ2/MagentoService.cpp',
    'PVZCachedNetworkTableManager': 'src/PvZ2/PVZCachedNetworkTable.cpp',
    'PVZPackageNetworkManager': 'src/PvZ2/PVZPackageNetwork.cpp',
    'PVZLevelNetworkManager': 'src/PvZ2/PVZPackageNetwork.cpp',
    'INetworkMsgProcess': 'src/PvZ2/net/gameNetWork/NetworkMsgProcess.cpp',
    'Message': 'src/PvZ2/Message.cpp',
    'androidNetworkMsgProcess': 'src/PvZ2/net/gameNetWork/androidNetworkMsgProcess.cpp',
    'NameMapperBase': 'src/PvZ2/Data/Mappers/NameMapperBase.cpp',
    'PlantNameMapper': 'src/PvZ2/Data/Mappers/PlantNameMapper.cpp',
    'PlantNameMapperServerID': 'src/PvZ2/Data/Mappers/PlantNameMapperServerID.cpp',
    'PlantChipNameMapperServerID': 'src/PvZ2/Data/Mappers/PlantChipNameMapperServerID.cpp',
    'AvatarNameMapperServerID': 'src/PvZ2/Data/Mappers/AvatarNameMapperServerID.cpp',
    'AvatarChipNameMapperServerID': 'src/PvZ2/Data/Mappers/AvatarChipNameMapperServerID.cpp',
    'ConstraintNameMapper': 'src/PvZ2/Data/Mappers/ConstraintNameMapper.cpp',
    'OtherServerNameMapper': 'src/PvZ2/Data/Mappers/OtherServerNameMapper.cpp',
    'NarrationEventNameMapper': 'src/PvZ2/Data/Mappers/NarrationEventNameMapper.cpp',
}


def write_stub(path, orig, funcs):
    full = os.path.join(config.HERE, path)
    os.makedirs(os.path.dirname(full), exist_ok=True)
    funcs = sorted(funcs, key=lambda f: -f[1])
    classes = sorted({class_ns(s)[0] or lead_names(s)[1] or 'free functions' for s, _ in funcs}) or ['(unknown)']
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
    per_class, class_outer, nonclass, extra = {}, {}, [0, 0], []
    for n, v, s, sh, t in game.symbols():
        if t == 2 and sh and s:
            c, ns = class_ns(n)
            if c and c not in _NAMESPACES:
                per_class.setdefault(c, []).append((n, s))
                class_outer.setdefault(c, ns)
            else:
                nonclass[0] += 1
                nonclass[1] += s
                extra.append((n, s))
    classes = set(per_class)

    place = build_families(classes)
    old = list(unit_paths())
    old_by_norm = {}
    for p in old:
        stem = os.path.splitext(os.path.basename(p))[0]
        for suf in ('',) + CO_SUFFIXES:
            old_by_norm.setdefault(_norm(stem + suf), relocate(p))
    hdr = header_index()

    unplaced, per_file, fallback = {}, {}, []
    for c, funcs in per_class.items():
        probe = c
        for suf in CO_SUFFIXES:
            if probe.endswith(suf):
                probe = probe[:-len(suf)]
                break
        target = (CLASS_FILES.get(c) or place.get(c) or place.get(probe)
                  or old_by_norm.get(_norm(c)) or old_by_norm.get(_norm(probe))
                  or hdr.get(_norm(c)) or hdr.get(_norm(probe)))
        pref = hdr.get(_norm(c)) or hdr.get(_norm(probe))
        if (target and pref and pref.startswith('src/PvZ2/')
                and pref.count('/') > 2
                and not pref.startswith(('src/PvZ2/plants/', 'src/PvZ2/zombies/')) and not (target or '').startswith('src/PvZ2/net/')):
            target = pref
        if not target:
            target = fallback_path(c, class_outer.get(c))
            fallback.append(target)
        per_file.setdefault(canon(target), []).extend(funcs)
    for n, sz in extra:
        per_file.setdefault(canon(nonclass_home(n, hdr)), []).append((n, sz))
    by_dir, real = {}, set()
    for key in per_file:
        full = os.path.join(config.HERE, key)
        if key in HANDWRITTEN or (os.path.exists(full) and not is_stub(full)):
            real.add(key)
        if key.startswith(('src/PvZ2/', 'src/SexyAppFramework/', 'src/ThirdParty/')):
            by_dir.setdefault(key.rsplit('/', 1)[0], []).append(key)
    sibling_dirs = {}
    for dd in {k.rsplit('/', 1)[0] for k in per_file}:
        sibling_dirs.setdefault(dd.rsplit('/', 1)[0], set()).add(dd.rsplit('/', 1)[1])
    for d, keys in by_dir.items():
        if '/plants' in d or '/zombies' in d:
            continue
        for key, new in split_dir(d, keys, real).items():
            per_file[new] = per_file.pop(key)
    for p in old:
        per_file.setdefault(relocate(p), [])

    placed = sum(len(v) for v in per_file.values())
    up = sum(len(v) for v in unplaced.values())
    print(f'{len(per_file)} units, {placed} functions placed, '
          f'{len(unplaced)} classes / {up} functions unplaced; '
          f'{nonclass[0]} non-class symbols ({nonclass[1]} B) placed by template or namespace')
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
                            'code': sum(sz for v in unplaced.values() for _, sz in v)},
               'nonclass': {'functions': nonclass[0], 'code': nonclass[1]}},
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
