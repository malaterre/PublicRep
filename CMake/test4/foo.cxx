#include <cstring>
#include <string>
#include <vector>

int main() {
  std::vector<char> v;
#ifdef RESIZE9
  v.resize(9);
#endif
  v.resize(10);

  std::string s(10, 'x');
  std::strcpy(&v[0], s.c_str());

  return 0;
}
