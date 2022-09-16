#!cmake .
#
# This works with SystemC versions 2.3.2 and later, which have support for
# cmake and specify SystemC_CXX_STANDARD.
# 
# REQUIREMENTS:
# - Adjust ../../setup.profile if needed

cmake_minimum_required( VERSION 3.20 )

project( dataperf VERSION 1.2 DESCRIPTION "SystemC data type performance evaluation" LANGUAGES CXX )

list( PREPEND CMAKE_MODULE_PATH "$ENV{PROJECT_DIR}/cmake" )
include( sc-project_defaults )

add_executable( "${PROJECT_NAME}" )
target_sources( "${PROJECT_NAME}" PRIVATE dataperf.cpp )
add_test( NAME "${PROJECT_NAME}" COMMAND "${PROJECT_NAME}" )

# vim:syntax=cmake:nospell
