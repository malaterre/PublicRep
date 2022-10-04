cmake_minimum_required(VERSION 3.24)
project(p)

set(BOOST_INCLUDE_LIBRARIES filesystem system program_options)
set(BOOST_ENABLE_CMAKE ON)

include(FetchContent)
FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.80.0
)
FetchContent_MakeAvailable(Boost)

add_executable(boost_test boost_test.cpp)
target_link_libraries(boost_test PRIVATE Boost::filesystem
                                         Boost::program_options)
