#include "RenderModules.h"

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
