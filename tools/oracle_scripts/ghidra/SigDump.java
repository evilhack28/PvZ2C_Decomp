// Prints address, size and prototype for each Class::method argument (exact name match).
//@category PvZ2C
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import java.util.*;

public class SigDump extends GhidraScript {
    public void run() throws Exception {
        Set<String> want = new HashSet<>(Arrays.asList(getScriptArgs()));
        FunctionManager fm = currentProgram.getFunctionManager();
        for (Function f : fm.getFunctions(true)) {
            String n = f.getName(true);
            if (want.contains(n)) {
                println(String.format("SIG %x %d %s", f.getEntryPoint().getOffset() - 0x100000, f.getBody().getNumAddresses(), f.getPrototypeString(true, false)));
            }
        }
    }
}
