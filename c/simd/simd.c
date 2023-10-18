#include <immintrin.h>
#include <stdint.h>

// note the unsigned function arg, not uint16_t;
// we only use the low 16, but GCC doesn't realize that and wastes an
// instruction in the non-AVX2 version
int HASMATCH(uint16_t needle, const uint16_t haystack[4]) {
#ifdef __AVX2__ // or higher
  __m128i vneedle = _mm_set1_epi16(needle);
#else
  __m128i vneedle = _mm_cvtsi32_si128(needle); // movd
  vneedle = _mm_shufflelo_epi16(vneedle, 0);   // broadcast to low half
#endif

  __m128i vbuf =
      _mm_loadl_epi64((void *)haystack); // alignment and aliasing safe
  unsigned mask = _mm_movemask_epi8(_mm_cmpeq_epi16(vneedle, vbuf));
  // return _tzcnt_u32(mask) >> 1;
  return mask & 0x00ff ? 1 : 0;
}
