cmake_minimum_required(VERSION 3.8)
project(str)

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

add_library(thelib SHARED myfile.cxx)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}")
find_package(CSharp REQUIRED)
include(${CSharp_USE_FILE})
set_source_files_properties(demo.i PROPERTIES CPLUSPLUS ON)

#set(DEMO_JAVA_HOME ${CMAKE_CURRENT_BINARY_DIR}/java/demo)
#make_directory(${DEMO_JAVA_HOME})
#set(CMAKE_SWIG_OUTDIR "${DEMO_JAVA_HOME}")

#set(CMAKE_SWIG_FLAGS "-package demo")
#separate_arguments(CMAKE_SWIG_FLAGS)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)

swig_add_library(demo LANGUAGE csharp SOURCES demo.i)
swig_link_libraries(demo thelib
  #  ${JNI_LIBRARIES}
  )

set(EXECUTABLE_OUTPUT_PATH ${str_BINARY_DIR}/bin CACHE PATH "Single output directory for building all executables.")
set(LIBRARY_OUTPUT_PATH    ${str_BINARY_DIR}/bin CACHE PATH "Single output directory for building all libraries.")

#add_custom_command(
#  OUTPUT ${LIBRARY_OUTPUT_PATH}/demo.jar
#  COMMAND ${JAVA_COMPILE} ARGS -source 1.5 "demo/*.java"
#  COMMAND ${JAVA_ARCHIVE} ARGS cvf ${LIBRARY_OUTPUT_PATH}/demo.jar demo/*.class
#  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/java
#  DEPENDS "${swig_generated_file_fullname}"
#)
#
#add_custom_command(
#  OUTPUT ${LIBRARY_OUTPUT_PATH}/testdemo.class
#  COMMAND ${JAVA_COMPILE} ARGS -source 1.5 ${CMAKE_CURRENT_SOURCE_DIR}/testdemo.java -classpath ${LIBRARY_OUTPUT_PATH}/demo.jar -d ${EXECUTABLE_OUTPUT_PATH}
#  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#  DEPENDS ${LIBRARY_OUTPUT_PATH}/demo.jar
#)
#
#add_custom_target(BLA ALL
#  DEPENDS ${LIBRARY_OUTPUT_PATH}/demo.jar
#  ${LIBRARY_OUTPUT_PATH}/testdemo.class
#)

# building HelloCSharpWorld:
add_custom_command(
  OUTPUT ${str_EXECUTABLE_DIR}/testdemo.exe
  COMMAND ${CMAKE_CSHARP_COMPILER} ARGS "/r:${str_BINARY_DIR}/gdcm-sharp.dll" "/out:${str_BINARY_DIR}/HelloCsharpWorld.exe" ${CMAKE_CURRENT_SOURCE_DIR}/testdemo.cs
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  DEPENDS ${str_BINARY_DIR}/demo.dll
  ${CMAKE_CURRENT_SOURCE_DIR}/testdemo.cs
  COMMENT "Create testdemo.exe"
  )
