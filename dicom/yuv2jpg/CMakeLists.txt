cmake_minimum_required(VERSION 3.22)
project(yuv2jpg)

find_package(JPEG)

add_executable(yuv2jpg yuv2jpg.cxx)
target_link_libraries(yuv2jpg PRIVATE ${JPEG_LIBRARIES})

add_executable(jpg2yuv jpg2yuv.cxx)
target_link_libraries(jpg2yuv PRIVATE ${JPEG_LIBRARIES})

add_executable(yuv422jpg yuv422jpg.c)
target_link_libraries(yuv422jpg PRIVATE ${JPEG_LIBRARIES})
