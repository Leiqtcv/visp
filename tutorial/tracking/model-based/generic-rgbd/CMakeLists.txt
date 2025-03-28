project(tutorial-tracking-mb-generic-rgbd)

cmake_minimum_required(VERSION 3.0)

find_package(VISP REQUIRED visp_core visp_mbt visp_io visp_gui visp_sensor)

# set the list of source files
set(tutorial_cpp
  tutorial-mb-generic-tracker-rgbd.cpp
  tutorial-mb-generic-tracker-rgbd-realsense.cpp
  tutorial-mb-generic-tracker-rgbd-structure-core.cpp
  tutorial-mb-generic-tracker-rgbd-realsense-json-settings.cpp)

foreach(cpp ${tutorial_cpp})
  visp_add_target(${cpp})

  if(VISP_HAVE_OGRE)
    # Add specific build flag to turn off warnings coming from Ogre3D 3rd party
    list(APPEND CXX_FLAGS_MUTE_WARNINGS "-Wno-deprecated-copy")
    list(APPEND CXX_FLAGS_MUTE_WARNINGS "-Wno-float-equal")
    list(APPEND CXX_FLAGS_MUTE_WARNINGS "-Wno-ignored-qualifiers")
    list(APPEND CXX_FLAGS_MUTE_WARNINGS "-Wno-overloaded-virtual")
    list(APPEND CXX_FLAGS_MUTE_WARNINGS "-Wno-register")
    list(APPEND CXX_FLAGS_MUTE_WARNINGS "-Wno-unused-but-set-parameter")
    list(APPEND CXX_FLAGS_MUTE_WARNINGS "-Wno-unused-parameter")
  endif()
  if(VISP_HAVE_REALSENSE2)
    # Add specific build flag to turn off warnings coming from librealsense 3rd party
    list(APPEND CXX_FLAGS_MUTE_WARNINGS "/wd4244")
    list(APPEND CXX_FLAGS_MUTE_WARNINGS "/wd4267")
    list(APPEND CXX_FLAGS_MUTE_WARNINGS "-Wno-deprecated-copy")
    list(APPEND CXX_FLAGS_MUTE_WARNINGS "-Wno-deprecated-declarations")
    list(APPEND CXX_FLAGS_MUTE_WARNINGS "-Wno-ignored-qualifiers")
    list(APPEND CXX_FLAGS_MUTE_WARNINGS "-Wno-overloaded-virtual")
    list(APPEND CXX_FLAGS_MUTE_WARNINGS "-Wno-reorder")
    list(APPEND CXX_FLAGS_MUTE_WARNINGS "-Wno-sign-compare")
    list(APPEND CXX_FLAGS_MUTE_WARNINGS "-Wno-unused-function")
    list(APPEND CXX_FLAGS_MUTE_WARNINGS "-Wno-unqualified-std-cast-call")
  endif()

  if(VISP_HAVE_OCCIPITAL_STRUCTURE)
    # Add specific build flag to turn off warnings coming from librealsense 3rd party
    list(APPEND CXX_FLAGS_MUTE_WARNINGS "-Wno-maybe-uninitialized")
    list(APPEND CXX_FLAGS_MUTE_WARNINGS "-Wno-unused-parameter")
  endif()

  if(VISP_HAVE_PCL)
    list(APPEND CXX_FLAGS_MUTE_WARNINGS "-Wno-missing-field-initializers")
    list(APPEND CXX_FLAGS_MUTE_WARNINGS "-Wno-shadow")
  endif()

  if(CXX_FLAGS_MUTE_WARNINGS)
    # Add specific build flag to turn off warnings
    visp_set_source_file_compile_flag(${cpp} ${CXX_FLAGS_MUTE_WARNINGS})
  endif()

  if(COMMAND visp_add_dependency)
    visp_add_dependency(${cpp} "tutorials")
  endif()
endforeach()

# Copy the data files
visp_copy_dir(tutorial-mb-generic-tracker-rgbd.cpp "${CMAKE_CURRENT_SOURCE_DIR}" data model)
visp_copy_dir(tutorial-mb-generic-tracker-rgbd-realsense.cpp "${CMAKE_CURRENT_SOURCE_DIR}" model)
visp_copy_dir(tutorial-mb-generic-tracker-rgbd-structure-core.cpp "${CMAKE_CURRENT_SOURCE_DIR}" model)
visp_copy_dir(tutorial-mb-generic-tracker-rgbd-realsense-json-settings.cpp "${CMAKE_CURRENT_SOURCE_DIR}" model)
