#ifndef OPENVDB_TREE_ROOTNODE_HAS_BEEN_INCLUDED
#define OPENVDB_TREE_ROOTNODE_HAS_BEEN_INCLUDED

#include <Types.h>
#include <vector>

namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {
namespace tree {

template<typename ChildType>
class RootNode
{
public:
    using ChildNodeType = ChildType;
    using LeafNodeType = typename ChildType::LeafNodeType;
    using ValueType = typename ChildType::ValueType;
    using BuildType = typename ChildType::BuildType;

private:
public:
}; // end of RootNode class



} // namespace tree
} // namespace OPENVDB_VERSION_NAME
} // namespace openvdb

#endif // OPENVDB_TREE_ROOTNODE_HAS_BEEN_INCLUDED
