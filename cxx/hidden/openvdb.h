// Copyright Contributors to the OpenVDB Project
// SPDX-License-Identifier: MPL-2.0

#ifndef OPENVDB_OPENVDB_HAS_BEEN_INCLUDED
#define OPENVDB_OPENVDB_HAS_BEEN_INCLUDED

#include "Platform.h"
#include "MyTree.h"

namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {

/// Common tree types
using BoolTree     = tree::Tree4<bool,        5, 4, 3>::Type;

/// Global registration of basic types
OPENVDB_API void initialize();


} // namespace OPENVDB_VERSION_NAME
} // namespace openvdb

#endif // OPENVDB_OPENVDB_HAS_BEEN_INCLUDED
