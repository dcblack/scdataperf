#!cmake .
cmake_minimum_required ( VERSION 3.20 )

message( "Setting up cmake" )

# Header style guard for multiple inclusion protection
if( DEFINED PROJECT_DEFAULTS )
  return()
endif()
set( PROJECT_DEFAULTS ON )

if( DEFINED ENV{PROJECT_DIR} )
  set( PROJECT_DIRS "$ENV{PROJECT_DIR}/externs;$ENV{APPS}" )
  foreach( _dir ${PROJECT_DIRS} )
     if( EXISTS "${_dir}" )
       list( APPEND CMAKE_PREFIX_PATH "${_dir}" )
     endif()
  endforeach()
  list( REMOVE_DUPLICATES CMAKE_PREFIX_PATH )
  include_directories( . "$ENV{PROJECT_DIR}" )
else()
  message( WARNING "PROJECT_DIR environment variable was not defined" )
endif()

#-------------------------------------------------------------------------------
# Increase sensitivity to all warnings
#-------------------------------------------------------------------------------
include( strict )

#------------------------------------------------------------------------------
# Choose minimum C++ standard for remainder of code
#------------------------------------------------------------------------------
set( SystemC_CXX_STANDARD        17 CACHE STRING "C++ standard for SystemC compilation." )
set( CMAKE_CXX_STANDARD          17 CACHE STRING "C++ standard to build all targets." )
set( CMAKE_CXX_STANDARD_REQUIRED 17 CACHE BOOL   "The CMAKE_CXX_STANDARD selected C++ standard is a requirement." )
set( CMAKE_C_STANDARD            11 CACHE STRING "C standard to build all targets." )
set( CMAKE_C_STANDARD_REQUIRED   11 CACHE BOOL   "The CMAKE_CXX_STANDARD selected C standard is a requirement." )

include( set_target )

enable_testing()

#------------------------------------------------------------------------------
# SystemC specifics
#------------------------------------------------------------------------------
if( DEFINED ENV{SYSTEMC_HOME} )
  include( systemc )
else()
  message( SEND_ERROR "SYSTEMC_HOME environment variable needs to be setup" )
endif()

# Simplify life
add_compile_definitions( SC_INCLUDE_FX SC_INCLUDE_DYNAMIC_PROCESSES )

# vim:nospell
