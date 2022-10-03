cmake_minimum_required(VERSION 3.24)
project(p)

set(BOOST_INCLUDE_LIBRARIES thread filesystem system program_options)
set(BOOST_ENABLE_CMAKE ON)

include(FetchContent)
FetchContent_Declare(
  log4cpp
  URL https://sourceforge.net/projects/log4cpp/files/log4cpp-1.1.x%20%28new%29/log4cpp-1.1/log4cpp-1.1.3.tar.gz
  )
FetchContent_MakeAvailable(log4cpp)

# find_package(Boost 1.53 REQUIRED COMPONENTS thread filesystem system
# program_options)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE log4cpp)
