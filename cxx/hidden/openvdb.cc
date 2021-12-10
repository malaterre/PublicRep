// Copyright Contributors to the OpenVDB Project
// SPDX-License-Identifier: MPL-2.0

#include "openvdb.h"

namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {

 static std::string gridType2() { return BoolTree::treeType(); }

void
initialize()
{
//    BoolGrid::registerGrid();
 gridType2();
}


} // namespace OPENVDB_VERSION_NAME
} // namespace openvdb
