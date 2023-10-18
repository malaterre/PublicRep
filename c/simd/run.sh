#!/bin/sh -e
set -x
gcc -std=c11 -O3 -march=x86-64-v3 -mtune=znver1 -fverbose-asm -S -c simd.c && cat simd.s
