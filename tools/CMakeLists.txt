if (NOT MSVC)
  set (MATH_LIBS m)
endif ()

foreach (TOOL ${TOOLS})
  add_executable (${TOOL} ${TOOL}.c)
  target_link_libraries (${TOOL} ${LIBNAME} ${MATH_LIBS})
endforeach ()
