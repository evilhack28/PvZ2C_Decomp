// Prints the data/symbol at each hex address and code that references addresses within +-0x20 of it.
//@category PvZ2C
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;

public class WhatIs extends GhidraScript {
    public void run() throws Exception {
        FunctionManager fm = currentProgram.getFunctionManager();
        for (String a : getScriptArgs()) {
            Address ad = toAddr(Long.parseLong(a, 16));
            for (long d = -0x40; d <= 0x40; d += 8) {
                Address x = ad.add(d);
                Symbol s = currentProgram.getSymbolTable().getPrimarySymbol(x);
                Data dt = currentProgram.getListing().getDataAt(x);
                long v = 0; try { v = currentProgram.getMemory().getLong(x); } catch (Exception e) {}
                StringBuilder sb = new StringBuilder("  " + x + " val=" + Long.toHexString(v) + (s == null ? "" : " sym=" + s.getName(true)));
                for (Reference r : getReferencesTo(x)) { Function c = fm.getFunctionContaining(r.getFromAddress()); sb.append(" <-" + r.getReferenceType() + "@" + r.getFromAddress() + (c == null ? "" : ":" + c.getName(true))); }
                println(sb.toString());
            }
        }
    }
}
