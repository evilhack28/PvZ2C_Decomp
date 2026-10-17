// Find ASCII/UTF-16/UTF-32 occurrences of a needle in all memory.  -postScript StrFind.java <needle>
//@category PvZ2C
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;

public class StrFind extends GhidraScript {
    public void run() throws Exception {
        String n = getScriptArgs()[0];
        String[] enc = {"a", "u16", "u32"};
        for (String e : enc) {
            byte[] b = new byte[n.length() * (e.equals("a") ? 1 : e.equals("u16") ? 2 : 4)];
            int w = b.length / n.length();
            for (int i = 0; i < n.length(); i++) b[i * w] = (byte) n.charAt(i);
            Address a = currentProgram.getMinAddress();
            int c = 0;
            while (a != null && c < 20) {
                a = currentProgram.getMemory().findBytes(a, b, null, true, monitor);
                if (a == null) break;
                println(a.toString() + " " + e);
                a = a.add(1);
                c++;
            }
        }
        println("done " + n);
    }
}
