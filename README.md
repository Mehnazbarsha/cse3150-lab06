# BigInts and Timing Lab

## Overview

This lab implements fraction arithmetic (product and sum) using three numeric types —
`int`, `long long`, and `bigint` — stored as `std::pair<T,T>` where `.first` is the
numerator and `.second` is the denominator.  It then benchmarks the time cost of each
type and demonstrates where `int`-based fractions silently produce wrong results due to
overflow.

## Files

| File | Purpose |
|---|---|
| `bigint.h` | Single-file big-integer library (compatible with rgroshanrg/bigint API) |
| `fractions.h` | `product()` and `sum()` overloads for `IntFrac`, `LLFrac`, `BigFrac` |
| `main.cpp` | Timing benchmark + overflow demonstration |
| `unit_tests.cpp` | 17 self-contained unit tests (run automatically on `make test`) |
| `Makefile` | Build system |

## Build & Run

```bash
# Compile everything
make

# Run unit tests (exits 0 on all pass, 1 on any failure)
make test

# Run timing benchmark and overflow demo
make run
```

Requires g++ with C++20 support (`-std=c++20`).

### Product formula

```
(a/b) * (c/d)  =  (a*c) / (b*d)   then GCD-reduced
```

### Sum formula

```
(a/b) + (c/d)  =  (a*d + c*b) / (b*d)   then GCD-reduced
```
