# Setup

`./installDependencies.sh` does all of this from a bash shell. The manual
steps:

## 1. Python

3.10+, with two packages. Commands below use `python`. On Windows that name is
often the Microsoft Store stub instead: turn off the `python.exe` / `python3.exe`
App execution aliases (Settings > Apps > Advanced app settings), or in Git Bash
add `~/bin/python` and `~/bin/python3` containing
`exec "/c/Program Files/Python312/python.exe" "$@"`. `py -3` works either way.

```
python -m pip install capstone pyelftools
```

## 2. Android NDK r10e

The shipped library's `.comment` is `GCC: (GNU) 4.9 20140827 (prerelease)` —
the aarch64 GCC in **NDK r10e** and no other. Newer GCC 4.9 (r11–r16) will
compile but not match. Unpack the three parts that are needed:

```
curl -L -o ndk.exe https://dl.google.com/android/ndk/android-ndk-r10e-windows-x86_64.exe
7z x ndk.exe \
  "android-ndk-r10e/toolchains/aarch64-linux-android-4.9/prebuilt/windows-x86_64/*" \
  "android-ndk-r10e/platforms/android-21/arch-arm64/*" \
  "android-ndk-r10e/sources/cxx-stl/gnu-libstdc++/4.9/*"
```

Put `android-ndk-r10e/` anywhere; on Linux/macOS use the `-linux-x86_64.bin`
/ `-darwin-x86_64.bin` archive.

## 3. The reference library

`libSrc.so`, `arm64-v8a`, from the 3.5.7 CN TV client:

```
SHA256  12bbf37af8c9d6201d00c8267fef30f735f26ba5753e540e043d1ed849695377
size    110723808
```

The APK is at <https://archive.org/details/com.popcap.pvz2cthdxy51>
(`com.popcap.pvz2cthdxy51.zip`). Pull the library out and put it at
`./reference/libSrc.so`:

```
python tools/extract.py <path or url to the apk/zip>
```

`extract.py` handles a plain APK or a zip-wrapped one, and verifies the
SHA256. Or place any copy at `./reference/libSrc.so` yourself, or set
`PVZ2C_TARGET_LIB`.

## 4. Configure

```
python tools/configure.py       # writes tools/config_local.py (git-ignored)
python tools/scaffold.py        # regenerate the src/ stubs + units.json
python tools/progress.py        # should now compile src/ and print a percentage
```

Overrides: `configure.py --ndk PATH --lib PATH`, or the `PVZ2C_NDK` /
`PVZ2C_TARGET_LIB` environment variables. `--author "Name"` sets the name
written into new `.cpp` headers (default: `git config user.name`).

## 5. Decompiler (optional)

Only `recon.py` and `reflect.py` use one; everything else needs just the NDK.
Add one of these to `tools/config_local.py`.

Ghidra: `GHIDRA_HEADLESS`, `GHIDRA_PROJECT_DIR`, `GHIDRA_PROJECT`,
`GHIDRA_PROGRAM`, `GHIDRA_SCRIPTS`, `GHIDRA_ADDR_BIAS` (Ghidra address minus
`libSrc.so` address, usually `0x100000`).

IDA 9.x with the Hex-Rays ARM64 decompiler, through idalib:

```
python -m pip install "<IDA dir>/idalib/python"
python "<IDA dir>/idalib/python/py-activate-idalib.py"
```

```
IDA_DB = r"C:\path\libSrc_tools.i64"   # a copy: the GUI locks the one it has open
IDA_PYTHON = None                      # or the interpreter that has idapro, if not this one
IDA_ADDR_BIAS = 0                      # IDA address minus libSrc.so address
```

`IDA_PYTHON` also needs `capstone` (`python -m pip install capstone`).

Check: `python tools/oracle.py Decomp <Class::method>`; `oracle.py --list`
names every script. The same scripts exist for both decompilers.
