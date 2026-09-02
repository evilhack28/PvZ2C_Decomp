"""Pull libSrc.so (arm64-v8a) out of the 3.5.7 APK into reference/libSrc.so.

    py -3 tools/extract.py <apk-or-zip, path or http(s) url>

Handles a plain APK, or a zip that contains the APK (as archive.org serves
it). Verifies the SHA256 before writing.
"""

import hashlib
import io
import os
import sys
import tempfile
import urllib.request
import zipfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from configure import TARGET_SHA256  # noqa: E402

HERE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OUT = os.path.join(HERE, 'reference', 'libSrc.so')
WANT = 'lib/arm64-v8a/libSrc.so'


def find_lib(zf, depth=0):
    for name in zf.namelist():
        if name.endswith(WANT):
            return zf.read(name)
    if depth == 0:
        for name in zf.namelist():
            if name.lower().endswith('.apk'):
                with zipfile.ZipFile(io.BytesIO(zf.read(name))) as inner:
                    data = find_lib(inner, depth + 1)
                    if data:
                        return data
    return None


def main():
    if len(sys.argv) != 2:
        print(__doc__)
        return 2
    src = sys.argv[1]
    tmp = None
    if src.startswith(('http://', 'https://')):
        tmp = tempfile.NamedTemporaryFile(delete=False, suffix='.zip')
        print(f'downloading {src} ...')
        urllib.request.urlretrieve(src, tmp.name)
        src = tmp.name
    try:
        with zipfile.ZipFile(src) as zf:
            data = find_lib(zf)
    except zipfile.BadZipFile:
        print(f'{sys.argv[1]} is not an apk/zip')
        return 2
    finally:
        if tmp:
            os.unlink(tmp.name)
    if not data:
        print(f'{WANT} not found in {sys.argv[1]}')
        return 1
    h = hashlib.sha256(data).hexdigest()
    if h != TARGET_SHA256:
        print(f'sha256 {h} != expected {TARGET_SHA256} -- wrong build, not writing')
        return 1
    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    open(OUT, 'wb').write(data)
    print(f'wrote {os.path.relpath(OUT, HERE)}  ({len(data)} bytes, sha256 ok)')


if __name__ == '__main__':
    raise SystemExit(main())
