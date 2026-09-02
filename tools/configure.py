"""Detect the NDK and reference library, write them to tools/config_local.py.

    py -3 tools/configure.py [--ndk PATH] [--lib PATH] [--show]
"""

import argparse
import hashlib
import os
import struct
import sys

HERE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LOCAL = os.path.join(HERE, 'tools', 'config_local.py')

# libSrc.so, arm64-v8a, from the 3.5.7 CN TV client (see README / INSTALL).
TARGET_SHA256 = '12bbf37af8c9d6201d00c8267fef30f735f26ba5753e540e043d1ed849695377'
TARGET_SIZE = 110723808

# .comment string of the shipped lib -- only NDK r10e's GCC 4.9 prints this.
WANT_COMMENT = b'GCC: (GNU) 4.9 20140827 (prerelease)'


def _rel(*p):
    return os.path.normpath(os.path.join(HERE, *p))


NDK_CANDIDATES = [
    os.environ.get('PVZ2C_NDK'),
    _rel('..', 'android-ndk-r10e'),
    os.path.expanduser('~/tools/android-ndk-r10e'),
    os.path.expanduser('~/android-ndk-r10e'),
    r'C:/android-ndk-r10e',
    '/opt/android-ndk-r10e',
]

LIB_CANDIDATES = [
    os.environ.get('PVZ2C_TARGET_LIB'),
    _rel('reference', 'libSrc.so'),
    _rel('libSrc.so'),
]


def gxx_for(ndk):
    for host in ('windows-x86_64', 'windows', 'linux-x86_64', 'darwin-x86_64'):
        for exe in ('aarch64-linux-android-g++.exe', 'aarch64-linux-android-g++'):
            p = os.path.join(ndk, 'toolchains', 'aarch64-linux-android-4.9',
                             'prebuilt', host, 'bin', exe)
            if os.path.isfile(p):
                return p
    return None


def ndk_ok(ndk):
    if not ndk or not os.path.isdir(ndk):
        return None
    gxx = gxx_for(ndk)
    if not gxx:
        return None
    import subprocess
    try:
        out = subprocess.run([gxx, '--version'], capture_output=True,
                             text=True, timeout=30).stdout
    except Exception:
        return None
    if '4.9 20140827' in out:
        return ndk
    print(f'  ! {ndk}: {out.splitlines()[0].strip()} -- wrong GCC, will not match')
    return None


def comment_of(path):
    try:
        f = open(path, 'rb')
    except OSError:
        return None
    with f:
        head = f.read(64)
        if head[:4] != b'\x7fELF' or head[4] != 2:
            return None
        shoff, = struct.unpack('<Q', head[0x28:0x30])
        shentsize, shnum, shstrndx = struct.unpack('<HHH', head[0x3A:0x40])
        f.seek(shoff)
        sh = [f.read(shentsize) for _ in range(shnum)]
        field = lambda e: struct.unpack('<QQ', e[0x18:0x28])
        stroff, strsize = field(sh[shstrndx])
        f.seek(stroff)
        strtab = f.read(strsize)
        for s in sh:
            nameoff, = struct.unpack('<I', s[0:4])
            if strtab[nameoff:strtab.index(b'\0', nameoff)] == b'.comment':
                off, size = field(s)
                f.seek(off)
                return f.read(size)
    return None


def lib_ok(path):
    if not path or not os.path.isfile(path):
        return None
    if os.path.getsize(path) == TARGET_SIZE:
        h = hashlib.sha256(open(path, 'rb').read()).hexdigest()
        if h == TARGET_SHA256:
            return path
        print(f'  ! {path}: sha256 {h} != expected {TARGET_SHA256}')
        return None
    c = comment_of(path)
    if c and WANT_COMMENT in c:
        print(f'  ! {path}: right toolchain but not the 3.5.7 arm64-v8a build (hash differs)')
        return path
    if c:
        print(f'  ! {path}: .comment {c!r} is not the 3.5.7 build')
    return None


def write_local(ndk, lib):
    with open(LOCAL, 'w') as f:
        f.write('# Written by tools/configure.py -- per-machine, git-ignored.\n')
        f.write(f'NDK = r"{ndk}"\nTARGET_LIB = r"{lib}"\n')
    print(f'wrote {os.path.relpath(LOCAL, HERE)}\n  NDK        {ndk}\n  TARGET_LIB {lib}')


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--ndk')
    ap.add_argument('--lib')
    ap.add_argument('--show', action='store_true')
    args = ap.parse_args()

    if args.show:
        print(open(LOCAL).read() if os.path.exists(LOCAL) else 'not configured yet')
        return

    ndk = ndk_ok(args.ndk) or next((n for n in map(ndk_ok, NDK_CANDIDATES) if n), None)
    lib = lib_ok(args.lib) or next((l for l in map(lib_ok, LIB_CANDIDATES) if l), None)

    if not ndk:
        print('NDK r10e not found -- pass --ndk PATH (see INSTALL.md).')
    if not lib:
        print('Reference libSrc.so not found. Get it with:\n'
              '  py -3 tools/extract.py <3.5.7 apk/zip>\n'
              'or pass --lib PATH (see INSTALL.md).')
    if not (ndk and lib):
        sys.exit(1)
    write_local(ndk, lib)


if __name__ == '__main__':
    main()
