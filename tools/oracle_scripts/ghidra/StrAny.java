// Prints defined strings matching the regex argument, with the functions that reference them.
//@category PvZ2C
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.util.*;

public class StrAny extends GhidraScript {
    public void run() throws Exception {
        String re = getScriptArgs()[0].replace("#", "|");
        FunctionManager fm = currentProgram.getFunctionManager();
        for (Data d : currentProgram.getListing().getDefinedData(true)) {
            Object v = d.getValue();
            if (!(v instanceof String) || !((String) v).matches(re)) continue;
            Set<String> seen = new LinkedHashSet<>();
            for (Reference r : getReferencesTo(d.getAddress())) {
                Function f = fm.getFunctionContaining(r.getFromAddress());
                seen.add(f == null ? r.getFromAddress().toString() : String.format("%x", f.getEntryPoint().getOffset()));
            }
            println("RX " + d.getAddress() + " " + v + " -> " + seen);
        }
    }
}
