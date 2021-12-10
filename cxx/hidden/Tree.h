#ifndef OPENVDB_TREE_TREE_HAS_BEEN_INCLUDED
#define OPENVDB_TREE_TREE_HAS_BEEN_INCLUDED

#include "Types.h"
#include "Platform.h"
#include "RootNode.h"
#include "InternalNode.h"
#include "LeafNode.h"
#include <mutex>

namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {
namespace tree {

class OPENVDB_API TreeBase
{
public:

    virtual const Name& type() const = 0;
};

template<typename _RootNodeType>
class Tree: public TreeBase
{
public:

    using RootNodeType = _RootNodeType;

    static const Name& treeType();
    const Name& type() const override { return this->treeType(); }

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
        sTreeTypeName.reset(new Name());
    });
    return *sTreeTypeName;
}


} // namespace tree
} // namespace OPENVDB_VERSION_NAME
} // namespace openvdb

#endif // OPENVDB_TREE_TREE_HAS_BEEN_INCLUDED
