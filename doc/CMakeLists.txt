configure_file (doxyfile.in doxyfile @ONLY)
file (GLOB CSOURCES ../src/*.[ch] ../tools/*.c)
add_custom_target (doc ALL
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/html/index.html)
add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/html/index.html
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/doxyfile geodesic-c.dox ${CSOURCES}
  COMMAND ${DOXYGEN_EXECUTABLE} doxyfile > doxygen.log
  COMMENT "Generating C documentation tree")
add_custom_target (distrib-doc DEPENDS doc
  COMMAND
  rsync -a --delete
  html/ /home/ckarney/web/geographiclib-web/htdocs/C/${PROJECT_VERSION}/
  )
