// Decompile a list of functions by name (comma-separated) or hex address.
//   -postScript Decomp.java "A::b,C::d,03d003cc"
//@category PvZ2C
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;

public class Decomp extends GhidraScript {
    public void run() throws Exception {
        String[] which = String.join(",", getScriptArgs()).split(",");
        FunctionManager fm = currentProgram.getFunctionManager();
        for (String w : which) {
            w = w.trim();
            Function f = null;
            try {
                Address a = currentProgram.getAddressFactory().getDefaultAddressSpace()
                            .getAddress(Long.parseLong(w, 16));
                f = fm.getFunctionContaining(a);
            } catch (Exception e) {}
            if (f == null) for (Function g : fm.getFunctions(true))
                if (g.getName(true).equals(w)) { f = g; break; }
            if (f == null) { println("\n// >>> not found: " + w); continue; }
            println("\n// ===== " + f.getName(true) + "  @ " + f.getEntryPoint()
                    + "  (" + f.getBody().getNumAddresses() + " b) =====");
            DecompInterface di = new DecompInterface();
            di.openProgram(currentProgram);
            try {
                DecompileResults r = di.decompileFunction(f, 100, monitor);
                if (r != null && r.getDecompiledFunction() != null)
                    println(r.getDecompiledFunction().getC());
                else
                    println("// <decomp failed: " + (r != null ? r.getErrorMessage() : "null") + ">");
            } finally {
                di.dispose();
            }
        }
    }
}
