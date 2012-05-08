cmake_minimum_required(VERSION 2.8)
project(test2 C)

SET(LIB_PROPERTIES
  VERSION "1.0"
  SOVERSION "1"
)

add_library(lib2 SHARED bla.c)
set_property(TARGET lib2 PROPERTY ${LIB_PROPERTIES})
