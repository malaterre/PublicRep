#ifndef OPENVDB_TYPES_HAS_BEEN_INCLUDED
#define OPENVDB_TYPES_HAS_BEEN_INCLUDED

#include <typeinfo>

namespace openvdb {
template<typename T> const char* typeNameAsString()                 { return typeid(T).name(); }
template<> inline const char* typeNameAsString<bool>()              { return "bool"; }
}

#endif // OPENVDB_TYPES_HAS_BEEN_INCLUDED
