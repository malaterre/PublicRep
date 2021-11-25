#include <bitset>
void foo()
{
  while (true) {
      new int[100000000ul];
  }
}

int bla(const char *bit_string)
{
  std::bitset<8> b(bit_string);   
  return b[0];
}
