#include "RenderModules.h"

namespace openvdb_viewer {

namespace util {

/// Helper function used internally by processTypedGrid()
template<typename GridType, typename OpType, typename GridPtrType>
inline void
doProcessTypedGrid(GridPtrType , OpType& )
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

}

class TreeTopologyOp
{
};

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
