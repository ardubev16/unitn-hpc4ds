# Requires mpicc/mpirun in PATH (see .envrc).
# Usage:
#   make run EX=l7p19 [NP=4] [ARGS="..."]   compile and run exercises/$(EX)/
#   make build EX=l7p19                     compile only
#   make clean
#   Stdin passes through:  echo hello | make run EX=l7p19

NP       ?= 4
CFLAGS   ?= -Wall -Wextra -pedantic -O2
LDLIBS   ?= -lm
BUILDDIR := build

.PHONY: run build clean check-ex

ifdef EX
SRC := $(wildcard exercises/$(EX)/*.c)
BIN := $(BUILDDIR)/$(EX)
endif

check-ex:
	@test -n "$(EX)" || { echo "usage: make run EX=<id> [NP=n]  (e.g. EX=l7p19)"; exit 2; }
	@test -n "$(SRC)" || { echo "no C sources in exercises/$(EX)/"; exit 2; }

build: check-ex
	@mkdir -p $(BUILDDIR)
	mpicc $(CFLAGS) -o $(BIN) $(SRC) $(LDLIBS)

run: build
	mpirun --oversubscribe -n $(NP) $(BIN) $(ARGS)

clean:
	rm -rf $(BUILDDIR)
