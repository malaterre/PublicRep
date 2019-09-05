cmake_minimum_required(VERSION 3.14)
project(test3 C)

set(MY_PRODUCT_NUMBER 3)
set(MY_PRODUCT_VERSION 5)
set(MY_BUILD_NUMBER 49)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/version.rc.in
  ${CMAKE_CURRENT_BINARY_DIR}/version.rc
  @ONLY)

add_library(foo SHARED foo.c
  ${CMAKE_CURRENT_BINARY_DIR}/version.rc)

