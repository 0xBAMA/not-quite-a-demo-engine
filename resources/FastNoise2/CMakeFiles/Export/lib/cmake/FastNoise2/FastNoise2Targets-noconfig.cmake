#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "FastNoise2::FastNoise" for configuration ""
set_property(TARGET FastNoise2::FastNoise APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(FastNoise2::FastNoise PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libFastNoise.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS FastNoise2::FastNoise )
list(APPEND _IMPORT_CHECK_FILES_FOR_FastNoise2::FastNoise "${_IMPORT_PREFIX}/lib/libFastNoise.a" )

# Import target "FastNoise2::NoiseTool" for configuration ""
set_property(TARGET FastNoise2::NoiseTool APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(FastNoise2::NoiseTool PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/bin/NoiseTool"
  )

list(APPEND _IMPORT_CHECK_TARGETS FastNoise2::NoiseTool )
list(APPEND _IMPORT_CHECK_FILES_FOR_FastNoise2::NoiseTool "${_IMPORT_PREFIX}/bin/NoiseTool" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
