// Finds a class vtable from its mangled type-name string (e.g. 12CheatUIPanel) via typeinfo and dumps each slot with function size.
//@category PvZ2C
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.mem.Memory;
import java.util.*;

public class VtByRtti extends GhidraScript {
    public void run() throws Exception {
        String[] a = getScriptArgs();
        String want = a[0];
        int slots = a.length > 1 ? Integer.parseInt(a[1]) : 40;
        FunctionManager fm = currentProgram.getFunctionManager();
        Memory mem = currentProgram.getMemory();
        for (Data d : currentProgram.getListing().getDefinedData(true)) {
            if (!(d.getValue() instanceof String) || !want.equals(d.getValue())) continue;
            for (Reference r1 : getReferencesTo(d.getAddress())) {
                Address ti = r1.getFromAddress().subtract(8);
                println("TYPEINFO " + ti + " for " + want);
                byte[] pat = new byte[8];
                long tv = ti.getOffset();
                for (int k = 0; k < 8; k++) pat[k] = (byte) (tv >> (8 * k));
                Address hit = mem.findBytes(mem.getMinAddress(), pat, null, true, monitor);
                while (hit != null) {
                    Address vt = hit.add(8);
                    println("VTABLE " + vt + " (typeinfo slot at " + hit + ")");
                    for (int i = 0; i < slots; i++) {
                        Address p = vt.add(8L * i);
                        long v = mem.getLong(p);
                        Function f = fm.getFunctionAt(toAddr(v));
                        println(String.format("  +0x%03x %s -> %x (%s bytes)", 8 * i, p, v, f == null ? "?" : "" + f.getBody().getNumAddresses()));
                    }
                    Address nxt = hit.add(8);
                    hit = mem.findBytes(nxt, pat, null, true, monitor);
                }
            }
        }
    }
}
