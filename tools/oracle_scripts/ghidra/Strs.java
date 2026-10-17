// Defined data (strings) in [start,end]: -postScript Strs.java <hexStart> <hexEnd>
//@category PvZ2C
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Data;

public class Strs extends GhidraScript {
    public void run() throws Exception {
        String[] a = getScriptArgs();
        Data d = getDataAt(toAddr(a[0]));
        if (d == null) d = getDataAfter(toAddr(a[0]));
        long hi = Long.parseLong(a[1], 16);
        for (; d != null && d.getAddress().getOffset() <= hi; d = getDataAfter(d.getAddress()))
            println(String.format("%08x  %s", d.getAddress().getOffset(), d.getDefaultValueRepresentation()));
    }
}
