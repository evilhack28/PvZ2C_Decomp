"""Compile a .cpp only when it or a header it includes changed; optionally through a per-file precompiled header."""

import glob
import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
import threading
import time

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import config

_FLAG_FILES = [os.path.join(config.HERE, 'tools', f) for f in ('config.py', 'config_local.py')] + [config.GXX]
PCH_DIR = os.path.join(config.BUILD, 'pch')
PCH_KEEP = 8

# NDK r10e's Windows cc1plus caps a PCH at 128 MB (host-mingw32.c pch_VA_max_size); ours are ~500 MB.
# A copy with those three immediates raised to 1 GB lives in build/pchcc; the NDK is never touched.
_CC1_SHA256 = '552daca2e6647cfb7ced0dc6872b8c9cf86fe1580c5230ebbfdf79e4102cb5f5'
_CC1_PATCHES = [(0x33f48b, '4881fa00000008'), (0x33f4a2, 'ba00000008'), (0x33f5b9, '4881fa00000008')]


def object_path(source):
    """The one .o per source that wd.py, progress.py and make check all share."""
    rel = os.path.relpath(os.path.abspath(source), config.HERE)
    return os.path.join(config.BUILD, rel.replace(os.sep, '__').replace('/', '__').replace('.cpp', '.o'))


def _deps(dep):
    try:
        text = open(dep, encoding='utf-8', errors='replace').read()
    except OSError:
        return None
    body = text.replace('\\\n', ' ').split(':', 1)
    if len(body) != 2:
        return None
    return [p.replace('\\ ', ' ') for p in re.split(r'(?<!\\)\s+', body[1].strip()) if p]


def _fresh(target, dep, extra=()):
    if not (os.path.exists(target) and os.path.exists(dep)):
        return False
    files = _deps(dep)
    if not files:
        return False
    t = os.path.getmtime(target)
    try:
        return all(os.path.getmtime(f) <= t for f in [*files, *extra, *(f for f in _FLAG_FILES if os.path.exists(f))])
    except OSError:
        return False


def up_to_date(source, obj):
    dep = obj[:-2] + '.d'
    if os.path.exists(obj) and not os.path.exists(dep):
        # an object from before depfiles: a preprocess-only pass (~0.3s) recovers its inputs
        subprocess.run([config.GXX, *config.CXXFLAGS, '-MM', '-MT', 'o', '-MF', dep, source], capture_output=True)
    return _fresh(obj, dep, [source])


def _fail(obj, dep, err):
    for f in (obj, dep):
        if os.path.exists(f):
            os.remove(f)
    return None, err


def _plain(source, obj):
    dep = obj[:-2] + '.d'
    r = subprocess.run([config.GXX, *config.CXXFLAGS, '-MMD', '-MT', 'o', '-MF', dep, '-c', source, '-o', obj],
                       capture_output=True, text=True)
    return (obj, r.stderr) if r.returncode == 0 else _fail(obj, dep, r.stderr)


def _pch_compiler():
    """-B directory holding the patched cc1plus, or None when this NDK is not the one the patch fits."""
    out = os.path.join(config.BUILD, 'pchcc')
    exe = os.path.join(out, 'cc1plus.exe')
    if os.path.exists(exe):
        return out.replace(os.sep, '/') + '/'
    src = glob.glob(os.path.join(config.TOOLCHAIN, 'libexec', 'gcc', '*', '*', 'cc1plus.exe'))
    if not src:
        return None
    data = bytearray(open(src[0], 'rb').read())
    if hashlib.sha256(data).hexdigest() != _CC1_SHA256:
        return None
    for off, old in _CC1_PATCHES:
        old = bytes.fromhex(old)
        if data[off:off + len(old)] != old:
            return None
        data[off + len(old) - 4:off + len(old)] = (0x40000000).to_bytes(4, 'little')
    os.makedirs(out, exist_ok=True)
    open(exe, 'wb').write(data)
    return out.replace(os.sep, '/') + '/'


def split_prefix(lines):
    """Index after the last top-level #include of the leading preprocessor block (0 if none)."""
    last, depth, in_block = 0, 0, False
    for i, ln in enumerate(lines):
        s = ln.strip()
        if in_block:
            in_block = '*/' not in s
            continue
        if not s or s.startswith('//'):
            continue
        if s.startswith('/*'):
            in_block = '*/' not in s
            continue
        if not s.startswith('#'):
            break
        d = re.match(r'#\s*(\w+)', s)
        d = d.group(1) if d else ''
        if d in ('if', 'ifdef', 'ifndef'):
            depth += 1
        elif d == 'endif':
            depth -= 1
        elif d == 'include' and depth == 0:
            last = i + 1
    return last if depth == 0 else 0


