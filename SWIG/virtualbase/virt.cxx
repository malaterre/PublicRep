#include "virt.h"

#include <iostream>

base * base::create_concrete()
{
  return new concrete;
}

void concrete::foo()
{
  std::cout << "foo" << std::endl;
}
