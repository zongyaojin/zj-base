# Use the folder name as the lib name
get_filename_component(libName ${CMAKE_CURRENT_LIST_DIR} NAME)

# * Get this lib's modules' absolute dirs without trailing slash
# * A lib could have one or many modules (no or many subdirectories, respectively) each with a set of inc, src, and
#   other folders
list(APPEND modulesAbsDirsNoSlash ${CMAKE_CURRENT_LIST_DIR})

# * Get absolute inc dirs without trailing slash, then the relative ones
# * Inc dirs are needed for install, which has to use generator expressions for portability, so they have to be relative
zj_paths_get_inc_no_slash("${modulesAbsDirsNoSlash}" libAbsIncDirs)
zj_paths_get_relative("${libAbsIncDirs}" libRelIncDirs)

# * Get absolute src dirs without trailing slash, then the cpp fils with absolute paths
# * Cpp files are only needed for building, not install, so absolute dirs are fine
zj_paths_get_src_no_slash("${modulesAbsDirsNoSlash}" libAbsSrcDirs)
zj_files_get_cpp("${libAbsSrcDirs}" libAbsCpps)

# ######################################################################################################################

# Add this lib as a target
add_library(${libName} ${libAbsCpps})

# This wrapper function invokes target_include_directories using each relative path with generator expression, so
# install gets the portable version of these inc dirs
zj_target_include_directories_genex(${libName} "${libRelIncDirs}")

# [Lib-specific] Link to internal libs, if any, that this lib depends on
target_link_libraries(${libName} zj-basics)

# [Lib-specific] Find and link external libs, if any, that this lib depends on, and link them to the target
find_package(spdlog REQUIRED)
target_link_libraries(${libName} spdlog::spdlog)

# ######################################################################################################################

# * Add slash to this lib's relative inc dirs
# * Append them to root-level variable, so that they can be used to with generator expression extract and install the
#   header files
zj_paths_add_slash("${libRelIncDirs}" libRelIncDirsSlash)
set(zjPkgRelIncDirsSlash "${zjPkgRelIncDirsSlash};${libRelIncDirsSlash}" PARENT_SCOPE)
