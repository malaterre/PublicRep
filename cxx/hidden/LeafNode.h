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

    static const Index
        LOG2DIM     = Log2Dim,      // needed by parent nodes
        TOTAL       = Log2Dim,      // needed by parent nodes
        DIM         = 1 << TOTAL,   // dimension along one coordinate direction
        NUM_VALUES  = 1 << 3 * Log2Dim,
        NUM_VOXELS  = NUM_VALUES,   // total number of voxels represented by this node
        SIZE        = NUM_VALUES,
        LEVEL       = 0;            // level 0 = leaf

    /// Append the Log2Dim of this LeafNode to the specified vector
    static void getNodeLog2Dims(std::vector<Index>& dims) { dims.push_back(Log2Dim); }

}; // end of LeafNode class

} // namespace tree
} // namespace OPENVDB_VERSION_NAME
} // namespace openvdb


////////////////////////////////////////


// Specialization for LeafNodes of type bool
//#include "LeafNodeBool.h"

// Specialization for LeafNodes with mask information only
//#include "LeafNodeMask.h"

#endif // OPENVDB_TREE_LEAFNODE_HAS_BEEN_INCLUDED
