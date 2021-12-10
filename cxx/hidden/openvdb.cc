#include "Tree.h"

static std::string do_segfault() { return Tree<bool>::treeType(); }

OPENVDB_API void initialize()
{
  do_segfault();
}
