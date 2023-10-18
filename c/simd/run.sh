#!/bin/sh -e
set -x
#gcc -std=c11 -O3 -march=x86-64-v3 -mtune=znver1 -fverbose-asm -S -c simd.c && cat simd.s
WFLAGS='-Wall -Wextra -Wpedantic'
gcc -std=c11 $WFLAGS -O3 -msse4.2 -fverbose-asm -S -c -o simd_see42.s simd.c && cat simd_see42.s
gcc -std=c11 $WFLAGS -O3 -mavx2 -fverbose-asm -S -c -o simd_avx2.s simd.c && cat simd_avx2.s
gcc -fopt-info-vec-all -std=c11 $WFLAGS -O3 -march=x86-64-v3 -mtune=znver1 -fverbose-asm -S  -c generic.c

gcc -DHASMATCH=hasmatch_avx2 -std=c11 $WFLAGS -O3 -msse4.2 -c -o simd_see42.o simd.c
gcc -DHASMATCH=hasmatch_sse42 -std=c11 $WFLAGS -O3 -mavx2 -c -o simd_avx2.o simd.c
gcc -DHASMATCH=hasmatch_generic -std=c11 $WFLAGS -O3 -c -o generic.o generic.c

gcc $WFLAGS -O0 -g -o main main.c simd_see42.o simd_avx2.o generic.o
