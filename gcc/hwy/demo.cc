#include "hwy/aligned_allocator.h"
#include <cstdlib>
#include <cstring>

bool BytesEqual2(const void *p1, const void *p2, const size_t size);

namespace hwy {
namespace N_EMU128 {
template <typename T, size_t N = 16 / sizeof(T)> struct Vec128 {
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

using AllocPtr2 = void *(*)(void *opaque, size_t bytes);
using FreePtr2 = void (*)(void *opaque, void *memory);

class AlignedFreer2 {
public:
  // Pass address of this to ctor to skip deleting externally-owned memory.
  static void DoNothing(void * /*opaque*/, void * /*aligned_pointer*/) {}

  AlignedFreer2() : free_(nullptr), opaque_ptr_(nullptr) {}
  AlignedFreer2(FreePtr2 free_ptr, void *opaque_ptr)
      : free_(free_ptr), opaque_ptr_(opaque_ptr) {}

  template <typename T> void operator()(T *aligned_pointer) const {
    hwy::FreeAlignedBytes(aligned_pointer, free_, opaque_ptr_);
  }

private:
  FreePtr2 free_;
  void *opaque_ptr_;
};

template <typename T>
using AlignedFreeUniquePtr2 = std::unique_ptr<T, AlignedFreer2>;

template <typename T>
AlignedFreeUniquePtr2<T[]> AllocateAligned2(const size_t items, AllocPtr2 alloc,
                                            FreePtr2 free, void *opaque) {
  return AlignedFreeUniquePtr2<T[]>(
      hwy::detail::AllocateAlignedItems<T>(items, alloc, opaque),
      AlignedFreer2(free, opaque));
}

template <typename T>
AlignedFreeUniquePtr2<T[]> AllocateAligned2(const size_t items) {
  return AllocateAligned2<T>(items, nullptr, nullptr, nullptr);
}

int main() {
  AlignedFreeUniquePtr2<uint16_t[]> in_lanes = AllocateAligned2<uint16_t>(2);
  uint16_t *ptr = in_lanes.get();
  uint16_t expected_lanes[2];
  in_lanes[0] = 65535;
  in_lanes[1] = 32767;
  expected_lanes[0] = 65534;
  expected_lanes[1] = 16383;
  hwy::N_EMU128::Vec128<uint16_t, 2> v = Load2<uint16_t, 2>(in_lanes.get());
  hwy::N_EMU128::Vec128<uint16_t, 2> actual = MulHigh(v, v);
  {
    auto actual_lanes = AllocateAligned2<uint16_t>(2);
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
