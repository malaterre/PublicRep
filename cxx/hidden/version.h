#ifndef OPENVDB_VERSION_HAS_BEEN_INCLUDED
#define OPENVDB_VERSION_HAS_BEEN_INCLUDED

#include "Platform.h"

#include <cstddef> // size_t
#include <cstdint> // uint32_t

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Auto generated build configurations from CMake

///@{
/// @brief Library major, minor and patch version numbers
/// @hideinitializer
#define OPENVDB_LIBRARY_MAJOR_VERSION_NUMBER 8
/// @hideinitializer
#define OPENVDB_LIBRARY_MINOR_VERSION_NUMBER 1
/// @hideinitializer
#define OPENVDB_LIBRARY_PATCH_VERSION_NUMBER 0
///@}

/// @note  This ifndef exists for compatibility with older versions of OpenVDB.
///   This value should never be different from the value configured when
///   OpenVDB was built, but this previously needed to be defined by downstream
///   software. Redefining it here would cause build failures, so this allows
///   users to transition and remove the define in their build systems.
#ifndef OPENVDB_ABI_VERSION_NUMBER
/// @brief The ABI version that OpenVDB was built with
/// @hideinitializer
#define OPENVDB_ABI_VERSION_NUMBER 8
#endif

/// @brief Library version number string of the form "<major>.<minor>.<patch>"
/// @details This is a macro rather than a static constant because we typically
/// want the compile-time version number, not the runtime version number
/// (although the two are usually the same).
/// @hideinitializer
#define OPENVDB_LIBRARY_VERSION_STRING "8.1.0"

/// @brief Library version number string of the form "<major>.<minor>.<patch>abi<abi>"
/// @details This is a macro rather than a static constant because we typically
/// want the compile-time version number, not the runtime version number
/// (although the two are usually the same).
/// @hideinitializer
#define OPENVDB_LIBRARY_ABI_VERSION_STRING "8.1.0abi8"

/// @brief Library version number as a packed integer ("%02x%02x%04x", major, minor, patch)
/// @hideinitializer
#define OPENVDB_LIBRARY_VERSION_NUMBER 134283264

/// @brief The version namespace name for this library version
/// @hideinitializer
///
/// When the ABI version number matches the library major version number,
/// symbols are named as in the following examples:
/// - @b openvdb::vX_Y::Vec3i
/// - @b openvdb::vX_Y::io::File
/// - @b openvdb::vX_Y::tree::Tree
///
/// where X and Y are the major and minor version numbers.
///
/// When the ABI version number does not match the library major version number,
/// symbol names include the ABI version:
/// - @b openvdb::vX_YabiN::Vec3i
/// - @b openvdb::vX_YabiN::io::File
/// - @b openvdb::vX_YabiN::tree::Tree
///
/// where X, Y and N are the major, minor and ABI version numbers, respectively.
#if OPENVDB_ABI_VERSION_NUMBER == OPENVDB_LIBRARY_MAJOR_VERSION_NUMBER
    #define OPENVDB_VERSION_NAME v8_1
#else
    #define OPENVDB_VERSION_NAME v8_1abi8
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////



/// By default, the @b OPENVDB_REQUIRE_VERSION_NAME macro is undefined, and
/// symbols from the version namespace are promoted to the top-level namespace
/// so that, for example, @b openvdb::v5_0::io::File can be referred to
/// simply as @b openvdb::io::File.
///
/// When @b OPENVDB_REQUIRE_VERSION_NAME is defined, symbols must be
/// fully namespace-qualified.
/// @hideinitializer
#ifdef OPENVDB_REQUIRE_VERSION_NAME
#define OPENVDB_USE_VERSION_NAMESPACE
#else
// The empty namespace clause below ensures that OPENVDB_VERSION_NAME
// is recognized as a namespace name.
#define OPENVDB_USE_VERSION_NAMESPACE \
    namespace OPENVDB_VERSION_NAME {} \
    using namespace OPENVDB_VERSION_NAME;
#endif


namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {

/// @brief The magic number is stored in the first four bytes of every VDB file.
/// @details This can be used to quickly test whether we have a valid file or not.
const int32_t OPENVDB_MAGIC = 0x56444220;

/// Library major, minor and patch version numbers
/// @hideinitializer
const uint32_t
    OPENVDB_LIBRARY_MAJOR_VERSION = OPENVDB_LIBRARY_MAJOR_VERSION_NUMBER,
    OPENVDB_LIBRARY_MINOR_VERSION = OPENVDB_LIBRARY_MINOR_VERSION_NUMBER,
    OPENVDB_LIBRARY_PATCH_VERSION = OPENVDB_LIBRARY_PATCH_VERSION_NUMBER;
/// Library version number as a packed integer ("%02x%02x%04x", major, minor, patch)
/// @hideinitializer
const uint32_t OPENVDB_LIBRARY_VERSION = OPENVDB_LIBRARY_VERSION_NUMBER;
/// ABI version number
/// @hideinitializer
const uint32_t OPENVDB_ABI_VERSION = OPENVDB_ABI_VERSION_NUMBER;

/// @brief The current version number of the VDB file format
/// @details  This can be used to enable various backwards compatibility switches
/// or to reject files that cannot be read.
const uint32_t OPENVDB_FILE_VERSION = 224;

} // namespace OPENVDB_VERSION_NAME
} // namespace openvdb

#endif // OPENVDB_VERSION_HAS_BEEN_INCLUDED
