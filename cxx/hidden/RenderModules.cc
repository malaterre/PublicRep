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


void
TreeTopologyModule::init()
{
    // extract grid topology
    TreeTopologyOp drawTopology;
    const openvdb::GridBase::ConstPtr mGrid2;

    util::processTypedGrid(mGrid2, drawTopology);
}

} // namespace openvdb_viewer
