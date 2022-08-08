#include "hwy/aligned_allocator.h"
#include "hwy/highway.h"

bool BytesEqual2(const uint8_t *p1, const uint8_t *p2, const size_t size,
                 size_t *pos = nullptr);

template <class D, class V>
void AssertVecEqual2(D d, const uint16_t *expected, const V &actual) {
  const size_t N = 2;
  auto actual_lanes = hwy::AllocateAligned<uint16_t>(N);
  Store(actual, d, actual_lanes.get());
  const uint8_t *expected_array = reinterpret_cast<const uint8_t *>(expected);
  const uint8_t *actual_array =
      reinterpret_cast<const uint8_t *>(actual_lanes.get());
  for (size_t i = 0; i < N; ++i) {
    const uint8_t *expected_ptr = expected_array + i * 2;
    const uint8_t *actual_ptr = actual_array + i * 2;
    if (!BytesEqual2(expected_ptr, actual_ptr, 2)) {
      abort();
    }
  }
}

int main() {
  hwy::N_EMU128::FixedTag<uint16_t, 2> d;
  const size_t N = 2;
  hwy::AlignedFreeUniquePtr<uint16_t[]> in_lanes =
      hwy::AllocateAligned<uint16_t>(N);
  uint16_t expected_lanes[2];
  in_lanes[0] = 65535;
  in_lanes[1] = 32767;
  expected_lanes[0] = 65534;
  expected_lanes[1] = 16383;
  hwy::N_EMU128::Vec128<uint16_t, 2> v = Load(d, in_lanes.get());
  hwy::N_EMU128::Vec128<uint16_t, 2> actual = MulHigh(v, v);
  AssertVecEqual2(d, expected_lanes, actual);
}
