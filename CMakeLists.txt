project (GeographicLib-C C)

# Version information
set (PROJECT_VERSION_MAJOR 2)
set (PROJECT_VERSION_MINOR 0)
set (PROJECT_VERSION_PATCH 0)
set (PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
if (PROJECT_VERSION_PATCH GREATER 0)
  set (PROJECT_VERSION "${PROJECT_VERSION}.${PROJECT_VERSION_PATCH}")
endif ()

cmake_minimum_required (VERSION 3.13.0)

option (CONVERT_WARNINGS_TO_ERRORS "Convert warnings into errors?" OFF)
option (BUILD_DOCUMENTATION "Use doxygen to create the documentation" OFF)

# Set a default build type for single-configuration cmake generators if
# no build type is set.
if (NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE Release)
endif ()

# We require C99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Make the compiler more picky.
if (MSVC)
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
else ()
  set (CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-array-bounds -pedantic")
  if (NOT CMAKE_C_COMPILER_ID STREQUAL "Intel")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wfloat-conversion")
  endif ()
endif ()

# Tell Intel compiler to do arithmetic accurately.  This is needed to
# stop the compiler from ignoring parentheses in expressions like
# (a + b) + c and from simplifying 0.0 + x to x (which is wrong if
# x = -0.0).
if (CMAKE_C_COMPILER_ID STREQUAL "Intel")
  if (MSVC)
    set (CMAKE_C_FLAGS
      "${CMAKE_C_FLAGS} /fp:precise /Qdiag-disable:11074,11076")
  else ()
    set (CMAKE_C_FLAGS
      "${CMAKE_C_FLAGS} -fp-model precise -diag-disable=11074,11076")
  endif ()
endif ()

if (CONVERT_WARNINGS_TO_ERRORS)
  if (MSVC)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /WX")
  else ()
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")
  endif ()
endif ()

set (LIBNAME geodc)
set (TOOLS direct inverse planimeter)
set (TESTS geodtest geodsigntest)

if (MSVC OR CMAKE_CONFIGURATION_TYPES)
  # Add _d suffix for your debug versions of the tools
  set_target_properties (${TOOLS} PROPERTIES DEBUG_POSTFIX _d)
endif ()

add_subdirectory (src)
add_subdirectory (tools)
add_subdirectory (tests)

enable_testing ()
# Run the test suite
add_test (NAME geodtest COMMAND geodtest)
add_test (NAME signtest COMMAND geodsigntest)

# The documentation depends on doxygen.
if (BUILD_DOCUMENTATION)
  set (DOXYGEN_SKIP_DOT ON)
  # Version 1.8.7 or later needed for &hellip;
  find_package (Doxygen 1.8.7 REQUIRED)
  add_subdirectory (doc)
endif ()

# The configuration of CPack is via variables that need to be set before
# the include (CPack).
set (CPACK_PACKAGE_CONTACT charles@karney.com)
set (CPACK_PACKAGE_VENDOR "GeographicLib-C")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY
  "GeographicLib C library and documentation")
# The list of files to be excluded from the source distribution.
set (CPACK_SOURCE_IGNORE_FILES
  "#"
  "~\$"
  "/\\\\.git"
  "${PROJECT_SOURCE_DIR}/BUILD")
set (CPACK_SOURCE_GENERATOR TGZ)

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

set (CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME}-${PROJECT_VERSION}")
set (CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY}")

include (CPack)
