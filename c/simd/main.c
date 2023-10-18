#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
int hasmatch_sse42(uint16_t needle, const uint16_t haystack[4]);
int hasmatch_avx2(uint16_t needle, const uint16_t haystack[4]);
int hasmatch_generic(uint16_t needle, const uint16_t haystack[4]);

typedef int (*hasmatch)(uint16_t needle, const uint16_t haystack[4]);

#include <sys/time.h>
void bench(hasmatch fn, const uint16_t *haystacks, size_t num) {
  struct timeval tv1, tv2;
  gettimeofday(&tv1, NULL);
  for (size_t n = 0; n < num; ++n) {
    const uint16_t *haystack = haystacks + 4 * n;
    for (uint32_t val = 0; val <= 0xffff; ++val) {
      (void)fn(val, haystack);
    }
  }
  /* stuff to do! */
  gettimeofday(&tv2, NULL);

  printf("Total time = %f seconds\n",
         (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 +
             (double)(tv2.tv_sec - tv1.tv_sec));
}

int main() {
  static const uint16_t haystack[] = {0x1234, 0x5432, 0x9090, 0xFEED};
  // uint16_t haystack[4] = {0x1234, 0x5432, 0x9090, 0xFEED};
  // for (int i = 0; i < 4; ++i) {
  //   haystack[i] = rand();
  // }
  // for (int i = 0; i < 4; ++i) {
  //   if (hasmatch_generic(haystack[i], haystack) != 1)
  //     abort();
  //   if (hasmatch_sse42(haystack[i], haystack) != 1)
  //     abort();
  //   if (hasmatch_avx2(haystack[i], haystack) != 1)
  //     abort();
  // }
  for (uint32_t val = 0; val <= 0xffff; ++val) {
    const int ret1 = hasmatch_generic(val, haystack);
    //    const int ret11 = hasmatch_generic(0x0, haystack) ;
    const int ret2 = hasmatch_sse42(val, haystack);
    //    const int ret22 = hasmatch_sse42(0x0, haystack) ;
    const int ret3 = hasmatch_avx2(val, haystack);
    //    const int ret33 = hasmatch_avx2(0x0, haystack) ;
    if (ret1 != ret2 || ret2 != ret3)
      abort();
  }
  //  printf("generic: %d %d\n", hasmatch_generic(0x0, haystack),
  //         hasmatch_generic(0xFEED, haystack));
  //  printf("sse42: %d %d\n", hasmatch_sse42(0x0, haystack),
  //         hasmatch_sse42(0xFEED, haystack));
  //  printf("avx2: %d %d\n", hasmatch_avx2(0x0, haystack),
  //         hasmatch_avx2(0xFEED, haystack));
  const size_t N = 100;
  uint16_t *haystacks = aligned_alloc(2, 4 * N * 2);
  for (size_t i = 0; i < 4 * N; ++i) {
    haystacks[i] = rand();
  }

  printf("generic\n");
  bench(hasmatch_generic, haystacks, N);
  printf("sse42\n");
  bench(hasmatch_sse42, haystacks, N);
  printf("avx2\n");
  bench(hasmatch_avx2, haystacks, N);
  return 0;
}
