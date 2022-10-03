cmake_minimum_required(VERSION 3.24)
project(p)

set(BOOST_INCLUDE_LIBRARIES thread filesystem system program_options)
set(BOOST_ENABLE_CMAKE ON)

include(FetchContent)
FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.80.0
  FIND_PACKAGE_ARGS
  NAMES
  Boost
  1.53
  REQUIRED
  COMPONENTS
  ${BOOST_INCLUDE_LIBRARIES})
FetchContent_MakeAvailable(Boost)

# find_package(Boost 1.53 REQUIRED COMPONENTS thread filesystem system
# program_options)

add_executable(boost_test boost_test.cpp)
target_link_libraries(boost_test PRIVATE Boost::filesystem
                                         Boost::program_options)
