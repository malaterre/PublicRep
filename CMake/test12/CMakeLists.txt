cmake_minimum_required(VERSION 3.24)
project(p)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        58d77fa8070e8cec2dc1ed015d66b454c8d78850 # release-1.12.1
  OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(googletest)

if(NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/gtest-config.cmake AND
   NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/GTestConfig.cmake)
  file(WRITE ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/gtest-config.cmake
[=[
include(CMakeFindDependencyMacro)
find_dependency(googletest)
]=])
endif()

if(NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/gtest-config-version.cmake AND
   NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/GTestConfigVersion.cmake)
  file(WRITE ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/gtest-config-version.cmake
[=[
include(${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/googletest-config-version.cmake OPTIONAL)
if(NOT PACKAGE_VERSION_COMPATIBLE)
  include(${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/googletestConfigVersion.cmake OPTIONAL)
endif()
]=])
endif()

# Now make sure hwy uses our gtest 1.12.1:
set(HWY_SYSTEM_GTEST ON CACHE BOOL "")
FetchContent_Declare(
  hwy
  GIT_REPOSITORY https://github.com/google/highway.git
  GIT_TAG        22e3d7276f4157d4a47586ba9fd91dd6303f441a # 1.0.1
)
FetchContent_MakeAvailable(hwy)
