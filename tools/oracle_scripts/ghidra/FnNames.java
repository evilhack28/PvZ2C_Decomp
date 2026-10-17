// Prints the function name containing each hex address argument.
//@category PvZ2C
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;

public class FnNames extends GhidraScript {
    public void run() throws Exception {
        for (String a : getScriptArgs()) {
            Function f = currentProgram.getFunctionManager().getFunctionContaining(toAddr(Long.parseLong(a, 16)));
            println("FN " + a + " " + (f == null ? "?" : f.getName(true)));
        }
    }
}
