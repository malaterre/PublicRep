#include <cstring>

bool BytesEqual(const void *bytes1, const void *bytes2, const size_t size) {
  return memcmp(bytes1, bytes2, size) == 0;
}
