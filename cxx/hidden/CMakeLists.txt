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

#set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
#set(THREADS_PREFER_PTHREAD_FLAG TRUE)
#find_package(Threads REQUIRED)
add_library(openvdb SHARED openvdb.cc)
target_include_directories(openvdb 
PRIVATE 
${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(vdb_view main.cc Module.cc)
target_link_libraries(vdb_view openvdb) # Threads::Threads)
target_include_directories(vdb_view
PRIVATE 
${CMAKE_CURRENT_SOURCE_DIR}
)

