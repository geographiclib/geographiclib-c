if (NOT MSVC)
  set (MATH_LIBS m)
endif ()

foreach (TEST ${TESTS})
  add_executable (${TEST} ${TEST}.c)
  target_link_libraries (${TEST} ${LIBNAME} ${MATH_LIBS})
endforeach ()
