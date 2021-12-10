#ifndef OPENVDB_OPENVDB_HAS_BEEN_INCLUDED
#define OPENVDB_OPENVDB_HAS_BEEN_INCLUDED

#include "Platform.h"
#include "Tree.h"

namespace openvdb {

using BoolTree     = Tree<bool>;
OPENVDB_API void initialize();

} // namespace openvdb

#endif // OPENVDB_OPENVDB_HAS_BEEN_INCLUDED
