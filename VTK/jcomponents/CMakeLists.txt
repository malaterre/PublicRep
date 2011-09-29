cmake_minimum_required(VERSION 2.8)
project(flicker)

# JNI bindings:
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS}
  #/usr/include/vtk-5.6/
  #/usr/include/vtk-5.8/
  )

add_library(transJNI SHARED trans.cxx)
target_link_libraries(transJNI
    ${JNI_LIBRARIES}
    #    vtkIO
    #    vtkCommon
    #/usr/lib/jni/libvtkCommonJava.so
    /home/mathieu/Kitware/VTK-gcc/bin/libvtkCommonJava.so
  )


# Java stuff
find_package(Java 1.5 REQUIRED)
set(EXECUTABLE_OUTPUT_PATH ${flicker_BINARY_DIR}/bin CACHE PATH "Single output directory for building all executables.")
set(LIBRARY_OUTPUT_PATH    ${flicker_BINARY_DIR}/bin CACHE PATH "Single output directory for building all libraries.")

add_custom_command(
  OUTPUT ${LIBRARY_OUTPUT_PATH}/MyFrame.class
  COMMAND ${JAVA_COMPILE} ARGS -source 1.5 "${CMAKE_CURRENT_SOURCE_DIR}/*.java"  -d ${EXECUTABLE_OUTPUT_PATH} -classpath /home/mathieu/Kitware/VTK-gcc/bin/vtk.jar:.

  #  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/MyFrame.java
)

add_custom_target(BLA ALL
  DEPENDS 
  ${LIBRARY_OUTPUT_PATH}/MyFrame.class
)
