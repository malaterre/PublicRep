#include "openvdb.h"

namespace openvdb {

class TreeTopologyModule
{
    void init();
};

void TreeTopologyModule::init() // no-inline
{
   openvdb::BoolTree::treeType();
}

}
