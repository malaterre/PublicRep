#ifndef OPENVDB_TREE_LEAFNODE_HAS_BEEN_INCLUDED
#define OPENVDB_TREE_LEAFNODE_HAS_BEEN_INCLUDED

#include <Types.h>

namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {
namespace tree {

template<typename T, Index Log2Dim>
class LeafNode
{
public:
    using ValueType = T;
}; // end of LeafNode class

} // namespace tree
} // namespace OPENVDB_VERSION_NAME
} // namespace openvdb

#endif // OPENVDB_TREE_LEAFNODE_HAS_BEEN_INCLUDED
