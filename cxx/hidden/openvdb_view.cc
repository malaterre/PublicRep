#include "version.h"

namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {
OPENVDB_API void initialize();
} // namespace OPENVDB_VERSION_NAME
} // namespace openvdb

int
main(int , char *[])
{
    openvdb::initialize();

    return 0;
}
