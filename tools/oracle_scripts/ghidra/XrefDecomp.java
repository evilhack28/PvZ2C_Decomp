// Functions referencing each address, decompiled: -postScript XrefDecomp.java <hex,...> [maxLines]
//@category PvZ2C
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;
import java.util.*;

public class XrefDecomp extends GhidraScript {
    public void run() throws Exception {
        String[] a = getScriptArgs();
        int max = a.length > 1 ? Integer.parseInt(a[1]) : 60;
        Set<Function> seen = new LinkedHashSet<>();
        for (String h : a[0].split(",")) {
            Address ad = toAddr(h);
            for (Reference r : getReferencesTo(ad)) {
                Function f = getFunctionContaining(r.getFromAddress());
                println("REF " + h + " from " + r.getFromAddress() + " in " + (f == null ? "none" : f.getName() + "@" + f.getEntryPoint()));
                if (f != null) seen.add(f);
            }
        }
        DecompInterface di = new DecompInterface();
        di.openProgram(currentProgram);
        for (Function f : seen) {
            DecompileResults r = di.decompileFunction(f, 60, monitor);
            println("//===== " + f.getName() + "@" + f.getEntryPoint());
            if (r.getDecompiledFunction() == null) continue;
            String[] ls = r.getDecompiledFunction().getC().split("\n");
            for (int i = 0; i < ls.length && i < max; i++) println(ls[i]);
        }
    }
}
