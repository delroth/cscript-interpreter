cmake_minimum_required(VERSION 2.8)
project(cscript-interpreter)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++0x -Wall -Wextra -Werror)
endif()

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(cscript
               cscript.cc
               cscript.hh
               endian.hh
               main.cc)
