# tools

All Python, all driven by `config.py` (which reads the per-machine
`config_local.py` written by `configure.py`).

The repo root also has `first_diff.py` (what is left across the whole tree,
biggest first). `make` wraps all of this — see the top-level `Makefile`.

## Setup

| tool | what it does |
| --- | --- |
| `extract.py <apk>` | pull `libSrc.so` out of the 3.5.7 APK (path or url), verify SHA256 |
| `configure.py` | find the NDK and `libSrc.so`, write `config_local.py` |
| `config.py` | paths and build flags; imported by everything else |
| `scaffold.py` | regenerate the `src/` stubs + `units.json` from the library |
| `genstage.py <Name>` | scaffold `<Name>Stage.cpp` -- RT_CLASS boilerplate for the stage / properties pair |

## Progress

| tool | what it does |
| --- | --- |
| `progress.py` | compile all of `src/`, diff every function; `<File>.cpp --quiet`, `--report`, `--check` |
| `chk.py <file.cpp> [-d] [pat]` | one compile, match state of every function in the file |
| `plant.py <Name>` | one plant's methods: matched / near / not written, with `--todo`, `--calls`, `--callers` |
| `m.py <file.cpp>` | compile one translation unit, diff every function it shares with the game |
| `ltodiff.py <src>... -f <sym>` | whole-program `-flto` diff, for the LTO-sensitive list |

## One function at a time

| tool | what it does |
| --- | --- |
| `wd.py <sym>...` / `<Class> <method>...` / `<file.cpp> <sym>...` | only the instructions that still differ; one compile for many functions. `-s` source + header decl, `--asm [--ours]` clean listing, `--shape` mnemonics only, `-a` all lines, `-c N` context |
| `recon.py <sym>` | decompile (Ghidra or IDA) + annotated game asm, members / vslots / calls named |
| `oracle.py <Script> [args]` | run an `oracle_scripts/` script (`RawFn`, `Grep`, `XrefsTo`, `WhoWrites`, ...) on this machine's Ghidra or IDA 9.x; `--list` names them |
| `explain.py <sym>` | annotated disassembly: floats resolved, member offsets labelled, unnamed clones followed |
| `guess.py <sym>` / `--class <Name>` | a draft body from the function's shape (empty, accessor, flag, forwarder, RT_CLASS). A start, never an answer |
| `autofill.py <file.cpp> [--dry]` | write missing methods, keep only what compiles to OK |
| `permute.py <Class> <method> [--variants F [--apply]]` | hill-climb one function, or score hand-written variants in parallel |
| `reflect.py <Class> [--cpp]` | a `StaticClassInit` straight to `REFLECTION_CLASSBUILDER` lines |

## Cleaning source

| tool | what it does |
| --- | --- |
| `tidy.py [file.cpp...]` | all of the below (layout only when given < 20 files) |
| `tidy.py args` | rename `i_arg` placeholders to the header's parameter names |
| `tidy.py nums [--report]` | `(Enum)N`, `case N:`, `x == N`, `x = N;` on enum-typed values -> the enumerator; kept only if the object is byte-identical. `--report` lists literals it could not type |
| `tidy.py layout <file>...` | group a file into Lifecycle / Reflection / Accessors / Logic sections |

## Layout and vtables

| tool | what it does |
| --- | --- |
| `off.py <Class> [member...]` | `offsetof` / `sizeof` from the headers; `--all` every declared field |
| `off.py <Class> --game` | the game's reflected field offsets vs the headers; every delta must be `+0` |
| `vt.py <Class>` | our vtable vs the game's (falls back to `names` when our build emits none) |
| `vt.py names <Class>` | slot numbering by symbol name; says where missing declarations belong |
| `vt.py slot <Class> [0xOFF\|method...]` | which no-argument virtual compiles to an offset (ICF-proof naming) |
| `vt.py expr ['<params>' '<call>']...` | same for virtuals that take arguments |
| `vt.py fix <Class>... [--chain]` | pad a header until its slots and size agree with the game |

Headers are found automatically (`lib/hdrindex.py`); `--hdr <path>` overrides.

## Running in the game

| tool | what it does |
| --- | --- |
| `hybrid.py <src.cpp>...` | build `libpvzours.so` from matched functions + a Frida loader; `hybrid.py run [s]` launches it |
| `trace/` | Frida boot traces (`trace_run.py`, `trace_live.py`, `trace_all.py`) and their results |
| `mods/` | cheat menus (3.5.7 / 4.2.4 / 9.6.1), console, and the 4.2.4 / 9.6.1 RE scripts (local only) |

## Layout

```
tools/*.py            the commands above (plus config.py / config_local.py)
tools/lib/            modules the commands import, never run directly:
                      asmdiff (normaliser), pvzelf (ELF reader), fastcc (cached /
                      PCH compiles), hdrindex, fields, layout, foldcopy, ctorinit
tools/oracle_scripts/ ghidra/*.java and ida/*.py: the same scripts for each
                      decompiler (same arguments, same output); ida_api.py is the
                      IDA side, asmtext.py prints capstone in Ghidra's syntax
tools/trace/          Frida boot traces
```

Import a library as `from lib import pvzelf` (run from `tools/`, or put
`tools/` on `sys.path`). Oracle script addresses are the decompiler's own:
ref-lib + `GHIDRA_ADDR_BIAS` / `IDA_ADDR_BIAS`.
