#include "virt.h"

#include <iostream>

void Ko::threats() {}

base * base::create_concrete(bool b)
{
  if( b )
    return new concrete;
  return NULL;
}

void concrete::foo()
{
  std::cout << "foo" << std::endl;
}

base * create_concrete_for_swig()
{
  return base::create_concrete();
}
