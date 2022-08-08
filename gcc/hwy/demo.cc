#include "hwy/aligned_allocator.h"
//#include "hwy/highway.h"
#include <cstdlib>
#include <cstring>

bool BytesEqual2(const void *p1, const void *p2, const size_t size);

namespace hwy {
namespace N_EMU128 {
template <typename T, size_t N = 16 / sizeof(T)> struct Vec128 {
  Vec128() = default;
  Vec128(const Vec128 &) = default;
  Vec128 &operator=(const Vec128 &) = default;

  Vec128 &operator*=(const Vec128 other) { return *this = (*this * other); }
  Vec128 &operator/=(const Vec128 other) { return *this = (*this / other); }
  Vec128 &operator+=(const Vec128 other) { return *this = (*this + other); }
  Vec128 &operator-=(const Vec128 other) { return *this = (*this - other); }
  Vec128 &operator&=(const Vec128 other) { return *this = (*this & other); }
  Vec128 &operator|=(const Vec128 other) { return *this = (*this | other); }
  Vec128 &operator^=(const Vec128 other) { return *this = (*this ^ other); }

  // Behave like wasm128 (vectors can always hold 128 bits). generic_ops-inl.h
  // relies on this for LoadInterleaved*. CAVEAT: this method of padding
  // prevents using range for, especially in SumOfLanes, where it would be
  // incorrect. Moving padding to another field would require handling the case
  // where N = 16 / sizeof(T) (i.e. there is no padding), which is also awkward.
  T raw[16 / sizeof(T)] = {};
};
} // namespace N_EMU128
} // namespace hwy

template <size_t kBytes, typename From, typename To>
void CopyBytes2(const From *from, To *to) {
  __builtin_memcpy(to, from, kBytes);
}

template <typename T, size_t N>
void Store2(const hwy::N_EMU128::Vec128<T, N> v, T *__restrict__ aligned) {
  CopyBytes2<sizeof(T) * N>(v.raw, aligned);
}

template <typename T, size_t N>
hwy::N_EMU128::Vec128<T, N> Load2(const T *__restrict__ aligned) {
  hwy::N_EMU128::Vec128<T, N> v;
  CopyBytes2<sizeof(T) * N>(aligned, v.raw);
  return v;
}

template <size_t N>
hwy::N_EMU128::Vec128<uint16_t, N>
MulHigh(hwy::N_EMU128::Vec128<uint16_t, N> a,
        const hwy::N_EMU128::Vec128<uint16_t, N> b) {
  for (size_t i = 0; i < N; ++i) {
    // Cast to uint32_t first to prevent overflow. Otherwise the result of
    // uint16_t * uint16_t is in "int" which may overflow. In practice the
    // result is the same but this way it is also defined.
    a.raw[i] = static_cast<uint16_t>(
        (static_cast<uint32_t>(a.raw[i]) * static_cast<uint32_t>(b.raw[i])) >>
        16);
  }
  return a;
}

int main() {
  hwy::AlignedFreeUniquePtr<uint16_t[]> in_lanes =
      hwy::AllocateAligned<uint16_t>(2);
  uint16_t *ptr = in_lanes.get();
  uint16_t expected_lanes[2];
  in_lanes[0] = 65535;
  in_lanes[1] = 32767;
  expected_lanes[0] = 65534;
  expected_lanes[1] = 16383;
  hwy::N_EMU128::Vec128<uint16_t, 2> v = Load2<uint16_t, 2>(in_lanes.get());
  hwy::N_EMU128::Vec128<uint16_t, 2> actual = MulHigh(v, v);
  {
    auto actual_lanes = hwy::AllocateAligned<uint16_t>(2);
    uint16_t *ptr = actual_lanes.get();
    Store2(actual, actual_lanes.get());
    const uint8_t *expected_array =
        reinterpret_cast<const uint8_t *>(expected_lanes);
    const uint8_t *actual_array =
        reinterpret_cast<const uint8_t *>(actual_lanes.get());
    for (size_t i = 0; i < 2; ++i) {
      const uint8_t *expected_ptr = expected_array + i * 2;
      const uint8_t *actual_ptr = actual_array + i * 2;
#if 1
      // trigger bug
      if (!BytesEqual2(expected_ptr, actual_ptr, 2)) {
#else
      // no bug
      if (std::memcmp(expected_ptr, actual_ptr, 2) != 0) {
#endif
        abort();
      }
    }
  }
}
