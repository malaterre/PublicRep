cmake_minimum_required(VERSION 3.13)
project(hidden)

# only export limited set of symbols
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

# require c++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#set(THREADS_PREFER_PTHREAD_FLAG TRUE)
#find_package(Threads)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
add_library(openvdb SHARED openvdb.cc)
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")
#include_directories("/usr/include")
target_include_directories(openvdb 
#PUBLIC /usr/include
PRIVATE 
#/home/mathieu/Perso/PublicRep/cxx/hidden/t/openvdb-8.1.0/openvdb/openvdb
#/home/mathieu/Perso/PublicRep/cxx/hidden/t/openvdb-8.1.0/openvdb
${CMAKE_CURRENT_SOURCE_DIR}
)

  target_compile_definitions(openvdb
    PUBLIC ${OPENVDB_CORE_PUBLIC_DEFINES} -DOPENVDB_DLL
    PRIVATE ${OPENVDB_CORE_PRIVATE_DEFINES}
     -DBOOST_IOSTREAMS_DYN_LINK -DBOOST_SYSTEM_DYN_LINK -DOPENVDB_DLL -DOPENVDB_PRIVATE 
  )

add_executable(vdb_view openvdb_view.cc RenderModules.cc)
target_link_libraries(vdb_view openvdb tbb Threads::Threads)
target_include_directories(vdb_view
PRIVATE 
${CMAKE_CURRENT_SOURCE_DIR}
)

