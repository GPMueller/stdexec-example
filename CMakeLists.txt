cmake_minimum_required( VERSION 3.22.1 )

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

project( stdexec-example LANGUAGES CXX )

add_subdirectory( thirdparty/stdexec )

add_executable( main source/main.cpp )
target_link_libraries( main PUBLIC STDEXEC::stdexec stdexec_executable_flags )
