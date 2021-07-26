cmake_minimum_required(VERSION 3.16)
project(lo)
find_package(DCMTK REQUIRED)

add_executable(main main.cxx)
target_include_directories(main PRIVATE ${DCMTK_INCLUDE_DIRS})
target_link_libraries(main LINK_PRIVATE ${DCMTK_LIBRARIES} z)

