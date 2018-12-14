include (ACGCommon)

include_directories (
  ../../../..
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${GLUT_INCLUDE_DIR}
)

# collect all header and source files
acg_append_files (headers "*.hh" .)
acg_append_files (sources "*.cc" .)

list (APPEND sources "../../QtViewer/QGLViewerWidget.cc")
list (APPEND sources "../../QtViewer/MeshViewerWidgetT.cc")

list (APPEND headers "../../QtViewer/QGLViewerWidget.hh")
list (APPEND headers "../../QtViewer/MeshViewerWidgetT.hh")

# remove template cc files from source file list
acg_drop_templates (sources)

if (WIN32)
  acg_add_executable (Synthesizer WIN32 ${sources} ${headers})
else ()
  acg_add_executable (Synthesizer ${sources} ${headers})
endif ()

target_link_libraries (Synthesizer
  OpenMeshCore
  OpenMeshTools
  Qt5::OpenGL
  ${OPENGL_LIBRARIES}
  ${GLUT_LIBRARIES}
)
