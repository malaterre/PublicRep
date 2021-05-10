cmake_minimum_required(VERSION 3.13.4)
project(
  p
  VERSION 0.0.1
  LANGUAGES CXX C)

set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

set(CMAKE_CXX_STANDARD 14)

add_executable(foo foo.cxx bla.cxx)
