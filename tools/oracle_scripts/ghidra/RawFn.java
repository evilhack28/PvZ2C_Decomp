// Raw disassembly of a function + the data/type at each address it references.
//   -postScript RawFn.java <funcNameOrAddr>
//@category PvZ2C
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;

public class RawFn extends GhidraScript {
    public void run() throws Exception {
        String arg = getScriptArgs()[0];
        FunctionManager fm = currentProgram.getFunctionManager();
        Listing lst = currentProgram.getListing();
        SymbolTable st = currentProgram.getSymbolTable();
        ReferenceManager rm = currentProgram.getReferenceManager();

        Function f = null;
        try {
            Address a = currentProgram.getAddressFactory().getDefaultAddressSpace()
                        .getAddress(Long.parseLong(arg, 16));
            f = fm.getFunctionContaining(a);
        } catch (Exception e) {}
        if (f == null) for (Function g : fm.getFunctions(true))
            if (g.getName(true).equals(arg) || g.getName().equals(arg)) { f = g; break; }
        if (f == null) { println("not found: " + arg); return; }

        println("=== " + f.getName(true) + "  @ " + f.getEntryPoint()
                + "  size=" + f.getBody().getNumAddresses() + " ===");
        InstructionIterator it = lst.getInstructions(f.getBody(), true);
        while (it.hasNext()) {
            Instruction ins = it.next();
            StringBuilder note = new StringBuilder();
            for (Reference r : ins.getReferencesFrom()) {
                Address t = r.getToAddress();
                Symbol s = st.getPrimarySymbol(t);
                Data d = lst.getDataAt(t);
                note.append("   ; ").append(t);
                if (s != null) note.append(" ").append(s.getName(true));
                if (d != null) {
                    Object v = d.getValue();
                    note.append(" [").append(d.getDataType().getName());
                    if (v != null) note.append(" = ").append(v);
                    note.append("]");
                }
            }
            println(String.format("  %s  %-28s%s", ins.getAddress(), ins.toString(), note));
        }
    }
}
