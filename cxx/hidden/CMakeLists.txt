cmake_minimum_required(VERSION 3.13)
project(hidden)


add_library(openvdb SHARED openvdb.cc)
#include_directories("/usr/include")
target_include_directories(openvdb 
#PUBLIC /usr/include
PRIVATE 
/home/mathieu/Perso/PublicRep/cxx/hidden/t/openvdb-8.1.0/openvdb/openvdb
/home/mathieu/Perso/PublicRep/cxx/hidden/t/openvdb-8.1.0/openvdb
${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(vdb_view openvdb_view.cc)
target_link_libraries(vdb_view openvdb tbb)
