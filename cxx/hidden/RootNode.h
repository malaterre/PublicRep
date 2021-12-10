#ifndef OPENVDB_TREE_ROOTNODE_HAS_BEEN_INCLUDED
#define OPENVDB_TREE_ROOTNODE_HAS_BEEN_INCLUDED

#include <Types.h>
#include <tbb/parallel_for.h>
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
    static void getNodeLog2Dims(std::vector<Index>& dims);
}; // end of RootNode class

template<typename HeadT, int HeadLevel>
struct NodeChain {
    using SubtreeT = typename NodeChain<typename HeadT::ChildNodeType, HeadLevel-1>::Type;
    using Type = typename SubtreeT::template Append<HeadT>;
};

template<typename ChildT>
inline void
RootNode<ChildT>::getNodeLog2Dims(std::vector<Index>& dims)
{
    dims.push_back(0); // magic number; RootNode has no Log2Dim
    ChildT::getNodeLog2Dims(dims);
}



} // namespace tree
} // namespace OPENVDB_VERSION_NAME
} // namespace openvdb

#endif // OPENVDB_TREE_ROOTNODE_HAS_BEEN_INCLUDED
