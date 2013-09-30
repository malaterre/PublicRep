#include "virt.h"

#include <iostream>

void base::foo()
{
  std::cout << "base::foo" << std::endl;
}
void concrete::foo()
{
  std::cout << "concrete::foo" << std::endl;
}

base * create_concrete()
{
  return new concrete;
}
