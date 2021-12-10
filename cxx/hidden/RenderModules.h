#ifndef OPENVDB_VIEWER_RENDERMODULES_HAS_BEEN_INCLUDED
#define OPENVDB_VIEWER_RENDERMODULES_HAS_BEEN_INCLUDED

#include <openvdb.h>

namespace openvdb_viewer {

class RenderModule
{
public:
    virtual ~RenderModule() {}
};

class TreeTopologyModule/*: public RenderModule*/
{
public:
    TreeTopologyModule(const openvdb::GridBase::ConstPtr&);
//    ~TreeTopologyModule() override = default;
private:
    void init();

    const openvdb::GridBase::ConstPtr& mGrid;
};



} // namespace openvdb_viewer

#endif // OPENVDB_VIEWER_RENDERMODULES_HAS_BEEN_INCLUDED
