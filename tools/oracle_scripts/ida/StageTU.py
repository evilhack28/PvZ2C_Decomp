"""A stage translation unit: ordered functions, the statics its render code uses, decompiled bodies: StageTU <ClassStem>."""

from ida_api import *

WANT = ('render', 'registerForEvents', 'addForeground', 'initializeModule', 'onUpdate', 'onLoadComplete',
        'onLevelLoaded', 'generatePlanks', 'InitPlanks', 'onZombieTypeCountChange', 'stopZombieGroans',
        'GatherPlanting', 'gatherPlanting', 'DropZombie', 'SpawnWater', 'CanZombie', 'CanGraveStone')


def run(args):
    stem = args[0] if args else 'LostCity'
    anchor = next((f for f in functions()
                   if fname(f) in ('%sStage::%sStage' % (stem, stem), '%sStage::StaticClassInit' % stem)), None)
    if anchor is None:
        println('no anchor for ' + stem)
        return
    lo, hi = anchor - 0x400, anchor + 0x4000
    println('=== %sStage TU  (band %x..%x) ===' % (stem, lo, hi))
    println('\n--- functions in band ---')
    for f in functions(lo, hi + 1):
        n = fname(f)
        if not n.startswith(('Sexy::', 'std::')):
            println('  %08x  %4db  %s' % (f, fsize(f), n))
    println('\n--- image statics referenced by render* ---')
    objs = []
    for f in functions():
        if stem + 'Stage::render' not in fname(f):
            continue
        for ea, _, _ in insns(f):
            for to, _ in refs_from(ea):
                if fn_containing(to) is None and to not in objs:
                    objs.append(to)
    for o in objs:
        line = '  %s  %s' % (A(o), name(o) or '(unnamed)')
        for frm, _ in refs_to(o):
            w = fn_containing(frm)
            if w is not None and any(k in fname(w) for k in ('static_init', 'GLOBAL__sub_I', stem)):
                line += '   <- %s @ %s' % (fname(w), A(frm))
        println(line)
    for f in functions():
        n = fname(f)
        if stem + 'Stage::' not in n or not any(w in n for w in WANT):
            continue
        println('\n========== %s ==========' % n)
        c = decompile(f)
        if c is not None:
            println(c)
