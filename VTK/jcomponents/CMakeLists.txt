cmake_minimum_required(VERSION 2.8)
project(flicker)

# JNI bindings:
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

add_library(transJNI SHARED trans.cxx)
target_link_libraries(transJNI
  ${JNI_LIBRARIES}
  )


# Java stuff
find_package(Java 1.5 REQUIRED)
set(EXECUTABLE_OUTPUT_PATH ${flicker_BINARY_DIR}/bin CACHE PATH "Single output directory for building all executables.")
set(LIBRARY_OUTPUT_PATH    ${flicker_BINARY_DIR}/bin CACHE PATH "Single output directory for building all libraries.")

add_custom_command(
  OUTPUT ${LIBRARY_OUTPUT_PATH}/MyFrame.class
  COMMAND ${JAVA_COMPILE} ARGS -source 1.5 "${CMAKE_CURRENT_SOURCE_DIR}/*.java"  -d ${EXECUTABLE_OUTPUT_PATH} # -classpath ${LIBRARY_OUTPUT_PATH}/demo.jar
  #  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  #DEPENDS ${LIBRARY_OUTPUT_PATH}/demo.jar
)

add_custom_target(BLA ALL
  DEPENDS 
  ${LIBRARY_OUTPUT_PATH}/MyFrame.class
)
