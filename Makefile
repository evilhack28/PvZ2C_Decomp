# See README.md Windows: `scoop install make`, or run
# tools/*.py directly.

PYTHON ?= $(shell command -v py >/dev/null 2>&1 && echo "py -3" || echo python3)
JOBS   ?= $(shell nproc 2>/dev/null || echo 4)
FUNC   ?=
PLANT  ?=

APK ?=

.PHONY: all setup extract configure report check progress diff first-diff plant scaffold format clean help

all: check                    ## compile everything and verify nothing regressed

setup:                        ## install Python deps, the NDK, and the reference lib
	./installDependencies.sh

extract:                      ## pull libSrc.so from the APK:  make extract APK=<path-or-url>
	@test -n "$(APK)" || { echo "usage: make extract APK=<3.5.7 apk or zip>"; exit 2; }
	$(PYTHON) tools/extract.py $(APK)

configure:                    ## (re)detect the NDK and libSrc.so on this machine
	$(PYTHON) tools/configure.py

report:                       ## refresh the report.json progress baseline
	$(PYTHON) tools/progress.py --report report.json

check:                        ## compile all of src/ and fail on any regression vs report.json
	$(PYTHON) tools/progress.py --cache --check report.json --jobs $(JOBS)

progress:                     ## full progress table (add `PLANT=Iceburg` to filter)
	$(PYTHON) tools/progress.py --jobs $(JOBS) $(PLANT)

diff:                         ## game-vs-ours listing:  make diff FUNC=<mangled>
	@test -n "$(FUNC)" || { echo "usage: make diff FUNC=<mangled symbol>"; exit 2; }
	$(PYTHON) diff.py $(FUNC)

first-diff:                   ## largest not-yet-matching functions (PLANT= to filter)
	$(PYTHON) first_diff.py $(PLANT)

plant:                        ## one plant's methods:  make plant PLANT=Iceburg
	@test -n "$(PLANT)" || { echo "usage: make plant PLANT=<Name>"; exit 2; }
	$(PYTHON) tools/plant.py $(PLANT) --todo

scaffold:                     ## regenerate the src/ stubs + units.json
	$(PYTHON) tools/scaffold.py

format:                       ## clang-format every source file in place
	@command -v clang-format >/dev/null || { echo "clang-format not found"; exit 2; }
	find src -name '*.cpp' -o -name '*.h' | xargs clang-format -i

clean:                        ## remove build artifacts (report.json is kept)
	rm -rf build

help:
	@grep -hE '^[a-z-]+:.*?## ' $(MAKEFILE_LIST) | sort | \
	  awk 'BEGIN{FS=":.*?## "}{printf "  \033[36m%-12s\033[0m %s\n", $$1, $$2}'
