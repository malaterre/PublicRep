project(vector)
cmake_minimum_required(VERSION 2.8)

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

include_directories(
${PYTHON_INCLUDE_PATH}
)

add_library(thelib SHARED myfile.cxx)

find_package(PythonLibs)
set_source_files_properties(demo.i PROPERTIES CPLUSPLUS ON)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)

swig_add_module(demo python demo.i)
swig_link_libraries(demo thelib)
