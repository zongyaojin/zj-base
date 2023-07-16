#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "zj-debug::zj-utility" for configuration ""
set_property(TARGET zj-debug::zj-utility APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(zj-debug::zj-utility PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libzj-utility.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS zj-debug::zj-utility )
list(APPEND _IMPORT_CHECK_FILES_FOR_zj-debug::zj-utility "${_IMPORT_PREFIX}/lib/libzj-utility.a" )

# Import target "zj-debug::zj-exception" for configuration ""
set_property(TARGET zj-debug::zj-exception APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(zj-debug::zj-exception PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libzj-exception.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS zj-debug::zj-exception )
list(APPEND _IMPORT_CHECK_FILES_FOR_zj-debug::zj-exception "${_IMPORT_PREFIX}/lib/libzj-exception.a" )

# Import target "zj-debug::tester" for configuration ""
set_property(TARGET zj-debug::tester APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(zj-debug::tester PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/bin/zj-debug/tester"
  )

list(APPEND _IMPORT_CHECK_TARGETS zj-debug::tester )
list(APPEND _IMPORT_CHECK_FILES_FOR_zj-debug::tester "${_IMPORT_PREFIX}/bin/zj-debug/tester" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
