#ifndef OPENVDB_TYPES_HAS_BEEN_INCLUDED
#define OPENVDB_TYPES_HAS_BEEN_INCLUDED

#include "Platform.h"
#include <typeinfo>

namespace openvdb {
using Index32 = int;
using Index64 = long;
using Index   = Index32;


template<typename T> const char* typeNameAsString()                 { return typeid(T).name(); }
template<> inline const char* typeNameAsString<bool>()              { return "bool"; }
}

#endif // OPENVDB_TYPES_HAS_BEEN_INCLUDED
