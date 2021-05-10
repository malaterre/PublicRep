#include <cstring>
#include <string>

extern "C" {
__attribute__((visibility("default"))) bool bla(char *buf, size_t len) {
  std::string s(10, 'x');
  std::strcpy(buf, s.c_str());
  return true;
}
}
