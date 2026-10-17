// Find every function that references given addresses, and decompile them.
//   -postScript WhoWrites.java 06ad56c8,06ad5700,06ad5780
//@category PvZ2C
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;

public class WhoWrites extends GhidraScript {
    public void run() throws Exception {
        String[] a = getScriptArgs();
        String[] addrs = a[0].split(",");
        FunctionManager fm = currentProgram.getFunctionManager();
        ReferenceManager rm = currentProgram.getReferenceManager();
        DecompInterface di = new DecompInterface();
        di.openProgram(currentProgram);

        java.util.LinkedHashSet<Function> funcs = new java.util.LinkedHashSet<>();
        for (String s : addrs) {
            Address t = currentProgram.getAddressFactory().getDefaultAddressSpace()
                        .getAddress(Long.parseLong(s.trim(), 16));
            println("refs to " + t + ":");
            for (Reference r : rm.getReferencesTo(t)) {
                Function f = fm.getFunctionContaining(r.getFromAddress());
                println("  " + r.getFromAddress() + "  " + r.getReferenceType()
                        + "  in " + (f != null ? f.getName(true) : "(none)"));
                if (f != null) funcs.add(f);
            }
        }
        for (Function f : funcs) {
            println("\n========== " + f.getName(true) + "  @ " + f.getEntryPoint() + " ==========");
            DecompileResults r = di.decompileFunction(f, 180, monitor);
            if (r != null && r.getDecompiledFunction() != null) println(r.getDecompiledFunction().getC());
        }
    }
}
