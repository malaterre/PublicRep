// Copyright Contributors to the OpenVDB Project
// SPDX-License-Identifier: MPL-2.0

/// @file tree/Tree.h

#ifndef OPENVDB_TREE_TREE_HAS_BEEN_INCLUDED
#define OPENVDB_TREE_TREE_HAS_BEEN_INCLUDED

#include <version.h>
#include <Platform.h>
#include <tbb/concurrent_hash_map.h>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <sstream>
#include <vector>


namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {
namespace tree {

/// @brief Base class for typed trees
class OPENVDB_API TreeBase
{
public:
};

template<typename ChildType>
class RootNode
{};

template<typename _ChildNodeType, uint32_t Log2Dim>
class InternalNode
{
};

template<typename T, uint32_t Log2Dim>
class LeafNode
{
};
////////////////////////////////////////


template<typename _RootNodeType>
class Tree: public TreeBase
{
public:
    /// Return the name of this type of tree.
    static const std::string& treeType();
    /// Return the name of this type of tree.
//    const std::string& type() const override { return this->treeType(); }

    static std::unique_ptr<const std::string> sTreeTypeName;
}; // end of Tree class

template<typename _RootNodeType>
std::unique_ptr<const std::string> Tree<_RootNodeType>::sTreeTypeName;

template<typename T, uint32_t N1=5, uint32_t N2=4, uint32_t N3=3>
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
        std::vector<uint32_t> dims;
        //Tree::getNodeLog2Dims(dims);
        std::ostringstream ostr;
        //ostr << "Tree_" << typeNameAsString<BuildType>();
        for (size_t i = 1, N = dims.size(); i < N; ++i) { // start from 1 to skip the RootNode
            ostr << "_" << dims[i];
        }
        sTreeTypeName.reset(new std::string(ostr.str()));
    });
    return *sTreeTypeName;
}



} // namespace tree
} // namespace OPENVDB_VERSION_NAME
} // namespace openvdb

#endif // OPENVDB_TREE_TREE_HAS_BEEN_INCLUDED
