#include <atomic>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <memory>
//#include <iostream>

#define HWY_ALIGNMENT 64
constexpr size_t kAlignment = HWY_ALIGNMENT;
constexpr size_t kAlias = kAlignment * 4;

bool BytesEqual2(const void *p1, const void *p2, const size_t size);

namespace hwy {
namespace N_EMU128 {
template <typename T, size_t N = 16 / sizeof(T)> struct Vec128 {
  T raw[16 / sizeof(T)] = {};
};
} // namespace N_EMU128
} // namespace hwy

template <size_t kBytes, typename From, typename To>
static void CopyBytes2(const From *from, To *to) {
  __builtin_memcpy(to, from, kBytes);
}

template <typename T, size_t N>
static void Store2(const hwy::N_EMU128::Vec128<T, N> v,
                   T *__restrict__ aligned) {
  __builtin_memcpy(aligned, v.raw, sizeof(T) * N);
}

template <typename T, size_t N>
static hwy::N_EMU128::Vec128<T, N> Load2(const T *__restrict__ aligned) {
  hwy::N_EMU128::Vec128<T, N> v;
  __builtin_memcpy(v.raw, aligned, sizeof(T) * N);
  return v;
}

template <size_t N>
static hwy::N_EMU128::Vec128<uint16_t, N>
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

#define HWY_ASSERT(condition) assert((condition))
#define HWY_ASSUME_ALIGNED(ptr, align) __builtin_assume_aligned((ptr), (align))

#pragma pack(push, 1)
struct AllocationHeader {
  void *allocated;
  size_t payload_size;
};
#pragma pack(pop)

static void FreeAlignedBytes2(const void *aligned_pointer) {
  HWY_ASSERT(aligned_pointer != nullptr);
  if (aligned_pointer == nullptr)
    return;

  const uintptr_t payload = reinterpret_cast<uintptr_t>(aligned_pointer);
  HWY_ASSERT(payload % kAlignment == 0);
  const AllocationHeader *header =
      reinterpret_cast<const AllocationHeader *>(payload) - 1;

  free(header->allocated);
}

class AlignedFreer2 {
public:
  template <typename T> void operator()(T *aligned_pointer) const {
    FreeAlignedBytes2(aligned_pointer);
  }
};

template <typename T>
using AlignedFreeUniquePtr2 = std::unique_ptr<T, AlignedFreer2>;

static inline constexpr size_t ShiftCount2(size_t n) {
  return (n <= 1) ? 0 : 1 + ShiftCount2(n / 2);
}

namespace {
static size_t NextAlignedOffset2() {
  static std::atomic<uint32_t> next{0};
  constexpr uint32_t kGroups = kAlias / kAlignment;
  const uint32_t group = next.fetch_add(1, std::memory_order_relaxed) % kGroups;
  const size_t offset = kAlignment * group;
  HWY_ASSERT((offset % kAlignment == 0) && offset <= kAlias);
  //  std::cerr << "O: " << offset << std::endl;
  return offset;
}
} // namespace

static void *AllocateAlignedBytes2(const size_t payload_size) {
  HWY_ASSERT(payload_size != 0); // likely a bug in caller
  if (payload_size >= std::numeric_limits<size_t>::max() / 2) {
    HWY_ASSERT(false && "payload_size too large");
    return nullptr;
  }

  size_t offset = NextAlignedOffset2();

  // What: | misalign | unused | AllocationHeader |payload
  // Size: |<= kAlias | offset                    |payload_size
  //       ^allocated.^aligned.^header............^payload
  // The header must immediately precede payload, which must remain aligned.
  // To avoid wasting space, the header resides at the end of `unused`,
  // which therefore cannot be empty (offset == 0).
  if (offset == 0) {
    offset = kAlignment; // = RoundUpTo(sizeof(AllocationHeader), kAlignment)
    static_assert(sizeof(AllocationHeader) <= kAlignment, "Else: round up");
  }

  const size_t allocated_size = kAlias + offset + payload_size;
  void *allocated;
  allocated = malloc(allocated_size);
  HWY_ASSERT(allocated != nullptr);
  if (allocated == nullptr)
    return nullptr;
  // Always round up even if already aligned - we already asked for kAlias
  // extra bytes and there's no way to give them back.
  uintptr_t aligned = reinterpret_cast<uintptr_t>(allocated) + kAlias;
  static_assert((kAlias & (kAlias - 1)) == 0, "kAlias must be a power of 2");
  static_assert(kAlias >= kAlignment, "Cannot align to more than kAlias");
  aligned &= ~(kAlias - 1);

  const uintptr_t payload = aligned + offset; // still aligned

  // Stash `allocated` and payload_size inside header for FreeAlignedBytes().
  // The allocated_size can be reconstructed from the payload_size.
  AllocationHeader *header = reinterpret_cast<AllocationHeader *>(payload) - 1;
  header->allocated = allocated;
  header->payload_size = payload_size;

  return HWY_ASSUME_ALIGNED(reinterpret_cast<void *>(payload), kAlignment);
}

template <typename T> static T *AllocateAlignedItems2(size_t items) {
  constexpr size_t size = sizeof(T);

  constexpr bool is_pow2 = (size & (size - 1)) == 0;
  constexpr size_t bits = ShiftCount2(size);
  static_assert(!is_pow2 || (1ull << bits) == size, "ShiftCount is incorrect");

  const size_t bytes = is_pow2 ? items << bits : items * size;
  const size_t check = is_pow2 ? bytes >> bits : bytes / size;
  if (check != items) {
    return nullptr; // overflowed
  }
  return static_cast<T *>(AllocateAlignedBytes2(bytes));
}

template <typename T>
static AlignedFreeUniquePtr2<T[]> AllocateAligned2(const size_t items) {
  return AlignedFreeUniquePtr2<T[]>(AllocateAlignedItems2<T>(items),
                                    AlignedFreer2());
}

int main() {
  AlignedFreeUniquePtr2<uint16_t[]> in_lanes = AllocateAligned2<uint16_t>(2);
  uint16_t expected_lanes[2];
  in_lanes[0] = 65535;
  in_lanes[1] = 32767;
  expected_lanes[0] = 65534;
  expected_lanes[1] = 16383;
  hwy::N_EMU128::Vec128<uint16_t, 2> v = Load2<uint16_t, 2>(in_lanes.get());
  hwy::N_EMU128::Vec128<uint16_t, 2> actual = MulHigh(v, v);
  {
    auto actual_lanes = AllocateAligned2<uint16_t>(2);
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
