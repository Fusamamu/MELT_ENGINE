#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MeltEngine::MeltEngineLib" for configuration "Debug"
set_property(TARGET MeltEngine::MeltEngineLib APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MeltEngine::MeltEngineLib PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libMeltEngineLib.a"
  )

list(APPEND _cmake_import_check_targets MeltEngine::MeltEngineLib )
list(APPEND _cmake_import_check_files_for_MeltEngine::MeltEngineLib "${_IMPORT_PREFIX}/lib/libMeltEngineLib.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
