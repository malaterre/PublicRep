cmake_minimum_required(VERSION 2.8)
project(test2 C)

SET(LIB_PROPERTIES
  VERSION "1.0"
  SOVERSION "1"
)

add_library(lib1 MODULE foo.c)
add_library(lib2 SHARED bla.c)
#add_library(lib3 SHARED bar.c)
target_link_libraries(lib1 lib2)
target_link_libraries(lib2 -lm)
set_property(TARGET lib1 PROPERTY NO_SONAME 1)
set_target_properties(lib2 PROPERTIES ${LIB_PROPERTIES} LINK_INTERFACE_LIBRARIES "")
#set_target_properties(lib3 PROPERTIES ${LIB_PROPERTIES} LINK_INTERFACE_LIBRARIES "")

install(TARGETS lib1 lib2
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
)
