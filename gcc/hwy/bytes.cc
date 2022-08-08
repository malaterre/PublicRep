#include <cstddef>
#include <cstdint>

bool BytesEqual2(const uint8_t *bytes1, const uint8_t *bytes2,
                 const size_t size, size_t *pos) {
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
