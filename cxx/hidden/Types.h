#ifndef OPENVDB_TYPES_HAS_BEEN_INCLUDED
#define OPENVDB_TYPES_HAS_BEEN_INCLUDED

#include "version.h"
#include "Platform.h"

#include <cstdint>
#include <memory>
#include <type_traits>

namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {
using Index32 = uint32_t;
using Index64 = uint64_t;
using Index   = Index32;

template<typename T> using SharedPtr = std::shared_ptr<T>;
template<typename T> using WeakPtr = std::weak_ptr<T>;

template<typename T> const char* typeNameAsString()                 { return typeid(T).name(); }
template<> inline const char* typeNameAsString<bool>()              { return "bool"; }
}
}

#endif // OPENVDB_TYPES_HAS_BEEN_INCLUDED
