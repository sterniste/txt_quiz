cmake_minimum_required(VERSION 3.0)

project(main CXX)

add_compile_options(-DLEVEL_LOGGING)

file(GLOB CC_FILES *.cc)

# prefer static to dynamic libraries
set(CMAKE_FIND_LIBRARY_SUFFIXES .a)

find_package(Boost 1.58.0 REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.58.0 COMPONENTS log log_setup program_options filesystem system thread REQUIRED)
find_package(Threads REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(txt_quiz ${CC_FILES})

find_package(Boost COMPONENTS system REQUIRED)

target_link_libraries(txt_quiz ${Boost_SYSTEM_LIBRARY})
