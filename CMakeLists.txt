cmake_minimum_required( VERSION 3.22.1 )

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

option( STDEXEC_EXAMPLE_USE_CUDA  "Use CUDA GPU scheduler" OFF )

project( stdexec-example LANGUAGES CXX )


if( STDEXEC_EXAMPLE_USE_CUDA )
    enable_language( CUDA )
endif()

add_subdirectory( thirdparty/stdexec )

add_executable( main source/main.cpp )
target_link_libraries( main PRIVATE STDEXEC::stdexec stdexec_executable_flags )

if( STDEXEC_EXAMPLE_USE_CUDA )
    target_compile_definitions( main PRIVATE -DSTDEXEC_EXAMPLE_USE_CUDA )
endif()
