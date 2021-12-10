// Copyright Contributors to the OpenVDB Project
// SPDX-License-Identifier: MPL-2.0

#include "RenderModules.h"

//#include <openvdb/points/PointDataGrid.h>
//#include <openvdb/points/PointCount.h>
//#include <openvdb/points/PointConversion.h>
//#include <openvdb/tools/Morphology.h>
//#include <openvdb/tools/Prune.h>
//#include <openvdb/tree/LeafManager.h>
//#include <openvdb/util/logging.h>
//#include <algorithm> // for std::min()
//#include <cmath> // for std::abs(), std::fabs(), std::floor()
//#include <limits>
//#include <stdexcept>
//#include <type_traits> // for std::is_const


namespace openvdb_viewer {

namespace util {

/// Helper function used internally by processTypedGrid()
template<typename GridType, typename OpType, typename GridPtrType>
inline void
doProcessTypedGrid(GridPtrType grid, OpType& op)
{
}

template<typename GridPtrType, typename OpType>
bool
processTypedGrid(GridPtrType grid, OpType& op)
{
    using namespace openvdb;
    if (grid->template isType<BoolGrid>())        doProcessTypedGrid<BoolGrid>(grid, op);
    return true;
}


template<typename GridPtrType, typename OpType>
bool
processTypedScalarGrid(GridPtrType grid, OpType& op)
{
    return true;
}


template<typename GridPtrType, typename OpType>
bool
processTypedScalarOrPointDataGrid(GridPtrType grid, OpType& op)
{
    return false;
}


template<typename GridPtrType, typename OpType>
bool
processTypedVectorGrid(GridPtrType grid, OpType& op)
{
    return true;
}

}

class TreeTopologyOp
{
public:
    TreeTopologyOp() {}

    template<typename GridType>
    void operator()(typename GridType::ConstPtr grid)
    {
   }

private:
}; // TreeTopologyOp

////////////////////////////////////////

// Tree topology render module

TreeTopologyModule::TreeTopologyModule(const openvdb::GridBase::ConstPtr& grid):
    mGrid(grid)
{
}


void
TreeTopologyModule::init()
{
    // extract grid topology
    TreeTopologyOp drawTopology;

    util::processTypedGrid(mGrid, drawTopology);
}

} // namespace openvdb_viewer
