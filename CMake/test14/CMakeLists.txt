cmake_minimum_required(VERSION 3.24)
project(p)

include(FetchContent)
FetchContent_Declare(
  Log4CPP
  URL https://sourceforge.net/projects/log4cpp/files/log4cpp-1.1.x%20%28new%29/log4cpp-1.1/log4cpp-1.1.3.tar.gz
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  #OVERRIDE_FIND_PACKAGE
  )
FetchContent_MakeAvailable(Log4CPP)
set(LOG4CPP_INCLUDE_DIRS ${log4cpp_SOURCE_DIR}/include)
#if(NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/log4cpp-extra.cmake
#		AND NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/Log4CPPExtra.cmake)
#  file(
#    WRITE ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/log4cpp-extra.cmake
#    [=[
#    set(LOG4CPP_INCLUDE_DIRS ${log4cpp_SOURCE_DIR}/include)
#]=])
#endif()
#find_package(Log4CPP)

include_directories(${LOG4CPP_INCLUDE_DIRS})
add_executable(main main.cpp)
target_link_libraries(main PRIVATE log4cpp)
