#include "virt.h"

int main()
{
  base * b = base::create_concrete();
  b->foo();
  return 0;
}
