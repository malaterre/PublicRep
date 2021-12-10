// Copyright Contributors to the OpenVDB Project
// SPDX-License-Identifier: MPL-2.0

#ifndef OPENVDB_OPENVDB_HAS_BEEN_INCLUDED
#define OPENVDB_OPENVDB_HAS_BEEN_INCLUDED

#include "Platform.h"
#include "Grid.h"
#include "Tree.h"

namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {

using BoolTree     = tree::Tree4<bool,        5, 4, 3>::Type;
using BoolGrid     = Grid<BoolTree>;
OPENVDB_API void initialize();

} // namespace OPENVDB_VERSION_NAME
} // namespace openvdb

#endif // OPENVDB_OPENVDB_HAS_BEEN_INCLUDED
