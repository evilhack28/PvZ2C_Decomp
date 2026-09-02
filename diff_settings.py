"""Root-level shim for asm-differ / decomp-permuter. Real config is tools/config.py."""

import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), 'tools'))

from config import CXXFLAGS, GXX, OBJDUMP, STL, SYSROOT, TARGET_LIB, TOOLCHAIN  # noqa: F401


def apply(config, args):
    config['baseimg'] = TARGET_LIB
    config['make_command'] = [sys.executable, 'tools/progress.py', '--cache']
    config['arch'] = 'aarch64'
    config['objdump_executable'] = OBJDUMP
