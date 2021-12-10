#ifndef OPENVDB_PLATFORM_HAS_BEEN_INCLUDED
#define OPENVDB_PLATFORM_HAS_BEEN_INCLUDED

#define OPENVDB_EXPORT __attribute__((visibility("default")))
#define OPENVDB_IMPORT __attribute__((visibility("default")))

#ifdef OPENVDB_PRIVATE
    #define OPENVDB_API OPENVDB_EXPORT
#else
    #define OPENVDB_API OPENVDB_IMPORT
#endif



#endif // OPENVDB_PLATFORM_HAS_BEEN_INCLUDED
