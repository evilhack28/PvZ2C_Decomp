// Grep every symbol name for a substring.  -postScript Grep.java <needle> [limit]
//@category PvZ2C
import ghidra.app.script.GhidraScript;
import ghidra.program.model.symbol.*;
import ghidra.program.model.listing.*;

public class Grep extends GhidraScript {
    public void run() throws Exception {
        String[] a = getScriptArgs();
        String needle = a.length > 0 ? a[0] : "LostCityStage";
        int limit = a.length > 1 ? Integer.parseInt(a[1]) : 400;
        SymbolTable st = currentProgram.getSymbolTable();
        FunctionManager fm = currentProgram.getFunctionManager();
        println("=== " + currentProgram.getName() + " base=" + currentProgram.getImageBase()
                + " funcs=" + fm.getFunctionCount() + "  grep='" + needle + "' ===");
        int n = 0;
        for (Symbol s : st.getAllSymbols(true)) {
            String nm = s.getName(true);
            if (nm.contains(needle)) {
                boolean isFn = fm.getFunctionAt(s.getAddress()) != null;
                println(String.format("  %012x %-8s%s %s",
                    s.getAddress().getOffset(), s.getSymbolType(), isFn ? " FUNC" : "", nm));
                if (++n >= limit) { println("  ...(truncated at " + limit + ")"); break; }
            }
        }
        println("total: " + n);
    }
}
