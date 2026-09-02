# Setup

`./installDependencies.sh` does all of this from a bash shell. The manual
steps:

## 1. Python

3.10+, with two packages. On Windows use `py -3`; bare `python` is often a
broken Store alias.

```
py -3 -m pip install capstone pyelftools
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
py -3 tools/extract.py <path or url to the apk/zip>
```

`extract.py` handles a plain APK or a zip-wrapped one, and verifies the
SHA256. Or place any copy at `./reference/libSrc.so` yourself, or set
`PVZ2C_TARGET_LIB`.

## 4. Configure

```
py -3 tools/configure.py       # writes tools/config_local.py (git-ignored)
py -3 tools/scaffold.py        # regenerate the src/ stubs + units.json
py -3 tools/progress.py        # should now compile src/ and print a percentage
```

Overrides: `configure.py --ndk PATH --lib PATH`, or the `PVZ2C_NDK` /
`PVZ2C_TARGET_LIB` environment variables.
