// Lists the functions that call each address given as a script argument.
//@category PvZ2C
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;
import java.util.*;

public class Callers extends GhidraScript {
    public void run() throws Exception {
        for (String h : getScriptArgs()) {
            Address t = toAddr(h);
            Map<Address, List<Address>> m = new TreeMap<>();
            for (Reference r : getReferencesTo(t)) {
                Function f = getFunctionContaining(r.getFromAddress());
                Address k = f == null ? r.getFromAddress() : f.getEntryPoint();
                m.computeIfAbsent(k, x -> new ArrayList<>()).add(r.getFromAddress());
            }
            println("//===== callers of " + h + " (" + m.size() + " functions)");
            for (Map.Entry<Address, List<Address>> e : m.entrySet())
                println("  " + e.getKey() + "  sites=" + e.getValue());
        }
    }
}
