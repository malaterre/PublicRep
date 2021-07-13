cmake_minimum_required(VERSION 3.16)
project(p)

set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
set(CMAKE_CXX_STANDARD 14)

add_library(p SHARED p.cxx)
set_target_properties(p PROPERTIES VERSION 0
                                           SOVERSION 0)
