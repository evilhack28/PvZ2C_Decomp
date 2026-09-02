# tools

All Python, all driven by `config.py` (which reads the per-machine
`config_local.py` written by `configure.py`).

The repo root also has `diff.py` (one function, game vs ours, finds the file
for you), `first_diff.py` (what is left, biggest first) and
`diff_settings.py` (a shim for asm-differ / decomp-permuter). `make` wraps
all of this — see the top-level `Makefile`.

## Setup

| tool | what it does |
| --- | --- |
| `extract.py <apk>` | pull `libSrc.so` out of the 3.5.7 APK (path or url), verify SHA256 |
| `configure.py` | find the NDK and `libSrc.so`, write `config_local.py` |
| `config.py` | paths and build flags; imported by everything else |
| `findincludes.py` | compile a probe and add missing header dirs to `-I` |

## Progress

| tool | what it does |
| --- | --- |
| `progress.py` | compile all of `src/`, diff every function; `--report`, `--check`, `--cache`, `--all` |
| `scaffold.py` | regenerate the `src/` stubs + `units.json` from the library |
| `plant.py <Name>` | one plant's methods: matched / near / not written, with `--todo`, `--calls`, `--callers` |
| `m.py <file.cpp>` | compile one translation unit, diff every function it shares with the game |
| `sweep.py <file.cpp>` | try the file under several flag sets, report which matches most |

## One function at a time

| tool | what it does |
| --- | --- |
| `disas.py <symbol>` | disassemble one game function, strings and symbols named |
| `explain.py <symbol>` | annotated disassembly: floats resolved, member offsets labelled, unnamed clones followed |
| `fndiff.py <Name> <method>` | aligned game-vs-ours listing for one method; `--shape` compares mnemonics only |
| `rawdiff.py` | byte-level diff, no normalisation |
| `asmdiff.py` | the normaliser the others call |

## Layout and vtables

| tool | what it does |
| --- | --- |
| `fields.py <Class> [Class...]` | every reflected field with the offset the game registers |
| `layoutdiff.py <Class> <Header.h>` | game offsets vs `offsetof` in the headers; every delta must be `+0` |
| `layout.cpp` | the probe `layoutdiff.py` compiles |
| `vtable.py <Class>` | dump a vtable from the library |
| `vtdiff.py <Class>` | our vtable vs the game's, when our build emits `_ZTV<class>` |
| `vtprobe.py <Class> <Header.h>` | same, by symbol name, when nothing emits the vtable |
| `slotprobe.py <Class> <Header.h> <method>...` | which no-argument virtual produces a given offset |
| `exprprobe.py <Header.h> '<params>' '<call>'...` | same for virtuals that take arguments |

`pvzelf.py` — minimal ELF reader, shared by the rest.
