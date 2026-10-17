// For each substring argument, prints matching defined strings and the functions that reference them.
//@category PvZ2C
import ghidra.app.script.GhidraScript;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import ghidra.program.model.symbol.*;
import java.util.*;

public class StrXref extends GhidraScript {
    public void run() throws Exception {
        String[] needles = getScriptArgs();
        FunctionManager fm = currentProgram.getFunctionManager();
        Listing listing = currentProgram.getListing();
        for (Data d : listing.getDefinedData(true)) {
            Object v = d.getValue();
            if (!(v instanceof String)) continue;
            String s = (String) v;
            for (String n : needles) {
                if (!s.contains(n)) continue;
                StringBuilder fns = new StringBuilder();
                Set<String> seen = new LinkedHashSet<>();
                for (Reference r : getReferencesTo(d.getAddress())) {
                    Function f = fm.getFunctionContaining(r.getFromAddress());
                    if (f != null) seen.add(String.format("%x(%d)", f.getEntryPoint().getOffset(), f.getBody().getNumAddresses()));
                }
                fns.append(String.join(",", seen));
                println("STR [" + n + "] @" + d.getAddress() + " \"" + (s.length() > 60 ? s.substring(0, 60) : s).replace("\n", " ") + "\" -> " + (fns.length() == 0 ? "(no xref)" : fns));
                break;
            }
        }
    }
}
