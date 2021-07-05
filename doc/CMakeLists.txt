configure_file (doxyfile-c.in doxyfile-c @ONLY)
file (GLOB CSOURCES ../src/*.[ch] ../tools/*.c)
add_custom_target (doc ALL
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/html/index.html)
add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/html/index.html
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/doxyfile-c geodesic-c.dox ${CSOURCES}
  COMMAND ${DOXYGEN_EXECUTABLE} doxyfile-c > doxygen-c.log
  COMMENT "Generating C documentation tree")
