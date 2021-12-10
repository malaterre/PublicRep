// Copyright Contributors to the OpenVDB Project
// SPDX-License-Identifier: MPL-2.0

#include "openvdb.h"

namespace openvdb {

 static std::string gridType2() { return BoolTree::treeType(); }

void
initialize()
{
//    BoolGrid::registerGrid();
 gridType2();
}


} // namespace openvdb
