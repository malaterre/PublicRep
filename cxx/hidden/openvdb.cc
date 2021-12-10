#include "openvdb.h"

namespace openvdb {

static std::string do_segfault() { return Tree<bool>::treeType(); }

void initialize()
{
  do_segfault();
}

} // namespace openvdb
