#include "hwy/aligned_allocator.h"
#include "hwy/highway.h"
#include "hwy/print.h"
//#include "hwy/tests/test_util-inl.h"
//#include <cstring>
//#include <cassert>

namespace hwy {


namespace detail {

void AssertArrayEqual(const TypeInfo &info,
                                         const void *expected_void,
                                         const void *actual_void, size_t N,
                                         const char *target_name,
                                         const char *filename, int line);
}


namespace N_EMU128 {

template <class D, typename T = TFromD<D>, class V = Vec<D>>
HWY_INLINE void AssertVecEqual(D d, const T *expected, VecArg<V> actual,
                               const char *filename, const int line) {
  const size_t N = Lanes(d);
  auto actual_lanes = hwy::AllocateAligned<T>(N);
  Store(actual, d, actual_lanes.get());

  const auto info = hwy::detail::MakeTypeInfo<T>();
  const char *target_name = hwy::TargetName(HWY_TARGET);
#if 1
  hwy::detail::AssertArrayEqual(info, expected, actual_lanes.get(), N,
                                target_name, filename, line);
#else
  assert(memcmp(expected, actual_lanes.get(), N * 2) == 0);
#endif
}
} // namespace N_EMU128
} // namespace hwy

struct TestMulHigh {
  template <typename T, class D> void operator()(T /*unused*/, D d) {
    const size_t N = 2;
    hwy::AlignedFreeUniquePtr<short unsigned int[]> in_lanes =
        hwy::AllocateAligned<T>(N);
    uint16_t expected_lanes[2];

    for (size_t i = 0; i < N; ++i) {
      in_lanes[i] = T(hwy::LimitsMax<T>() >> i);
    }
    expected_lanes[0] = 65534;
    expected_lanes[1] = 16383;
    hwy::N_EMU128::Vec128<uint16_t, 2> v = Load(d, in_lanes.get());
    //    HWY_ASSERT_VEC_EQ(d, in_lanes.get(), v);
    hwy::N_EMU128::Vec128<uint16_t, 2> actual = MulHigh(v, v);

    //    HWY_ASSERT_VEC_EQ(d, expected_lanes, actual);
    hwy::N_EMU128::AssertVecEqual(d, expected_lanes, actual, __FILE__,
                                  __LINE__);
  }
};

int main() {
  TestMulHigh()(uint16_t(), hwy::N_EMU128::FixedTag<uint16_t, 2>());
}
