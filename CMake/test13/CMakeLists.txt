cmake_minimum_required(VERSION 3.24)
project(p)

include(FetchContent)
FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.74.0
  #GIT_SHALLOW ON
  #GIT_PROGRESS ON
  #FIND_PACKAGE_ARGS NAMES Boost 1.75.0 REQUIRED
)
set(BOOST_INCLUDE_LIBRARIES filesystem system) # enabled libraries
set(BOOST_ENABLE_CMAKE ON) # CMake support
FetchContent_MakeAvailable(Boost)

add_executable(boost_test boost_test.cpp)
target_link_libraries(boost_test PRIVATE Boost::filesystem)
