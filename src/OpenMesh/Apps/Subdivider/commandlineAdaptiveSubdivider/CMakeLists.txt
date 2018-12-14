include (ACGCommon)

include_directories (
  ../../../..
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# collect all header and source files
set (sources
  ../adaptive_subdivider.cc
)

acg_add_executable (commandlineAdaptiveSubdivider ${sources})

target_link_libraries (commandlineAdaptiveSubdivider
  OpenMeshCore
  OpenMeshTools
)

