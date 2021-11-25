cmake_minimum_required(VERSION 3.22)
project(p)

add_library(foo SHARED foo.cxx)
set_property(TARGET foo PROPERTY COMPILE_FLAGS "-fno-exceptions")
set_property(TARGET foo PROPERTY LINK_FLAGS "-Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/foo.version")

add_executable(bar bar.cxx)
target_link_libraries(bar foo)
