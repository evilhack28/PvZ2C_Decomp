// Finds the biggest function referencing a given string and prints every string it references, in instruction order: -postScript SetupStrs.java <needle>
//@category PvZ2C
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.mem.Memory;

public class SetupStrs extends GhidraScript {
    String cstr(Address a) throws Exception {
        StringBuilder sb = new StringBuilder();
        Memory m = currentProgram.getMemory();
        for (int i = 0; i < 80; i++) { int b = m.getByte(a.add(i)) & 0xff; if (b == 0) break; if (b < 32 || b > 126) return null; sb.append((char) b); }
        return sb.length() > 1 ? sb.toString() : null;
    }
    public void run() throws Exception {
        String needle = getScriptArgs()[0];
        byte[] nb = needle.getBytes();
        byte[] pb = new byte[nb.length + 2];
        System.arraycopy(nb, 0, pb, 1, nb.length);
        Memory m = currentProgram.getMemory();
        Function best = null;
        Address sa = currentProgram.getMinAddress();
        while (true) {
            sa = m.findBytes(sa, pb, null, true, monitor);
            if (sa == null) break;
            Address ha = sa.add(1);
            for (Reference r : getReferencesTo(ha)) {
                Function f = getFunctionContaining(r.getFromAddress());
                if (f != null && (best == null || f.getBody().getNumAddresses() > best.getBody().getNumAddresses())) best = f;
            }
            sa = ha;
        }
        if (best == null) { println("NOFUNC"); return; }
        println("FUNC " + best.getEntryPoint() + " size " + best.getBody().getNumAddresses());
        Listing l = currentProgram.getListing();
        InstructionIterator it = l.getInstructions(best.getBody(), true); int nref = 0, ninst = 0;
        while (it.hasNext()) {
            Instruction ins = it.next(); ninst++;
            for (Reference r : ins.getReferencesFrom()) { nref++;
                if (r.getToAddress().isMemoryAddress() && !r.getReferenceType().isCall()) {
                    String s = null; try { s = cstr(r.getToAddress()); } catch (Exception e) { }
                    if (s != null) println("S " + s);
                }
            }
        }
        println("inst " + ninst + " refs " + nref);
    }
}
