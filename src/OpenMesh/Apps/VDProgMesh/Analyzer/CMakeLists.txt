include (ACGCommon)

include_directories (
  ../../../..
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# collect all header and source files
set (sources
  ./vdpmanalyzer.cc
)

acg_add_executable (Analyzer ${sources})

target_link_libraries (Analyzer
  OpenMeshCore
  OpenMeshTools
)

