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

include (CheckCSourceCompiles)
if (MSVC)
  set (CMAKE_REQUIRED_FLAGS "${CMAKE_C_FLAGS} /WX")
else ()
  set (CMAKE_REQUIRED_LIBRARIES m)
  set (CMAKE_REQUIRED_FLAGS "${CMAKE_C_FLAGS} -Werror")
endif ()
# Check whether the C99 math function: hypot, atanh, etc. are available.
check_c_source_compiles (
  "#include <math.h>
int main() {
  int q = 0;
  return (int)(hypot(3.0, 4.0) + atanh(0.8) + copysign(1.0, -0.0) +
               cbrt(8.0) + remainder(100.0, 90.0) +
               remquo(100.0, 90.0, &q));
}\n" C99_MATH)
if (NOT C99_MATH)
  message (FATAL_ERROR "Missing C99 math functions")
endif ()

if (CONVERT_WARNINGS_TO_ERRORS)
  if (MSVC)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /WX")
  else ()
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")
  endif ()
endif ()

set (LIBNAME geodc)
set (TOOLS direct inverse planimeter geodtest)

if (MSVC OR CMAKE_CONFIGURATION_TYPES)
  # Add _d suffix for your debug versions of the tools
  set_target_properties (${TOOLS} PROPERTIES
    DEBUG_POSTFIX _d)
endif ()

add_subdirectory (src)
add_subdirectory (tools)

enable_testing ()
# Run the test suite
add_test (NAME geodtest COMMAND geodtest)

# The documentation depends on doxygen.
if (BUILD_DOCUMENTATION)
  set (DOXYGEN_SKIP_DOT ON)
  # Version 1.8.7 or later needed for &hellip;
  find_package (Doxygen 1.8.7 REQUIRED)
  add_subdirectory (doc)
endif ()
