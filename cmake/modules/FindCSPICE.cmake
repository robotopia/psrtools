# - Try to find CSPICE code.
# Variables used by this module:
#  CSPICE_ROOT     - CSPICE root directory
# Variables defined by this module:
#  CSPICE_FOUND        - system has CSPICE
#  CSPICE_INCLUDE_DIR  - the CSPICE include directory (cached)
#  CSPICE_INCLUDE_DIRS - the CSPICE include directories
#                         (identical to CSPICE_INCLUDE_DIR)
#  CSPICE_LIBRARY      - the CSPICE library (cached)
#  CSPICE_LIBRARIES    - the CSPICE libraries
#  CSPICE_HDF5         - the full embedded element pattern HDF5 file

message("Finding CSPICE")

set(CSPICE_ROOT $ENV{CSPICE})

if(NOT DEFINED CSPICE_ROOT)
    message(STATUS "Warning CSPICE_ROOT not set: will try and find it ")
else(NOT DEFINED CSPICE_ROOT)
    message(STATUS "CSPICE_ROOT = ${CSPICE_ROOT}")
endif(NOT DEFINED CSPICE_ROOT)

if(NOT CSPICE_FOUND)

    find_path(CSPICE_INCLUDE_DIR SpiceUsr.h
    HINTS ${CSPICE_ROOT} PATH_SUFFIXES /include)
    find_library(CSPICE_LIBRARY cspice.a
    HINTS ${CSPICE_ROOT} PATH_SUFFIXES lib )

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(CSPICE DEFAULT_MSG
    CSPICE_LIBRARY CSPICE_INCLUDE_DIR)

endif(NOT CSPICE_FOUND)

if (CSPICE_FOUND)
    message (STATUS "Found CSPICE (${CSPICE_LIBRARY})")
else (CSPICE_FOUND)
    message( STATUS "CSPICE not found" )
endif (CSPICE_FOUND)

