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
find_library(M_LIBRARY m)
find_library(ERFA_LIBRARY erfa)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -march=native -Wall -Wextra")

if (CSPICE_FOUND)
    add_library(psrtools "barycentre.c;dm.c;vec.c")
    add_executable(bary2topo "bary2topo.c;barycentre.c;vec.c")
    include_directories(${CSPICE_INCLUDE_DIR})
    target_link_libraries(psrtools ${M_LIBRARY} ${CSPICE_LIBRARY})
    target_link_libraries(bary2topo ${M_LIBRARY} ${CSPICE_LIBRARY})
    set_target_properties(psrtools PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS}" PUBLIC_HEADER "dm.h;vec.h;barycentre.h")
else (CSPICE_FOUND)
    add_library(psrtools "dm.c;vec.c")
endif (CSPICE_FOUND)

add_executable(dmdelay "dmdelay.c;dm.c")
set_target_properties(dmdelay PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS}")

add_executable(angsep "angsep.c")
target_link_libraries(angsep ${M_LIBRARY} ${ERFA_LIBRARY})

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/dmdelay gps2mjd ${CMAKE_CURRENT_BINARY_DIR}/angsep DESTINATION bin)

if (CSPICE_FOUND)
    install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/bary2topo DESTINATION bin)
endif(CSPICE_FOUND)

install(TARGETS psrtools
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include/psrtools)
