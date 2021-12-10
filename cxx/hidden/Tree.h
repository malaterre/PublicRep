#ifndef OPENVDB_TREE_TREE_HAS_BEEN_INCLUDED
#define OPENVDB_TREE_TREE_HAS_BEEN_INCLUDED

#include "Types.h"
#include "Platform.h"
#include "RootNode.h"
#include "InternalNode.h"
#include "LeafNode.h"
#include <tbb/concurrent_hash_map.h>
#include <cstdint>
#include <mutex>
#include <sstream>
#include <vector>


namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {
namespace tree {

class OPENVDB_API TreeBase
{
public:
    using Ptr = SharedPtr<TreeBase>;
    using ConstPtr = SharedPtr<const TreeBase>;

    virtual const Name& type() const = 0;
};


template<typename _RootNodeType>
class Tree: public TreeBase
{
public:
    using Ptr = SharedPtr<Tree>;
    using ConstPtr = SharedPtr<const Tree>;

    using RootNodeType = _RootNodeType;
    using ValueType = typename RootNodeType::ValueType;
    using BuildType = typename RootNodeType::BuildType;
    using LeafNodeType = typename RootNodeType::LeafNodeType;

    static const Name& treeType();
    const Name& type() const override { return this->treeType(); }

    static void getNodeLog2Dims(std::vector<Index>& dims);

private:
    static std::unique_ptr<const Name> sTreeTypeName;
}; // end of Tree class

template<typename _RootNodeType>
std::unique_ptr<const Name> Tree<_RootNodeType>::sTreeTypeName;

template<typename T, Index N1=5, Index N2=4, Index N3=3>
struct Tree4 {
    using Type = Tree<RootNode<InternalNode<InternalNode<LeafNode<T, N3>, N2>, N1>>>;
};

template<typename RootNodeType>
inline const Name&
Tree<RootNodeType>::treeType()
{
    static std::once_flag once;
    std::call_once(once, []()
    {
        std::vector<Index> dims;
        Tree::getNodeLog2Dims(dims);
        std::ostringstream ostr;
//        ostr << "Tree_" << typeNameAsString<BuildType>();
        for (size_t i = 1, N = dims.size(); i < N; ++i) { // start from 1 to skip the RootNode
            ostr << "_" << dims[i];
        }
        sTreeTypeName.reset(new Name(ostr.str()));
    });
    return *sTreeTypeName;
}

template<typename RootNodeType>
inline void
Tree<RootNodeType>::getNodeLog2Dims(std::vector<Index>& dims)
{
    dims.clear();
    RootNodeType::getNodeLog2Dims(dims);
}

} // namespace tree
} // namespace OPENVDB_VERSION_NAME
} // namespace openvdb

#endif // OPENVDB_TREE_TREE_HAS_BEEN_INCLUDED
