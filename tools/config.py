"""Paths and build flags. Per-machine paths come from config_local.py
(written by configure.py) or the PVZ2C_NDK / PVZ2C_TARGET_LIB env vars.
Flag rationale: docs/toolchain.md.
"""

import glob
import os

HERE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

try:
    from config_local import NDK, TARGET_LIB
except ImportError:
    NDK = os.environ.get('PVZ2C_NDK')
    TARGET_LIB = os.environ.get('PVZ2C_TARGET_LIB')
    if not (NDK and TARGET_LIB):
        raise SystemExit('not configured -- run: py -3 tools/configure.py  (see INSTALL.md)')

# Optional Ghidra oracle (used by tools/ghidra.py, tools/reflect.py). Set in
# config_local.py or the PVZ2C_GHIDRA_* env vars; tools that need it say so.
try:
    from config_local import GHIDRA_HEADLESS, GHIDRA_PROJECT_DIR, GHIDRA_PROJECT, \
        GHIDRA_PROGRAM, GHIDRA_SCRIPTS, GHIDRA_ADDR_BIAS
except ImportError:
    GHIDRA_HEADLESS = os.environ.get('PVZ2C_GHIDRA_HEADLESS')
    GHIDRA_PROJECT_DIR = os.environ.get('PVZ2C_GHIDRA_PROJECT_DIR')
    GHIDRA_PROJECT = os.environ.get('PVZ2C_GHIDRA_PROJECT')
    GHIDRA_PROGRAM = os.environ.get('PVZ2C_GHIDRA_PROGRAM', 'libSrc.so')
    GHIDRA_SCRIPTS = os.environ.get('PVZ2C_GHIDRA_SCRIPTS')
    # Ghidra loads the .so at a nonzero base: ghidra_addr = ref_addr + BIAS.
    GHIDRA_ADDR_BIAS = int(os.environ.get('PVZ2C_GHIDRA_ADDR_BIAS', '0x100000'), 0)

_hosts = glob.glob(f'{NDK}/toolchains/aarch64-linux-android-4.9/prebuilt/*')
TOOLCHAIN = _hosts[0] if _hosts else (
    f'{NDK}/toolchains/aarch64-linux-android-4.9/prebuilt/windows-x86_64')
_exe = '.exe' if os.path.exists(f'{TOOLCHAIN}/bin/aarch64-linux-android-g++.exe') else ''
GXX = f'{TOOLCHAIN}/bin/aarch64-linux-android-g++{_exe}'
OBJDUMP = f'{TOOLCHAIN}/bin/aarch64-linux-android-objdump{_exe}'
SYSROOT = f'{NDK}/platforms/android-21/arch-arm64'
STL = f'{NDK}/sources/cxx-stl/gnu-libstdc++/4.9'

HEADERS = f'{HERE}/include'
SRC = f'{HERE}/src'
BUILD = f'{HERE}/build'

CXXFLAGS = [
    '-std=gnu++11', '-O2', '-fno-inline', '-fno-exceptions', '-fPIC',
    '-funwind-tables', '-fstack-protector-strong', '-fno-math-errno',
    '-DANDROID', '-DNDEBUG', '-DRELEASEFINAL',
    '-DPRIME_FOR_PVZ2', '-DWANTS_PRIMETEXT', '-DWIDGETS_USE_PRIMETEXT',
    '-DSUPPORT_WWISE', '-DWANTS_WWISE_ENABLED',
    '-D_USE_WIDE_STRING',
    '--sysroot', SYSROOT,
    '-isystem', f'{STL}/include',
    '-isystem', f'{STL}/libs/arm64-v8a/include',
    '-isystem', f'{SYSROOT}/usr/include',
    '-I', f'{HERE}/include',
    '-I', f'{HEADERS}',
    '-I', f'{HEADERS}/PvZ',
    '-I', f'{HEADERS}/SexyAppFramework',
]

# EA middleware, versioned in its own tree
EATECH = f'{HEADERS}/SexyAppFramework/EATech'
for _pkg in ('coreallocator/1.03.11', 'EABase/2.06.01', 'EAIO/2.17.03',
             'EAMGraphicsDriver/1.00.04', 'EAStdC/1.10.02', 'EASTL/1.17.00',
             'EAText/1.09.07', 'EAThread/1.22.05', 'EATrace/2.09.07',
             'PPMalloc/1.20.03'):
    CXXFLAGS += ['-I', f'{EATECH}/{_pkg}/include', '-I', f'{EATECH}/{_pkg}/include/Common']
CXXFLAGS += ['-I', f'{EATECH}/FontFusion/4.5a.06/core']

# headers include each other by bare filename, so every PvZ subdir is on -I
for _root, _dirs, _files in os.walk(f'{HEADERS}/PvZ'):
    if any(f.endswith('.h') for f in _files):
        CXXFLAGS += ['-I', _root.replace(os.sep, '/')]
