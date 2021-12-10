#ifndef OPENVDB_OPENVDB_HAS_BEEN_INCLUDED
#define OPENVDB_OPENVDB_HAS_BEEN_INCLUDED

#include "Platform.h"
#include "Grid.h"
#include "Tree.h"

namespace openvdb {

using BoolTree     = tree::Tree4<bool,        5, 4, 3>::Type;
using BoolGrid     = Grid<BoolTree>;
OPENVDB_API void initialize();

} // namespace openvdb

#endif // OPENVDB_OPENVDB_HAS_BEEN_INCLUDED
