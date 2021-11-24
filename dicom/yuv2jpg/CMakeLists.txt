cmake_minimum_required(VERSION 3.22)
project(yuv2jpg)

find_package(JPEG)

add_executable(yuv2jpg yuv2jpg.cxx)
target_link_libraries(yuv2jpg PRIVATE ${JPEG_LIBRARIES})
