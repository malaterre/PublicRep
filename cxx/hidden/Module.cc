#include "Tree.h"

class Module
{
    void init();
};

void Module::init() // no-inline
{
   Tree<bool>::treeType();
}
