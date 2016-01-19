cmake_minimum_required(VERSION 3.0)

project(txt_quiz)

enable_testing()

set(CMAKE_VERBOSE_MAKEFILE ON)

# remove 'lib' prefix for shared libraries on Windows
if (WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

# once for all subprojects
add_compile_options(-std=c++14 -Wall)

add_subdirectory(main) # middle executable (depends on INCLUDES: Boost LIBS: Boost)
add_subdirectory(test)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if (DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/doxygen/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif ()








