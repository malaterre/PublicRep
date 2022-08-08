project(p)
add_executable(demo demo.cc bytes.cc)
target_link_libraries(demo hwy hwy_test)
