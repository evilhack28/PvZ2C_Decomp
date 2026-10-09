"""ghidra.py -- cached decompile() over this machine's oracle (Ghidra or IDA, see oracle.py)."""

import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import config


def _biased(tok):
    """A bare hex reference address -> the Ghidra address; names pass through."""
    tok = tok.strip()
    if re.fullmatch(r'(0x)?[0-9a-fA-F]{5,9}', tok):   # a game address, not a name
        return f'{int(tok, 16) + config.GHIDRA_ADDR_BIAS:x}'
    return tok


def decompile(*targets, fresh=False, script='Decomp.java'):
    """Decompile `targets` (names or hex ref-lib addresses) on this machine's oracle, return the dump (cached).

    Targets are comma-joined into one script arg. Hex targets are treated as
    reference-lib addresses and biased to the oracle's load address.
    """
    import oracle
    return oracle.run(script[:-5], [','.join(_biased(t) for t in targets)], fresh=fresh)


def function(text, needle):
    """Slice one `// ===== <name> ... =====` section out of a decompile() dump."""
    blocks = re.split(r'(?m)^// ===== ', text)
    for b in blocks[1:]:
        if needle in b.split('\n', 1)[0]:
            return '// ===== ' + b
    return None


if __name__ == '__main__':
    if len(sys.argv) < 2:
        raise SystemExit('usage: py -3 tools/ghidra.py <hex|Class::method> [...]')
    print(decompile(*sys.argv[1:], fresh='--fresh' in sys.argv))
