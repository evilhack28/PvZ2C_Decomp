// Lists every reference to the function at each hex address argument, with the containing function.
//@category PvZ2C
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;

public class XrefsTo extends GhidraScript {
    public void run() throws Exception {
        FunctionManager fm = currentProgram.getFunctionManager();
        for (String a : getScriptArgs()) {
            Address ad = toAddr(Long.parseLong(a, 16));
            Function f = fm.getFunctionAt(ad);
            println("TARGET " + a + " " + (f == null ? "(no function)" : f.getName(true)));
            for (Reference r : getReferencesTo(ad)) {
                Function c = fm.getFunctionContaining(r.getFromAddress());
                println("  " + r.getReferenceType() + " from " + r.getFromAddress() + " in " + (c == null ? "(data)" : c.getName(true)));
            }
        }
    }
}
