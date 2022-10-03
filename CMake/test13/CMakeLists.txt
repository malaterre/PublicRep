cmake_minimum_required(VERSION 3.24)
project(p)

include(FetchContent)
FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.55.0
  # FIND_PACKAGE_ARGS NAMES Boost 1.75.0 REQUIRED
)
set(BOOST_ENABLE_CMAKE ON)
FetchContent_MakeAvailable(Boost)

add_executable(boost_test boost_test.cpp)
target_link_libraries(boost_test PRIVATE Boost::format)