def _prune():
    """Keep the PCH_KEEP newest precompiled headers plus any used in the last 10 minutes."""
    dirs = sorted((d for d in glob.glob(os.path.join(PCH_DIR, '*')) if os.path.isdir(d)),
                  key=os.path.getmtime, reverse=True)
    for d in dirs[PCH_KEEP:]:
        if time.time() - os.path.getmtime(d) > 600:
            shutil.rmtree(d, ignore_errors=True)


_gch_lock = threading.Lock()


def _gch_for(source, prefix, bdir):
    """Path of an up-to-date .gch of `prefix` for `source`, building it if needed; None if it cannot be built."""
    # keyed by prefix too: another process rebuilding a different prefix must not replace a .gch in use
    work = os.path.join(PCH_DIR, hashlib.md5((source + '\0' + prefix).encode()).hexdigest()[:10])
    hdr = os.path.join(work, 'prefix.h')
    gch, hdep = hdr + '.gch', hdr + '.d'
    with _gch_lock:
        os.makedirs(work, exist_ok=True)
        os.utime(work)
        old = open(hdr, encoding='utf-8').read() if os.path.exists(hdr) else None
        if old == prefix and _fresh(gch, hdep):
            return hdr
        open(hdr, 'w', encoding='utf-8', newline='').write(prefix)
        tmp = f'{gch}.{os.getpid()}'
        r = subprocess.run([config.GXX, *config.CXXFLAGS, '-B', bdir, '-iquote', os.path.dirname(source),
                            '-x', 'c++-header', hdr, '-o', tmp, '-MMD', '-MT', 'o', '-MF', hdep],
                           capture_output=True, text=True)
        if r.returncode != 0:
            _fail(tmp, hdep, '')
            return None
        os.replace(tmp, gch)
        _prune()
        return hdr


def _with_pch(source, text, obj):
    """Compile `text` as if it were `source`, its leading #include block read from a .gch. None = could not."""
    bdir = _pch_compiler()
    if bdir is None:
        return None
    lines = text.replace('\r\n', '\n').split('\n')
    n = split_prefix(lines)
    if n == 0:
        return None
    hdr = _gch_for(source, '\n'.join(lines[:n]) + '\n', bdir)
    if hdr is None:
        return None
    # same basename as the source, so _GLOBAL__sub_I_<file> keeps its name
    jobdir = os.path.join(os.path.dirname(hdr), f'j{os.getpid()}_{threading.get_ident()}')
    os.makedirs(jobdir, exist_ok=True)
    body = os.path.join(jobdir, os.path.basename(source))
    open(body, 'w', encoding='utf-8', newline='').write(
        f'#include "{hdr.replace(os.sep, "/")}"\n#line {n + 1} "{source.replace(os.sep, "/")}"\n' + '\n'.join(lines[n:]))
    dep, bdep = obj[:-2] + '.d', os.path.join(jobdir, 'body.d')
    r = subprocess.run([config.GXX, *config.CXXFLAGS, '-B', bdir, '-iquote', os.path.dirname(source),
                        '-MMD', '-MT', 'o', '-MF', bdep, '-c', body, '-o', obj], capture_output=True, text=True)
    if r.returncode != 0:
        if 'error' not in r.stderr:
            return None             # cc1plus could not map the .gch; a plain compile still can
        return _fail(obj, dep, r.stderr)
    skip = {os.path.normcase(os.path.abspath(f)) for f in (hdr, hdr + '.gch', body)}
    files = [source] + [f for f in (_deps(hdr + '.d') or []) + (_deps(bdep) or [])
                        if os.path.normcase(os.path.abspath(f)) not in skip]
    open(dep, 'w', encoding='utf-8').write('o: ' + ' \\\n '.join(f.replace(' ', '\\ ') for f in files) + '\n')
    return obj, r.stderr


def _alive(pid):
    if os.name != 'nt':
        try:
            os.kill(pid, 0)
            return True
        except OSError:
            return False
    import ctypes
    k = ctypes.windll.kernel32
    h = k.OpenProcess(0x100000, False, pid)     # SYNCHRONIZE
    if not h:
        return False
    try:
        return k.WaitForSingleObject(h, 0) == 0x102   # WAIT_TIMEOUT: still running
    finally:
        k.CloseHandle(h)


