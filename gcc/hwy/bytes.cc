#include <cstddef>
#include <cstdint>

namespace hwy {
bool BytesEqual2(const void* p1, const void* p2,
                                   const size_t size, size_t* pos ) {
  const uint8_t* bytes1 = reinterpret_cast<const uint8_t*>(p1);
  const uint8_t* bytes2 = reinterpret_cast<const uint8_t*>(p2);
  for (size_t i = 0; i < size; ++i) {
    if (bytes1[i] != bytes2[i]) {
      if (pos != nullptr) {
        *pos = i;
      }
      return false;
    }
  }
  return true;
}
}
