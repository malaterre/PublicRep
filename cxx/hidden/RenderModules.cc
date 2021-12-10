#include "openvdb.h"

namespace openvdb_viewer {

	class TreeTopologyModule
{
private:
    void init();
};


template<typename GridPtrType>
bool
processTypedGrid(GridPtrType grid)
{
    return grid->template isType<openvdb::BoolGrid>();
}

void
TreeTopologyModule::init()
{
    const std::shared_ptr<openvdb::GridBase> mGrid2;

    processTypedGrid(mGrid2);
}

} // namespace openvdb_viewer
