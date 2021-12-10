#ifndef OPENVDB_GRID_HAS_BEEN_INCLUDED
#define OPENVDB_GRID_HAS_BEEN_INCLUDED

#include "Types.h"
#include <iostream>

namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {

typedef std::string Name;

class OPENVDB_API GridBase
{
public:
    using ConstPtr = SharedPtr<const GridBase>;

    virtual Name type() const = 0;

    template<typename GridType>
    bool isType() const { return (this->type() == GridType::gridType()); }
};

template<typename _TreeType>
class Grid: public GridBase
{
public:
    using Ptr                 = SharedPtr<Grid>;

    using TreeType            = _TreeType;
    using TreePtrType         = typename _TreeType::Ptr;

    Name type() const override { return this->gridType(); }
    static Name gridType() { return TreeType::treeType(); }
}; // class Grid

} // namespace OPENVDB_VERSION_NAME
} // namespace openvdb

#endif // OPENVDB_GRID_HAS_BEEN_INCLUDED
