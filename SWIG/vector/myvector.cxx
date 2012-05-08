#include "myvector.h"

my_vector::SizeType my_vector::Count() const
{
  return I.size();
}

std::vector<int> const &my_vector::GetI() const
{
  return I;
}

