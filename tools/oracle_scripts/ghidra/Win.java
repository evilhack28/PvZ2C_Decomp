// Instruction window around an address: -postScript Win.java <hex> [beforeInsns] [afterInsns]
//@category PvZ2C
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Instruction;

public class Win extends GhidraScript {
    public void run() throws Exception {
        String[] a = getScriptArgs();
        int b = a.length > 1 ? Integer.parseInt(a[1]) : 20, f = a.length > 2 ? Integer.parseInt(a[2]) : 20;
        Instruction i = getInstructionContaining(toAddr(a[0]));
        for (int k = 0; k < b && i.getPrevious() != null; k++) i = i.getPrevious();
        for (int k = 0; k < b + f && i != null; k++, i = i.getNext()) println(String.format("%08x  %s", i.getAddress().getOffset(), i));
    }
}
