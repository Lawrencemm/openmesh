#unset cached qt variables which are set by all qt versions. version is the major number of the qt version (e.g. 4 or 5, not 4.8)
macro (acg_unset_qt_shared_variables version)
  if (ACG_INTERNAL_QT_LAST_VERSION)
    if (NOT ${ACG_INTERNAL_QT_LAST_VERSION} EQUAL ${version})
      unset(QT_BINARY_DIR)
      unset(QT_PLUGINS_DIR)
      unset(ACG_INTERNAL_QT_LAST_VERSION)
    endif()
  endif()
  set (ACG_INTERNAL_QT_LAST_VERSION "${version}" CACHE INTERNAL "Qt Version, which was used on the last time")
endmacro()

macro (acg_qt5)

   if(POLICY CMP0020)
     # Automatically link Qt executables to qtmain target on Windows
     cmake_policy(SET CMP0020 NEW)
   endif(POLICY CMP0020)
  #if (NOT QT5_FOUND)

    #set (QT_MIN_VERSION ${ARGN})

  #try to find qt5 automatically
  #for custom installation of qt5, dont use any of these variables
  set (QT5_INSTALL_PATH "" CACHE PATH "Path to Qt5 directory which contains lib and include folder")

  if (EXISTS "${QT5_INSTALL_PATH}")
    set (CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${QT5_INSTALL_PATH}")
    set (QT5_INSTALL_PATH_EXISTS TRUE)
  endif(EXISTS "${QT5_INSTALL_PATH}")
  
  set(QT5_FINDER_FLAGS "" CACHE STRING "Flags for the Qt finder e.g.
                                                       NO_DEFAULT_PATH if no system installed Qt shall be found")
  # compute default search paths
  set(SUPPORTED_QT_VERSIONS 5.11 5.10 5.9 5.8 5.7 5.6)
  foreach (suffix gcc_64 clang_64)
     foreach(version ${SUPPORTED_QT_VERSIONS})
         list(APPEND QT_DEFAULT_PATH "~/sw/Qt/${version}/${suffix}")
     endforeach()
  endforeach()

  find_package (Qt5Core PATHS ${QT_DEFAULT_PATH} ${QT5_FINDER_FLAGS})
  if(Qt5Core_FOUND)

      if(Qt5Core_VERSION) # use the new version variable if it is set
          set(Qt5Core_VERSION_STRING ${Qt5Core_VERSION})
      endif(Qt5Core_VERSION)

      string(REGEX REPLACE "^([0-9]+)\\.[0-9]+\\.[0-9]+.*" "\\1" QT_VERSION_MAJOR "${Qt5Core_VERSION_STRING}")
      string(REGEX REPLACE "^[0-9]+\\.([0-9]+)\\.[0-9]+.*" "\\1" QT_VERSION_MINOR "${Qt5Core_VERSION_STRING}")
      string(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" QT_VERSION_PATCH "${Qt5Core_VERSION_STRING}")

    find_package (Qt5Widgets QUIET PATHS ${QT_DEFAULT_PATH} ${QT5_FINDER_FLAGS})
    find_package (Qt5Gui QUIET PATHS ${QT_DEFAULT_PATH} ${QT5_FINDER_FLAGS})
    find_package (Qt5OpenGL QUIET PATHS ${QT_DEFAULT_PATH} ${QT5_FINDER_FLAGS})
    find_package (Qt5Network QUIET PATHS ${QT_DEFAULT_PATH} ${QT5_FINDER_FLAGS})

    if (NOT WIN32 AND NOT APPLE)
       find_package (Qt5X11Extras QUIET PATHS ${QT_DEFAULT_PATH} ${QT5_FINDER_FLAGS})
    endif ()

    if (Qt5Core_FOUND AND Qt5Widgets_FOUND AND Qt5Gui_FOUND AND Qt5OpenGL_FOUND AND Qt5Network_FOUND )
          set (QT5_FOUND TRUE)
    endif()

  endif(Qt5Core_FOUND)
  
  if (QT5_FOUND)   
    acg_unset_qt_shared_variables(5)
  
    #set plugin dir
    list(GET Qt5Gui_PLUGINS 0 _plugin)
    if (_plugin)
      get_target_property(_plugin_full ${_plugin} LOCATION)
      get_filename_component(_plugin_dir ${_plugin_full} PATH)
    set (QT_PLUGINS_DIR "${_plugin_dir}/../" CACHE PATH "Path to the qt plugin directory")
    elseif(QT5_INSTALL_PATH_EXISTS)
      set (QT_PLUGINS_DIR "${QT5_INSTALL_PATH}/plugins/" CACHE PATH "Path to the qt plugin directory")
    elseif()
      set (QT_PLUGINS_DIR "QT_PLUGIN_DIR_NOT_FOUND" CACHE PATH "Path to the qt plugin directory")
    endif(_plugin)

    #set binary dir for fixupbundle
    if(QT5_INSTALL_PATH_EXISTS)
      set(_QT_BINARY_DIR "${QT5_INSTALL_PATH}/bin")
    else()
      get_target_property(_QT_BINARY_DIR ${Qt5Widgets_UIC_EXECUTABLE} LOCATION)
      get_filename_component(_QT_BINARY_DIR ${_QT_BINARY_DIR} PATH)
    endif(QT5_INSTALL_PATH_EXISTS)
    
    set (QT_BINARY_DIR "${_QT_BINARY_DIR}" CACHE PATH "Qt5 binary Directory")
    mark_as_advanced(QT_BINARY_DIR)
    
    set (CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
  
    include_directories(${Qt5Core_INCLUDE_DIRS})
    include_directories(${Qt5Widgets_INCLUDE_DIRS})
    include_directories(${Qt5Gui_INCLUDE_DIRS})
    include_directories(${Qt5OpenGL_INCLUDE_DIRS})
    include_directories(${Qt5Network_INCLUDE_DIRS})
    add_definitions(${Qt5Core_DEFINITIONS})
    add_definitions(${Qt5Widgets_DEFINITIONS})
    add_definitions(${Qt5Gui_DEFINITIONS})
    add_definitions(${Qt5OpenGL_DEFINITIONS})
    add_definitions(${Qt5Network_DEFINITIONS})
    
    if (Qt5X11Extras_FOUND)
            include_directories(${Qt5X11Extras_INCLUDE_DIRS})
            add_definitions(${Qt5X11Extras_DEFINITIONS})
    endif ()
    
    if ( NOT MSVC )
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    endif()

    set (QT_LIBRARIES ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES}
      ${Qt5Gui_LIBRARIES} ${Qt5OpenGL_LIBRARIES} ${Qt5Network_LIBRARIES} )
      
    if (Qt5X11Extras_FOUND)
            list (APPEND QT_LIBRARIES ${Qt5X11Extras_LIBRARIES})
        endif ()
     
    if (MSVC)
      set (QT_LIBRARIES ${QT_LIBRARIES} ${Qt5Core_QTMAIN_LIBRARIES})
      endif()

	  #add_definitions(-DQT_NO_OPENGL)

	  #adding QT_NO_DEBUG to all release modes. 
	  #  Note: for multi generators like msvc you cannot set this definition depending of
	  #  the current build type, because it may change in the future inside the ide and not via cmake
	  if (MSVC_IDE)
	    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /DQT_NO_DEBUG")
	    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /DQT_NO_DEBUG")
		
		set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_RELEASE} /DQT_NO_DEBUG")
	    set(CMAKE_CXX_FLAGS_MINSITEREL "${CMAKE_C_FLAGS_RELEASE} /DQT_NO_DEBUG")
		
		set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELEASE} /DQT_NO_DEBUG")
	    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELEASE} /DQT_NO_DEBUG")
	  else(MSVC_IDE)
	    if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
	      add_definitions(-DQT_NO_DEBUG)
	    endif()
      endif(MSVC_IDE)

    endif ()
