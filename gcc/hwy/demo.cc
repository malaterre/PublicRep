#include "hwy/aligned_allocator.h"
#include "hwy/highway.h"
#include "hwy/print.h"

namespace hwy {

namespace detail {
//HWY_TEST_DLLEXPORT HWY_NORETURN void PrintMismatchAndAbort(
//    const TypeInfo& info, const void* expected_ptr, const void* actual_ptr,
//    const char* target_name, const char* filename, int line, size_t lane,
//    size_t num_lanes) ;

HWY_TEST_DLLEXPORT bool IsEqual(const TypeInfo& info, const void* expected_ptr,
                                const void* actual_ptr);

void AssertArrayEqual2(const TypeInfo &info, const void *expected_void,
                      const void *actual_void, size_t N,
                      const char *target_name, const char *filename, int line) {
  const uint8_t* expected_array =
      reinterpret_cast<const uint8_t*>(expected_void);
  const uint8_t* actual_array = reinterpret_cast<const uint8_t*>(actual_void);
  for (size_t i = 0; i < N; ++i) {
    const void* expected_ptr = expected_array + i * info.sizeof_t;
    const void* actual_ptr = actual_array + i * info.sizeof_t;
    if (!IsEqual(info, expected_ptr, actual_ptr)) {
//      fprintf(stderr, "\n\n");
//      PrintArray(info, "expect", expected_array, N, i);
//      PrintArray(info, "actual", actual_array, N, i);

abort();
//      PrintMismatchAndAbort(info, expected_ptr, actual_ptr, target_name,
//                            filename, line, i, N);
    }
  }

}
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
  hwy::detail::AssertArrayEqual2(info, expected, actual_lanes.get(), N,
                                target_name, filename, line);
}
} // namespace N_EMU128
} // namespace hwy

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
  hwy::N_EMU128::AssertVecEqual(d, expected_lanes, actual, __FILE__, __LINE__);
}
