#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
int hasmatch_sse42(uint16_t needle, const uint16_t haystack[4]);
int hasmatch_avx2(uint16_t needle, const uint16_t haystack[4]);
int hasmatch_generic(uint16_t needle, const uint16_t haystack[4]);

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
}
