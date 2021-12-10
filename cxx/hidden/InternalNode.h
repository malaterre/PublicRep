#ifndef OPENVDB_TREE_INTERNALNODE_HAS_BEEN_INCLUDED
#define OPENVDB_TREE_INTERNALNODE_HAS_BEEN_INCLUDED

#include <Platform.h>
#include <version.h>
#include <Types.h>
#include <tbb/parallel_for.h>
#include <memory>
#include <type_traits>


namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {
namespace tree {


template<typename _ChildNodeType, Index Log2Dim>
class InternalNode
{
public:
    using ChildNodeType = _ChildNodeType;
    using LeafNodeType = typename ChildNodeType::LeafNodeType;
    using ValueType = typename ChildNodeType::ValueType;
    using BuildType = typename ChildNodeType::BuildType;

    static const Index
        LOG2DIM      = Log2Dim,                        // log2 of tile count in one dimension
        TOTAL        = Log2Dim + ChildNodeType::TOTAL, // log2 of voxel count in one dimension
        DIM          = 1 << TOTAL,                     // total voxel count in one dimension
        NUM_VALUES   = 1 << (3 * Log2Dim),             // total voxel count represented by this node
        LEVEL        = 1 + ChildNodeType::LEVEL;       // level 0 = leaf
    static const Index64
        NUM_VOXELS   = uint64_t(1) << (3 * TOTAL);     // total voxel count represented by this node

public:
    static void getNodeLog2Dims(std::vector<Index>& dims);
}; // class InternalNode


template<typename ChildT, Index Log2Dim>
void
InternalNode<ChildT, Log2Dim>::getNodeLog2Dims(std::vector<Index>& dims)
{
    dims.push_back(Log2Dim);
    ChildNodeType::getNodeLog2Dims(dims);
}
} // namespace tree
} // namespace OPENVDB_VERSION_NAME
} // namespace openvdb

#endif // OPENVDB_TREE_INTERNALNODE_HAS_BEEN_INCLUDED
