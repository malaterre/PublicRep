cmake_minimum_required(VERSION 3.18)
project(top-level)
# see https://github.com/sunsided/cmake

add_subdirectory(extern)
find_package(foo CONFIG REQUIRED HINTS
             ${CMAKE_CURRENT_BINARY_DIR}/extern/foo)
