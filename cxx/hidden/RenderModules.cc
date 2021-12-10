#include "RenderModules.h"

namespace openvdb_viewer {

template<typename GridType, /*typename OpType,*/ typename GridPtrType>
inline void
doProcessTypedGrid(GridPtrType /*, OpType&*/ )
{
}

template<typename GridPtrType/*, typename OpType = int*/>
bool
processTypedGrid(GridPtrType grid/*, OpType& op*/)
{
    using namespace openvdb;
    return grid->template isType<BoolGrid>();
}

//class TreeTopologyOp
//{
//};

void
TreeTopologyModule::init()
{
    const std::shared_ptr<openvdb::GridBase> mGrid2;

    processTypedGrid(mGrid2);
}

} // namespace openvdb_viewer
