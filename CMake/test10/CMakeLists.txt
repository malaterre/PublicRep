cmake_minimum_required(VERSION 3.16.3)
project(p)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
  FIND_PACKAGE_ARGS NAMES gtest
)

# This will try calling find_package() first for both dependencies
FetchContent_MakeAvailable(googletest)
find_package(GTest)
