include (ACGCommon)

include_directories (
  ../../../..
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${GLUT_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)

# source code directories
set (directories 
  ../../QtViewer
  ../
)

# collect all header and source files
acg_append_files (headers "*.hh" ${directories})

set (sources
  ../../QtViewer/QGLViewerWidget.cc
  ../../QtViewer/MeshViewerWidgetT.cc
  ../DecimaterViewerWidget.cc
  ../decimaterviewer.cc
)

# remove template cc files from source file list
acg_drop_templates (sources)

if (WIN32)
  acg_add_executable (DecimaterGui WIN32 ${sources} ${headers})
  # link to qtmain library to get WinMain function for a non terminal app
  target_link_libraries (DecimaterGui ${QT_QTMAIN_LIBRARY})
else ()
  acg_add_executable (DecimaterGui ${sources} ${headers} ) 
endif ()

target_link_libraries (DecimaterGui
  OpenMeshCore
  OpenMeshTools
  ${QT_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${GLUT_LIBRARIES}
)

