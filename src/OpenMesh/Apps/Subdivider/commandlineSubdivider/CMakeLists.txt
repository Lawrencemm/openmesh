include (ACGCommon)

include_directories (
  ../../../..
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# collect all header and source files
set (sources
  ../subdivider.cc
)

acg_add_executable (commandlineSubdivider ${sources})

target_link_libraries (commandlineSubdivider
  OpenMeshCore
  OpenMeshTools
)

