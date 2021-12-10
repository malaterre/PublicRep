#include "RenderModules.h"

namespace openvdb_viewer {

namespace util {

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
    TreeTopologyOp drawTopology;
    const std::shared_ptr<openvdb::GridBase> mGrid2;

    util::processTypedGrid(mGrid2, drawTopology);
}

} // namespace openvdb_viewer
