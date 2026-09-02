# PvZ2C

A matching decompilation of the PvZ2 CN 3.5.7 client library (`libSrc.so`,
`arm64-v8a`).

```
SHA256  12bbf37af8c9d6201d00c8267fef30f735f26ba5753e540e043d1ed849695377
size    110723808
```

The APK is archived at
<https://archive.org/details/com.popcap.pvz2cthdxy51>. Pull the library out
with `py -3 tools/extract.py <apk-or-zip>`; it is read in place, never
modified.

## Layout

```
src/           the reconstructed source, one file per translation unit
tools/         extract, configure, compile, disassemble, diff  (tools/README.md)
report.json    committed progress baseline (make check fails on regression)
```

## Use

```
py -3 tools/configure.py           # detect the toolchain, write config_local.py
py -3 tools/progress.py            # compile src/, print the match percentage
py -3 tools/progress.py Iceburg    # one class family
py -3 diff.py <mangled-symbol>     # game vs ours, one function
```

`make` wraps the same commands — see the `Makefile`.
