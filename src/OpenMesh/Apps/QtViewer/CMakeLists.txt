include (ACGCommon)

include_directories (
  ../../..
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${GLUT_INCLUDE_DIR}
)

# source code directories
set (directories 
  .
)

# collect all header and source files
acg_append_files (headers "*.hh" ${directories})
acg_append_files (sources "*.cc" ${directories})

# remove template cc files from source file list
acg_drop_templates (sources)

if (WIN32)
  acg_add_executable (QtViewer WIN32 ${sources} ${headers})
else ()
  acg_add_executable (QtViewer ${sources} ${headers})
endif ()

target_link_libraries (QtViewer
  OpenMeshCore
  OpenMeshTools
  Qt5::OpenGL
  ${OPENGL_LIBRARIES}
  ${GLUT_LIBRARIES}
)

