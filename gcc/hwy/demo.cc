#include "hwy/highway.h"
#include "hwy/tests/test_util-inl.h"


struct TestMulHigh {
  template <typename T, class D>
  void operator()(T /*unused*/, D d) {
    const size_t N = 2;
    hwy::AlignedFreeUniquePtr<short unsigned int []> in_lanes = hwy::AllocateAligned<T>(N);
    uint16_t expected_lanes[2];

    for (size_t i = 0; i < N; ++i) {
      in_lanes[i] = T(hwy::LimitsMax<T>() >> i);
    }
    expected_lanes[0] = 65534 ;
    expected_lanes[1] = 16383 ;
    hwy::N_EMU128::Vec128<uint16_t, 2> v = Load(d, in_lanes.get());
    HWY_ASSERT_VEC_EQ(d, in_lanes.get(), v);
    hwy::N_EMU128::Vec128<uint16_t, 2> actual = MulHigh(v, v);

    HWY_ASSERT_VEC_EQ(d, expected_lanes, actual);
  }
};

int main()
{
  TestMulHigh()(uint16_t(), hwy::N_EMU128::FixedTag<uint16_t, 2>());
}
