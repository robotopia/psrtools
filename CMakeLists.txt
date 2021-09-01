cmake_minimum_required (VERSION 3.15)
#cmake_policy(SET CMP0012 NEW)
#cmake_policy(SET CMP0048 NEW)

# Set up version number
execute_process(
  COMMAND bash -c "git describe --tags --long | sed 's/-/./' | sed 's/-g/_/'"
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE PSRTOOLS_VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

message("PSRTools ${PSRTOOLS_VERSION}")
message("Install directory: ${CMAKE_INSTALL_PREFIX}")

project (psrtools LANGUAGES C)

add_definitions(-DPSRTOOLS_VERSION="${PSRTOOLS_VERSION}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(CSPICE)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -march=native -Wall -Wextra")

if (CSPICE_FOUND)
    add_library(psrtools "barycentre.c;dm.c;vec.c")
    include_directories(${CSPICE_INCLUDE_DIR})
    target_link_libraries(psrtools ${CSPICE_LIBRARY})
else (CSPICE_FOUND)
    add_library(psrtools "dm.c;vec.c")
endif (CSPICE_FOUND)

add_executable(dmdelay "dmdelay.c;dm.c")

install(PROGRAMS dmdelay DESTINATION bin)
install(FILES gps2mjd DESTINATION bin)
install(TARGETS psrtools ARCHIVE DESTINATION lib)
