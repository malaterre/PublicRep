cmake_minimum_required(VERSION 2.8)
project(current_scope)

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

add_library(thelib SHARED cov.cxx)

set_source_files_properties(foo.i PROPERTIES CPLUSPLUS ON)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)

set(CMAKE_SWIG_FLAGS "-namespace foo -dllimport foosharpglue")
separate_arguments(CMAKE_SWIG_FLAGS)

swig_add_module(foo csharp foo.i)
swig_link_libraries(foo thelib)
