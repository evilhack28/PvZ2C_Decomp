"""Run an oracle script on this machine's decompiler (Ghidra or IDA 9.x): oracle.py [--fresh] <Script> [args...]"""

import hashlib
import importlib
import io
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
SCRIPTS = os.path.join(HERE, 'oracle_scripts')
sys.path.insert(0, HERE)

import config


def backend():
    if config.GHIDRA_HEADLESS:
        return 'ghidra'
    if config.IDA_DB:
        return 'ida'
    raise SystemExit('No decompiler configured -- add GHIDRA_* or IDA_DB to tools/config_local.py (INSTALL.md 5)')


def scripts():
    """Script names available on this machine's backend."""
    if backend() == 'ida':
        return sorted(f[:-3] for f in os.listdir(os.path.join(SCRIPTS, 'ida')) if f.endswith('.py'))
    dirs = [os.path.join(SCRIPTS, 'ghidra')] + ([config.GHIDRA_SCRIPTS] if config.GHIDRA_SCRIPTS else [])
    return sorted({f[:-5] for d in dirs if os.path.isdir(d) for f in os.listdir(d) if f.endswith('.java')})


def _ghidra(script, args):
    path = os.path.join(SCRIPTS, 'ghidra') + (';' + config.GHIDRA_SCRIPTS if config.GHIDRA_SCRIPTS else '')
    cmd = [config.GHIDRA_HEADLESS, config.GHIDRA_PROJECT_DIR, config.GHIDRA_PROJECT,
           '-process', config.GHIDRA_PROGRAM, '-noanalysis', '-readOnly',
           '-scriptPath', path, '-postScript', script + '.java'] + list(args)
    if os.name == 'nt':
        # cmd.exe splits a .bat's arguments at ';' unless the argument is quoted
        cmd = subprocess.list2cmdline(cmd).replace(' ' + subprocess.list2cmdline([path]) + ' ', ' "%s" ' % path)
    done = subprocess.run(cmd, capture_output=True, text=True, encoding='utf-8', errors='replace',
                          stdin=subprocess.DEVNULL)
    # keep only the script's own lines; a framework message's continuation lines go with it
    lines, mine = [], False
    for l in (done.stdout + done.stderr).splitlines():
        m = re.match(r'^INFO\s+\w+\.java>\s?(.*)', l)
        if m:
            mine, l = True, m.group(1)
        elif re.match(r'^(INFO|WARN|WARNING|ERROR|DEBUG|Exception)\b', l):
            mine = False
        if mine:
            lines.append(re.sub(r'\s*\(GhidraScript\)\s*$', '', l))
    return '\n'.join(lines)


def _ida(script, args):
    done = subprocess.run([config.IDA_PYTHON or sys.executable, os.path.abspath(__file__),
                           '--ida-worker', script] + list(args),
                          capture_output=True, text=True, encoding='utf-8', errors='replace')
    if done.returncode:
        raise SystemExit(f'IDA {script} failed ({done.returncode}):\n{done.stderr[-3000:]}')
    out = done.stdout
    return out[out.index('\0') + 1:] if '\0' in out else out


def run(script, args=(), fresh=False):
    """Output of `script` over `args` on this machine's backend (cached in build/<backend>-cache)."""
    b = backend()
    key = hashlib.sha1('\0'.join([script + '.java'] + list(args)).encode()).hexdigest()[:16]
    cached = os.path.join(config.BUILD, f'{b}-cache', f'{key}.txt')
    if not fresh and os.path.exists(cached):
        return open(cached, encoding='utf-8', errors='replace').read()
    text = (_ghidra if b == 'ghidra' else _ida)(script, args)
    os.makedirs(os.path.dirname(cached), exist_ok=True)
    open(cached, 'w', encoding='utf-8').write(text)
    return text


def _worker(script, args):
    import idapro
    sys.path[:0] = [SCRIPTS, os.path.join(SCRIPTS, 'ida')]
    if idapro.open_database(config.IDA_DB, run_auto_analysis=False):
        raise SystemExit(f'cannot open {config.IDA_DB} (open in the IDA GUI? point IDA_DB at a copy)')
    try:
        mod = importlib.import_module(script)
        sys.stdout.write('\0')
        mod.run(list(args))
        sys.stdout.flush()
    finally:
        idapro.close_database(save=False)


if __name__ == '__main__':
    argv = sys.argv[1:]
    if argv[:1] == ['--ida-worker']:
        sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
        _worker(argv[1], argv[2:])
    elif not argv or argv[0] in ('-h', '--help', '--list'):
        print(__doc__ + '\n\nscripts (' + backend() + '): ' + ' '.join(scripts()))
    else:
        fresh = '--fresh' in argv
        argv = [a for a in argv if a != '--fresh']
        print(run(argv[0], argv[1:], fresh=fresh))
