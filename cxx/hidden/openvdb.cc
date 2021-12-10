#include "Tree.h"

static std::string do_segfault() { return Tree::treeType(); }

 __attribute__((visibility("default")))
void initialize()
{
  do_segfault();
}
