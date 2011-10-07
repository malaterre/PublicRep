SET(EXE_DIR ".")
IF(EXECUTABLE_OUTPUT_PATH)
  SET(EXE_DIR "${EXECUTABLE_OUTPUT_PATH}")
ENDIF(EXECUTABLE_OUTPUT_PATH)


set(DEBIAN_TESTS 
  "${CMAKE_CURRENT_SOURCE_DIR}/cmath.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/complex.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/tr1_type_traits.cc"
)

FOREACH(test ${DEBIAN_TESTS})
  GET_FILENAME_COMPONENT(name "${test}" NAME)
  GET_FILENAME_COMPONENT(name_we "${test}" NAME_WE)
  ADD_TEST(${name}
    ${EXE_DIR}/gccxml ${gccxml_dashI_args} ${test} -fxml=${name}.gcc.xml
  )
ENDFOREACH(test)

