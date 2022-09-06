cmake_minimum_required(VERSION 3.24)
project(p)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
  #FIND_PACKAGE_ARGS 1.11 REQUIRED NAMES gtest
  FIND_PACKAGE_ARGS NAMES prout
)

# This will try calling find_package() first for both dependencies
FetchContent_MakeAvailable(googletest)
#find_package(GTest)
#message(${GTest_DIR})
