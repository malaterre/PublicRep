#include "virt.h"

int main()
{
  base * b = create_concrete();
  b->foo();
  return 0;
}
