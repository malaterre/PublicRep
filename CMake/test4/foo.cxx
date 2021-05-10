#include <vector>

extern "C" {
bool bla(char *data, size_t size);
}

int main() {
  std::vector<char> v;
  v.resize(9);
  v.resize(10);
  bla(&v[0], v.size());
  return 0;
}
