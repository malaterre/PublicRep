// Copyright Contributors to the OpenVDB Project
// SPDX-License-Identifier: MPL-2.0

#include "openvdb.h"

namespace openvdb {

static std::string do_segfault() { return BoolTree::treeType(); }

void
initialize()
{
  do_segfault();
}


} // namespace openvdb
