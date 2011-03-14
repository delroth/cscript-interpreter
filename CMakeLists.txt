cmake_minimum_required(VERSION 2.8)
project(cscript-interpreter)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++0x -Wall -Wextra -Werror)
endif()

find_package(Boost REQUIRED COMPONENTS iostreams)
include_directories(${Boost_INCLUDE_DIRS})
link_directories("${Boost_LIBRARY_DIRS}")

include_directories(lib)

add_subdirectory(lib)
add_subdirectory(frontend)
