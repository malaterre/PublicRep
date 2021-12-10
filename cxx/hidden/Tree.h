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


template<typename _RootNodeType>
class Tree
{
public:
    static const std::string& treeType();
    const std::string& type() const { return this->treeType(); }
private:
    static std::unique_ptr<const std::string> sTreeTypeName;
};

template<typename _RootNodeType>
std::unique_ptr<const std::string> Tree<_RootNodeType>::sTreeTypeName;

template<typename T>
struct Tree4 {
    using Type = Tree<T>;
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
