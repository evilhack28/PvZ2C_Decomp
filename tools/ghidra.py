"""ghidra.py -- cached wrapper over the Ghidra headless oracle. `from ghidra import decompile`."""

import hashlib
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import config

CACHE = os.path.join(config.BUILD, 'ghidra-cache')


def _biased(tok):
    """A bare hex reference address -> the Ghidra address; names pass through."""
    tok = tok.strip()
    if re.fullmatch(r'(0x)?[0-9a-fA-F]{5,9}', tok):   # a game address, not a name
        return f'{int(tok, 16) + config.GHIDRA_ADDR_BIAS:x}'
    return tok


def decompile(*targets, fresh=False, script='Decomp.java'):
    """Run a Ghidra script over `targets`, return its stdout (cached).

    Targets are comma-joined into one script arg. Hex targets are treated as
    reference-lib addresses and biased to Ghidra's load address.
    """
    if not config.GHIDRA_HEADLESS:
        raise SystemExit('Ghidra not configured -- add GHIDRA_* to tools/config_local.py '
                         '(see docs/SESSION-HANDOFF.md "Ghidra oracle")')
    arg = ','.join(_biased(t) for t in targets)
    key = hashlib.sha1(f'{script}\0{arg}'.encode()).hexdigest()[:16]
    cached = os.path.join(CACHE, f'{key}.txt')
    if not fresh and os.path.exists(cached):
        return open(cached, encoding='utf-8', errors='replace').read()

    cmd = [config.GHIDRA_HEADLESS, config.GHIDRA_PROJECT_DIR, config.GHIDRA_PROJECT,
           '-process', config.GHIDRA_PROGRAM, '-noanalysis',
           '-scriptPath', config.GHIDRA_SCRIPTS, '-postScript', script, arg]
    done = subprocess.run(cmd, capture_output=True, text=True)
    out = done.stdout + done.stderr
    # keep only the script's own lines (drop the headless framework chatter)
    lines = [re.sub(r'\s*\(GhidraScript\)\s*$', '', l)
             for l in out.splitlines()
             if not re.match(r'^(INFO|WARN|WARNING|DEBUG|Exception|\s+at |\s*java)', l)]
    lines = [re.sub(r'^INFO\s+\w+\.java>\s?', '', l) for l in lines]
    text = '\n'.join(l for l in lines if l.strip() or True)
    os.makedirs(CACHE, exist_ok=True)
    open(cached, 'w', encoding='utf-8').write(text)
    return text


def function(text, needle):
    """Slice one `// ===== <name> ... =====` section out of a decompile() dump."""
    blocks = re.split(r'(?m)^// ===== ', text)
    for b in blocks[1:]:
        if needle in b.split('\n', 1)[0]:
            return '// ===== ' + b
    return None


if __name__ == '__main__':
    if len(sys.argv) < 2:
        raise SystemExit('usage: python tools/ghidra.py <hex|Class::method> [...]')
    print(decompile(*sys.argv[1:], fresh='--fresh' in sys.argv))
