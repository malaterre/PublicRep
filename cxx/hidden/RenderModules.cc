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
   openvdb::BoolGrid::gridType();
   return true;
   // return (grid->type() == openvdb::BoolGrid::gridType());
}

void
TreeTopologyModule::init()
{
   openvdb::BoolGrid::gridType();
   // const std::shared_ptr<openvdb::GridBase> mGrid2;

   // processTypedGrid(mGrid2);
}

} // namespace openvdb_viewer
