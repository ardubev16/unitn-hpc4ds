---
name: check-exercise
description: Use when the user asks to check/review/verify an exercise by id (e.g. "l7p19") in this HPC4DS repo. Reads exercises/<id>/, builds and runs it via the Makefile, and reports errors.
---

# Check an exercise

Input: exercise id like `l7p19`. Source lives in `exercises/<id>/`. MPI is assumed to be loaded in the environment.

## Steps

1. **Read** every file in `exercises/<id>/`. The leading comment in `main.c` is the spec; if missing or ambiguous, say so.
2. **Build and run** with the Makefile (warnings show on build):
   ```
   make run EX=<id> NP=<n>
   ```
   Try NP = 1, 2, 4 and an odd value (3 or 5). Pipe stdin for realistic input, then edge input: `</dev/null`, no trailing newline, over-long line. Add `ARGS="..."` for program arguments.
3. **Review** against the spec and common MPI faults:
   - Deadlock: Send/Recv ordering, mismatched tag/source/count/type, collectives not called by all ranks.
   - Buffers: size vs count, missing `+1` for NUL, uninitialized data printed/sent, unchecked `fgets`/`scanf`.
   - Only rank 0 reads stdin.
   - Edge cases: `comm_sz == 1`, first/last rank, ring wraparound.
   - Missing `MPI_Finalize`, MPI calls before `MPI_Init`, compiler warnings.
   - Nondeterministic per-rank print order is expected; flag only if the spec requires order.
4. **Report** each finding with severity, line, evidence (warning or observed output) and a fix. State what was run and what passed. Don't modify the exercise unless asked. Run `make clean` afterwards.
