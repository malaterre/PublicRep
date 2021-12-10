#include "openvdb.h"

namespace openvdb_viewer {

class TreeTopologyModule
{
    void init();
};

void TreeTopologyModule::init()
{
   openvdb::BoolTree::treeType();
}

} // namespace openvdb_viewer
