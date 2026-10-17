"""Network-handler helpers: asm <Class> <m>..., ghidra <Class> <m>, str <hexaddr>..., msg <file.cpp> <Ident> <Name> "<params>" <Sig>."""
import os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PY = [sys.executable]
ANSI = re.compile(r'\x1b\[[0-9;]*m')
NOISE = re.compile(r'^$|^---|ldp  |stp       x(29|19|21)|stack_chk|vslots|^calls|^members|\+0x118|^    \d+ B|, #0x118\]|cmp       x1, x0|ldr       x1, \[x29, #0x[0-9a-f]+\]$')


def run(*args):
    r = subprocess.run(PY + [os.path.join(ROOT, 'tools', args[0])] + list(args[1:]), capture_output=True, text=True, encoding='utf8', errors='replace', cwd=ROOT)
    return ANSI.sub('', r.stdout + r.stderr)


def mangled(cls, name):
    m = re.search(r'_ZN\d+%s\d+%s[A-Za-z0-9_]*' % (cls, name), run('wd.py', cls, name, '-s'))
    return m.group(0) if m else None


def cmd_asm(cls, names):
    for n in names:
        sym = mangled(cls, n)
        print('#####', n)
        if sym:
            print('\n'.join(l[:175] for l in run('recon.py', sym, '--asm-only').split('\n') if not NOISE.search(l)))


def cmd_ghidra(cls, name):
    sym = mangled(cls, name)
    out = run('recon.py', sym) if sym else ''
    keep = re.search(r'--- GHIDRA ---.*?--- ASM ---', out, re.S)
    print(keep.group(0) if keep else out)
    print(out[out.find('--- REFERENCES'):])


def cmd_str(addrs):
    sys.path[:0] = [os.path.join(ROOT, 'tools', 'lib'), os.path.join(ROOT, 'tools')]
    import config
    from pvzelf import Elf
    elf = Elf(config.TARGET_LIB)
    for a in addrs:
        print(a, repr(elf.read_at(int(a, 16), 200).split(b'\0')[0].decode('utf8', 'replace')))


def cmd_msg(path, ident, name, params, sig):
    s = open(path).read()
    if 'void %s(' % ident in s:
        sys.exit('exists')
    line = 'void %s(%s) asm("_ZN7Message%d%s%s");\n' % (ident, params, len(name), name, sig)
    i = s.index('\nvoid INetworkMsgProcess::')
    k = s.index('\n', s.rfind('asm("_ZN7Message', 0, i)) + 1
    open(path, 'w').write(s[:k] + line + s[k:])


if __name__ == '__main__':
    a = sys.argv[1:]
    if len(a) >= 3 and a[0] == 'asm':
        cmd_asm(a[1], a[2:])
    elif len(a) == 3 and a[0] == 'ghidra':
        cmd_ghidra(a[1], a[2])
    elif len(a) >= 2 and a[0] == 'str':
        cmd_str(a[1:])
    elif len(a) == 6 and a[0] == 'msg':
        cmd_msg(*a[1:])
    else:
        sys.exit(__doc__)
