#include "openvdb.h"

namespace openvdb {

class Module
{
    void init();
};

void Module::init() // no-inline
{
   openvdb::BoolTree::treeType();
}

}
