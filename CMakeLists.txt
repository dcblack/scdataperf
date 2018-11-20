#!cmake .
# This works with SystemV versions 2.3.2 and later, which have support for
# cmake and specify SystemC_CXX_STANDARD.
# 
# REQUIREMENTS:
#   Define SYSTEMC_HOME to point to install directory of SystemC (not source)

cmake_minimum_required(VERSION 3.11)

project(dataperf CXX)
set(TARGET_EXECUTABLE $<TARGET_FILE_NAME:dataperf>)
set(TARGET_NAME dataperf)
set(default_build_type "Debug")
include(systemc.cmake)

add_compile_definitions(SC_INCLUDE_FX SC_INCLUDE_DYNAMIC_PROCESSES)

add_executable(dataperf
  dataperf.cpp
)
