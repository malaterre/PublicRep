#ifndef OPENVDB_TREE_TREE_HAS_BEEN_INCLUDED
#define OPENVDB_TREE_TREE_HAS_BEEN_INCLUDED

#include "Platform.h"
#include <mutex>
#include <memory>

namespace openvdb {
namespace tree {

template<typename ChildType>
class RootNode
{
}; // end of RootNode class

template<typename _ChildNodeType, int Log2Dim>
class InternalNode
{
};
template<typename T, int Log2Dim>
class LeafNode
{
}; // end of LeafNode class


class OPENVDB_API TreeBase
{
public:
    virtual const std::string& type() const = 0;
};

template<typename _RootNodeType>
class Tree/*: public TreeBase*/
{
public:
    using RootNodeType = _RootNodeType;

    static const std::string& treeType();
    const std::string& type() const { return this->treeType(); }
private:
    static std::unique_ptr<const std::string> sTreeTypeName;
};

template<typename _RootNodeType>
std::unique_ptr<const std::string> Tree<_RootNodeType>::sTreeTypeName;

template<typename T, int N1=5, int N2=4, int N3=3>
struct Tree4 {
    using Type = Tree<RootNode<InternalNode<InternalNode<LeafNode<T, N3>, N2>, N1>>>;
};

template<typename RootNodeType>
inline const std::string&
Tree<RootNodeType>::treeType()
{
    static std::once_flag once;
    std::call_once(once, []()
    {
        sTreeTypeName.reset(new std::string());
    });
    return *sTreeTypeName;
}

} // namespace tree
} // namespace openvdb

#endif // OPENVDB_TREE_TREE_HAS_BEEN_INCLUDED
