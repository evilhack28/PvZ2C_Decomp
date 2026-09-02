#!/usr/bin/env bash
# Python deps + Android NDK r10e, then configure. Run from a bash shell.
# Windows PowerShell: run `py -3 tools/configure.py` after `pip install
# capstone pyelftools` instead.
set -u
cd "$(dirname "$0")" || exit 1

# When double-clicked from Explorer, Git Bash closes the window the instant
# the script ends -- success or failure -- and the output just flashes past.
# Hold the window open on any exit if we have a terminal, so the result is
# readable. Non-interactive runs (make, CI) have no tty and are unaffected.
_hold_window() {
    rc=$?
    [ -t 0 ] || return $rc
    if [ $rc -eq 0 ]; then echo; echo ">> all good -- setup complete"
    else echo; echo ">> FAILED (exit $rc) -- see messages above / INSTALL.md"; fi
    printf 'Press Enter to close... '
    read -r _ || true
    return $rc
}
trap _hold_window EXIT

if command -v py >/dev/null 2>&1; then PY="py -3"
elif command -v python3 >/dev/null 2>&1; then PY="python3"
else PY="python"; fi

NDK_DIR="${PVZ2C_NDK:-$HOME/tools/android-ndk-r10e}"

echo ">> capstone, pyelftools"
$PY -m pip install --quiet capstone pyelftools \
  || $PY -m pip install --quiet --user capstone pyelftools || exit 1

echo ">> NDK r10e"
if ls "$NDK_DIR"/toolchains/aarch64-linux-android-4.9/prebuilt/*/bin/aarch64-linux-android-g++* >/dev/null 2>&1; then
    echo "   $NDK_DIR"
else
    case "$(uname -s)" in
        Linux)  HOST=linux-x86_64;  A=android-ndk-r10e-linux-x86_64.bin ;;
        Darwin) HOST=darwin-x86_64; A=android-ndk-r10e-darwin-x86_64.bin ;;
        *)      HOST=windows-x86_64; A=android-ndk-r10e-windows-x86_64.exe ;;
    esac
    SZ=""
    for c in 7z 7za "/c/Program Files/7-Zip/7z.exe"; do
        command -v "$c" >/dev/null 2>&1 && { SZ="$c"; break; }
        [ -x "$c" ] && { SZ="$c"; break; }
    done
    [ -z "$SZ" ] && { echo "   need 7-Zip; unpack r10e by hand (see INSTALL.md)"; exit 1; }
    tmp=$(mktemp -d)
    echo "   downloading $A (~400 MB)"
    curl -# -L -o "$tmp/ndk" "https://dl.google.com/android/ndk/$A" || exit 1
    mkdir -p "$(dirname "$NDK_DIR")"
    "$SZ" x -y -o"$(dirname "$NDK_DIR")" "$tmp/ndk" \
        "android-ndk-r10e/toolchains/aarch64-linux-android-4.9/prebuilt/$HOST/*" \
        "android-ndk-r10e/platforms/android-21/arch-arm64/*" \
        "android-ndk-r10e/sources/cxx-stl/gnu-libstdc++/4.9/*" >/dev/null || exit 1
    rm -rf "$tmp"
fi

echo ">> configure"
$PY tools/configure.py || {
    echo "   get libSrc.so:  py -3 tools/extract.py <3.5.7 apk/zip>   (see INSTALL.md)"
    exit 1
}
echo "   done -- try: make progress"
