#include "Tree.h"

static std::string do_segfault() { return Tree::treeType(); }

OPENVDB_API void initialize()
{
  do_segfault();
}
