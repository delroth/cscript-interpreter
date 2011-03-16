cmake_minimum_required(VERSION 2.8)
project(cscript-interpreter)

enable_testing()

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++0x -Wall -Wextra -Werror -g -ggdb3)
    add_definitions(-DSOURCE_DIR="${CMAKE_SOURCE_DIR}")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(Boost REQUIRED COMPONENTS iostreams)
include_directories(${Boost_INCLUDE_DIRS})
link_directories("${Boost_LIBRARY_DIRS}")

include_directories(lib)

add_subdirectory(lib)
add_subdirectory(tests)
add_subdirectory(frontend)
