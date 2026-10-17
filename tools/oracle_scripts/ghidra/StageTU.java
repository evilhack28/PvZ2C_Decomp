// Extract a stage translation unit: ordered functions, the .bss statics it
// constructs (with IMAGE_ strings), and decompiled render/init bodies.
//   -postScript StageTU.java <ClassStem>
//@category PvZ2C
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.scalar.Scalar;

public class StageTU extends GhidraScript {
    public void run() throws Exception {
        String stem = getScriptArgs().length > 0 ? getScriptArgs()[0] : "LostCity";
        SymbolTable st = currentProgram.getSymbolTable();
        Listing lst = currentProgram.getListing();
        FunctionManager fm = currentProgram.getFunctionManager();
        ReferenceManager rm = currentProgram.getReferenceManager();
        DecompInterface di = new DecompInterface();
        di.openProgram(currentProgram);

        // anchor: the stage's ctor, to find the TU's function-address band
        Function anchor = null;
        for (Function f : fm.getFunctions(true)) {
            if (f.getName(true).equals(stem + "Stage::" + stem + "Stage")
                || f.getName(true).equals(stem + "Stage::StaticClassInit")) { anchor = f; break; }
        }
        if (anchor == null) { println("no anchor for " + stem); return; }
        long lo = anchor.getEntryPoint().getOffset() - 0x400;
        long hi = anchor.getEntryPoint().getOffset() + 0x4000;

        println("=== " + stem + "Stage TU  (band " + Long.toHexString(lo) + ".." + Long.toHexString(hi) + ") ===");
        println("\n--- functions in band ---");
        for (Function f : fm.getFunctions(true)) {
            long a = f.getEntryPoint().getOffset();
            if (a >= lo && a <= hi) {
                String n = f.getName(true);
                if (n.startsWith("Sexy::") || n.startsWith("std::")) continue;
                println(String.format("  %08x  %4db  %s", a, f.getBody().getNumAddresses(), n));
            }
        }

        // the CachedResourcePtr<Image> statics: find data the render fns point at,
        // then find who writes a string near it (the static init ctor call)
        println("\n--- image statics referenced by render* ---");
        java.util.LinkedHashSet<Address> objs = new java.util.LinkedHashSet<>();
        for (Function f : fm.getFunctions(true)) {
            if (!f.getName(true).contains(stem + "Stage::render")) continue;
            for (Address a : f.getBody().getAddresses(true)) {
                for (Reference r : rm.getReferencesFrom(a)) {
                    Address to = r.getToAddress();
                    if (to != null && to.isMemoryAddress() && fm.getFunctionAt(to) == null
                        && !lst.isInFunction(to)) objs.add(to);
                }
            }
        }
        for (Address o : objs) {
            Symbol s = st.getPrimarySymbol(o);
            print("  " + o + "  " + (s != null ? s.getName(true) : "(unnamed)"));
            // who references it?
            for (Reference r : rm.getReferencesTo(o)) {
                Function w = fm.getFunctionContaining(r.getFromAddress());
                if (w != null && (w.getName(true).contains("static_init")
                     || w.getName(true).contains("GLOBAL__sub_I")
                     || w.getName(true).contains(stem))) {
                    print("   <- " + w.getName(true) + " @ " + r.getFromAddress());
                }
            }
            println("");
        }

        // decompile render + registerForEvents + addForeground + initializeModule + onUpdate + onLoadComplete
        String[] want = {"render", "registerForEvents", "addForeground", "initializeModule",
                         "onUpdate", "onLoadComplete", "onLevelLoaded", "generatePlanks", "InitPlanks",
                         "onZombieTypeCountChange", "stopZombieGroans", "GatherPlanting", "gatherPlanting",
                         "DropZombie", "SpawnWater", "CanZombie", "CanGraveStone"};
        for (Function f : fm.getFunctions(true)) {
            String n = f.getName(true);
            if (!n.contains(stem + "Stage::")) continue;
            boolean hit = false; for (String w : want) if (n.contains(w)) hit = true;
            if (!hit) continue;
            println("\n========== " + n + " ==========");
            DecompileResults r = di.decompileFunction(f, 150, monitor);
            if (r != null && r.getDecompiledFunction() != null) println(r.getDecompiledFunction().getC());
        }
    }
}
