#include "Tree.h"

static std::string do_segfault() { return Tree::treeType(); }

#ifdef VIS
__attribute__((visibility("default")))
#endif
void initialize()
{
  do_segfault();
}