endmacro ()

# generate moc targets for sources in list
macro (acg_qt5_automoc moc_SRCS)
  qt5_get_moc_flags (_moc_INCS)
  
  list(REMOVE_DUPLICATES _moc_INCS)

  set (_matching_FILES )
  foreach (_current_FILE ${ARGN})

     get_filename_component (_abs_FILE ${_current_FILE} ABSOLUTE)
     # if "SKIP_AUTOMOC" is set to true, we will not handle this file here.
     # here. this is required to make bouic work correctly:
     # we need to add generated .cpp files to the sources (to compile them),
     # but we cannot let automoc handle them, as the .cpp files don't exist yet when
     # cmake is run for the very first time on them -> however the .cpp files might
     # exist at a later run. at that time we need to skip them, so that we don't add two
     # different rules for the same moc file
     get_source_file_property (_skip ${_abs_FILE} SKIP_AUTOMOC)

     if ( NOT _skip AND EXISTS ${_abs_FILE} )

        file (READ ${_abs_FILE} _contents)

        get_filename_component (_abs_PATH ${_abs_FILE} PATH)

        string (REGEX MATCHALL "Q_OBJECT" _match "${_contents}")
        if (_match)
            get_filename_component (_basename ${_current_FILE} NAME_WE)
            set (_header ${_abs_FILE})
            set (_moc    ${CMAKE_CURRENT_BINARY_DIR}/moc_${_basename}.cpp)

            add_custom_command (OUTPUT ${_moc}
                COMMAND ${QT_MOC_EXECUTABLE}
                ARGS ${_moc_INCS} ${_header} -o ${_moc}
                DEPENDS ${_header}
            )

            add_file_dependencies (${_abs_FILE} ${_moc})
            set (${moc_SRCS} ${${moc_SRCS}} ${_moc})

        endif ()
     endif ()
  endforeach ()
endmacro ()
