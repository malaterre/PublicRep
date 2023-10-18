#include <stdint.h>
#include <stdio.h>
int hasmatch_sse42(uint16_t needle, const uint16_t haystack[4]);
int hasmatch_avx2(uint16_t needle, const uint16_t haystack[4]);
int hasmatch_generic(uint16_t needle, const uint16_t haystack[4]);

int main() {
  static const uint16_t haystack[] = {0x1234, 0x5432, 0x9090, 0xFEED};
  printf("generic: %d %d\n", hasmatch_generic(0x0, haystack),
         hasmatch_generic(0xFEED, haystack));
  printf("sse42: %d %d\n", hasmatch_sse42(0x0, haystack),
         hasmatch_sse42(0xFEED, haystack));
  printf("avx2: %d %d\n", hasmatch_avx2(0x0, haystack),
         hasmatch_avx2(0xFEED, haystack));
}