def _lock(obj):
    """Hold obj + '.lock' so two processes (warm-up, wd.py, make check) never write one .o at once. -> True if another holder finished first."""
    lock, waited = obj + '.lock', False
    while True:
        try:
            fd = os.open(lock, os.O_CREAT | os.O_EXCL | os.O_WRONLY)
            os.write(fd, str(os.getpid()).encode())
            os.close(fd)
            return waited
        except FileExistsError:
            try:
                pid = int(open(lock).read() or 0)
                if (pid and not _alive(pid)) or time.time() - os.path.getmtime(lock) > 900:
                    os.remove(lock)     # left by a killed process
                    continue
            except (OSError, ValueError):
                continue
            waited = True
            time.sleep(0.5)


def compile_file(source, obj=None, force=False, pch=False):
    """-> (obj or None, stderr). Skips the compiler when nothing obj depends on changed."""
    source = os.path.abspath(source)
    obj = obj or object_path(source)
    if not force and up_to_date(source, obj):
        return obj, ''
    os.makedirs(os.path.dirname(os.path.abspath(obj)), exist_ok=True)
    waited = _lock(obj)
    try:
        if waited and not force and up_to_date(source, obj):
            return obj, ''
        if pch and os.name == 'nt':
            done = _with_pch(source, open(source, encoding='utf-8', errors='replace').read(), obj)
            if done is not None:
                return done
        return _plain(source, obj)
    finally:
        try:
            os.remove(obj + '.lock')
        except OSError:
            pass


def warm_pch(source):
    """Build source's precompiled #include block now, so its next edit compiles in seconds. -> True if one exists."""
    bdir = _pch_compiler()
    source = os.path.abspath(source)
    lines = open(source, encoding='utf-8', errors='replace').read().replace('\r\n', '\n').split('\n')
    n = split_prefix(lines)
    return bool(bdir and n and _gch_for(source, '\n'.join(lines[:n]) + '\n', bdir))


def compile_text(source, text, obj):
    """-> (obj or None, stderr) for `text` compiled in place of `source` (a variant of it); uses source's PCH."""
    source = os.path.abspath(source)
    os.makedirs(os.path.dirname(os.path.abspath(obj)), exist_ok=True)
    if os.name == 'nt':
        done = _with_pch(source, text, obj)
        if done is not None:
            return done
    jobdir = os.path.join(PCH_DIR, 'plain', f'j{os.getpid()}_{threading.get_ident()}')
    os.makedirs(jobdir, exist_ok=True)
    path = os.path.join(jobdir, os.path.basename(source))
    open(path, 'w', encoding='utf-8', newline='').write(f'#line 1 "{source.replace(os.sep, "/")}"\n' + text)
    r = subprocess.run([config.GXX, *config.CXXFLAGS, '-iquote', os.path.dirname(source), '-c', path, '-o', obj],
                       capture_output=True, text=True)
    return (obj, r.stderr) if r.returncode == 0 else _fail(obj, obj[:-2] + '.d', r.stderr)



def header_deps(source, text):
    """Files the precompiled #include block of `text` (compiled as `source`) was built from, or None."""
    lines = text.replace('\r\n', '\n').split('\n')
    n = split_prefix(lines)
    prefix = '\n'.join(lines[:n]) + '\n'
    work = os.path.join(PCH_DIR, hashlib.md5((os.path.abspath(source) + '\0' + prefix).encode()).hexdigest()[:10])
    deps = _deps(os.path.join(work, 'prefix.h.d')) if n else None
    return [os.path.abspath(f) for f in deps] if deps else None


def memo(key, run):
    """run() -> (value, obj or [dep files]); value is reused until one of those headers changes. JSON values only."""
    path = os.path.join(config.BUILD, 'probe-cache', hashlib.md5(repr((key, config.CXXFLAGS)).encode()).hexdigest() + '.json')
    try:
        saved = json.load(open(path, encoding='utf-8'))
        t = os.path.getmtime(path)
        if all(os.path.getmtime(f) <= t for f in saved['deps'] + [f for f in _FLAG_FILES if os.path.exists(f)]):
            return saved['value']
    except (OSError, ValueError, KeyError):
        pass
    value, obj = run()
    deps = obj if isinstance(obj, list) else obj and _deps(obj[:-2] + '.d')
    if deps:
        # the probe's own .cpp is rewritten each run; only what it includes decides the answer
        deps = [os.path.abspath(f) for f in (deps if isinstance(obj, list) else deps[1:])]
        os.makedirs(os.path.dirname(path), exist_ok=True)
        json.dump({'deps': deps, 'value': value}, open(path, 'w', encoding='utf-8'))
    return value


if __name__ == '__main__':
    o, err = compile_file(sys.argv[1], force='--force' in sys.argv, pch='--pch' in sys.argv)
    print(o or '\n'.join(l for l in err.splitlines() if 'error' in l)[:2000])
