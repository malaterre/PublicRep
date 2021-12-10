#ifndef OPENVDB_TREE_LEAFNODE_HAS_BEEN_INCLUDED
#define OPENVDB_TREE_LEAFNODE_HAS_BEEN_INCLUDED

#include <Types.h>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>

namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {
namespace tree {

template<typename T, Index Log2Dim>
class LeafNode
{
public:
    using BuildType = T;
    using ValueType = T;
    using LeafNodeType = LeafNode<ValueType, Log2Dim>;
    using Ptr = SharedPtr<LeafNode>;


}; // end of LeafNode class

} // namespace tree
} // namespace OPENVDB_VERSION_NAME
} // namespace openvdb

#endif // OPENVDB_TREE_LEAFNODE_HAS_BEEN_INCLUDED
