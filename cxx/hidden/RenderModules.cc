#include "openvdb.h"

namespace openvdb {

class TreeTopologyModule
{
    void init();
};

void TreeTopologyModule::init()
{
   openvdb::BoolTree::treeType();
}

}
