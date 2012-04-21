# http://cmake.org/Bug/view.php?id=13155#c29270
string(REPLACE "<CMAKE_SHARED_LIBRARY_SONAME_C_FLAG><TARGET_SONAME>" "" CMAKE_C_CREATE_SHARED_MODULE "${CMAKE_C_CREATE_SHARED_MODULE}")
cmake_minimum_required(VERSION 2.8)
project(test1 C)

add_library(lib1 SHARED foo.c)
add_library(lib2 MODULE foo.c)

install(TARGETS lib1 lib2
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib)
