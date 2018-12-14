include (ACGCommon)

include_directories (
  ../../..
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# collect all header and source files
acg_append_files (headers "*.hh" .)
acg_append_files (sources "*.cc" .)

acg_add_executable (mconvert ${headers} ${sources})

target_link_libraries (mconvert
  OpenMeshCore
  OpenMeshTools
)

