include (ACGCommon)

include_directories (
  ../../../..
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# collect all header and source files
set (sources
  ../decimater.cc
)

acg_add_executable (commandlineDecimater ${sources})

target_link_libraries (commandlineDecimater
  OpenMeshCore
  OpenMeshTools
)

