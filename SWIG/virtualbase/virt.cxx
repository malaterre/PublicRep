#include "virt.h"

base * base::create_concrete()
{
  return new concrete;
}

void concrete::foo()
{
}
