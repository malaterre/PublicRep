#ifndef OPENVDB_GRID_HAS_BEEN_INCLUDED
#define OPENVDB_GRID_HAS_BEEN_INCLUDED

#include "Types.h"
#include <iostream>

namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {


class OPENVDB_API GridBase
{
public:
    using ConstPtr = SharedPtr<const GridBase>;

    virtual std::string type() const = 0;

    template<typename GridType>
    bool isType() const { return (this->type() == GridType::gridType()); }
};

template<typename _TreeType>
class Grid: public GridBase
{
public:
    using TreeType            = _TreeType;

    std::string type() const override { return this->gridType(); }
    static std::string gridType() { return TreeType::treeType(); }
}; // class Grid

} // namespace OPENVDB_VERSION_NAME
} // namespace openvdb

#endif // OPENVDB_GRID_HAS_BEEN_INCLUDED
