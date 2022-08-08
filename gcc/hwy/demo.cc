#include "hwy/aligned_allocator.h"
#include "hwy/highway.h"

#include <cstring>

bool BytesEqual2(const void * __restrict__ p1, const void * __restrict__ p2, const size_t size);

template< typename T >
bool is_aligned(T* p){
    return !(reinterpret_cast<uintptr_t>(p) % std::alignment_of<T>::value);
}

template <class D, class V>
void AssertVecEqual2(D d, const uint16_t *expected, const V &actual) {
  auto actual_lanes = hwy::AllocateAligned<uint16_t>(2);
  uint16_t *ptr = actual_lanes.get();
  HWY_ASSERT(is_aligned(ptr));
  Store(actual, d, actual_lanes.get());
  const uint8_t *expected_array = reinterpret_cast<const uint8_t *>(expected);
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

int main() {
  hwy::N_EMU128::FixedTag<uint16_t, 2> d;
  hwy::AlignedFreeUniquePtr<uint16_t[]> in_lanes =
      hwy::AllocateAligned<uint16_t>(2);
  uint16_t *ptr = in_lanes.get();
  HWY_ASSERT(is_aligned(ptr));
  uint16_t expected_lanes[2];
  in_lanes[0] = 65535;
  in_lanes[1] = 32767;
  expected_lanes[0] = 65534;
  expected_lanes[1] = 16383;
  hwy::N_EMU128::Vec128<uint16_t, 2> v = Load(d, in_lanes.get());
  hwy::N_EMU128::Vec128<uint16_t, 2> actual = MulHigh(v, v);
  AssertVecEqual2(d, expected_lanes, actual);
}
