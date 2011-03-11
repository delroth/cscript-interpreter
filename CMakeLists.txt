cmake_minimum_required(VERSION 2.8)
project(cscript-interpreter)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++0x -Wall -Wextra -Werror)
endif()

find_package(Boost REQUIRED COMPONENTS iostreams)
include_directories(${Boost_INCLUDE_DIRS})
link_directories("${Boost_LIBRARY_DIRS}")

add_executable(cscript
               cscript.cc
               cscript.hh
               endian.hh
               exception.hh
               instruction-dispatcher.cc
               instruction-dispatcher.hh
               instruction-handler.hh
               main.cc
               stack.hh
               thread-context.hh)
target_link_libraries(cscript ${Boost_LIBRARIES})
