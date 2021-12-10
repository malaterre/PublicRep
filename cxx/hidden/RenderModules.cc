#include "openvdb.h"

namespace openvdb_viewer {

class TreeTopologyModule
{
    void init();
};

void TreeTopologyModule::init()
{
   openvdb::BoolTree::treeType();
//   openvdb::BoolGrid::gridType();
}

} // namespace openvdb_viewer
