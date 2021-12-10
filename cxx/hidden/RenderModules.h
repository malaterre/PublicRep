#ifndef OPENVDB_VIEWER_RENDERMODULES_HAS_BEEN_INCLUDED
#define OPENVDB_VIEWER_RENDERMODULES_HAS_BEEN_INCLUDED

#include <openvdb.h>

namespace openvdb_viewer {

class TreeTopologyModule
{
public:
    TreeTopologyModule(const openvdb::GridBase::ConstPtr&);
private:
    void init();
    const openvdb::GridBase::ConstPtr& mGrid;
};

} // namespace openvdb_viewer

#endif // OPENVDB_VIEWER_RENDERMODULES_HAS_BEEN_INCLUDED
