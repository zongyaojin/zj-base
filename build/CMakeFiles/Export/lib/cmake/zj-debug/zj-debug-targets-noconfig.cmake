#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "zj-debug::zj-exceptions" for configuration ""
set_property(TARGET zj-debug::zj-exceptions APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(zj-debug::zj-exceptions PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libzj-exceptions.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS zj-debug::zj-exceptions )
list(APPEND _IMPORT_CHECK_FILES_FOR_zj-debug::zj-exceptions "${_IMPORT_PREFIX}/lib/libzj-exceptions.a" )

# Import target "zj-debug::tester" for configuration ""
set_property(TARGET zj-debug::tester APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(zj-debug::tester PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/bin/zj-debug/tester"
  )

list(APPEND _IMPORT_CHECK_TARGETS zj-debug::tester )
list(APPEND _IMPORT_CHECK_FILES_FOR_zj-debug::tester "${_IMPORT_PREFIX}/bin/zj-debug/tester" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
