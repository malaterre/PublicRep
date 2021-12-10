#include "version.h"

namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {
	OPENVDB_API void initialize();

/// Global deregistration of basic types

} // namespace OPENVDB_VERSION_NAME
} // namespace openvdb


int
main(int argc, char *argv[])
{
        openvdb::initialize();

    return 0;
}
