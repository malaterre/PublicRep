cmake_minimum_required(VERSION 3.24)
project(p)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
  OVERRIDE_FIND_PACKAGE
)

# The following will automatically forward through to FetchContent_MakeAvailable()
find_package(googletest)

if(TARGET GTest::gtest_main)
	message("coucou")
endif()
