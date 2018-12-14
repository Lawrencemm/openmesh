include (ACGCommon)

include_directories (
  ../../../..
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# collect all header and source files
set (sources
  ./mkbalancedpm.cc
)

acg_add_executable (mkbalancedpm ${sources})

target_link_libraries (mkbalancedpm
  OpenMeshCore
  OpenMeshTools
)

