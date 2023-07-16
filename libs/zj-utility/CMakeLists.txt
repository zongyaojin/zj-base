# Use the folder name as the lib name
get_filename_component(libName ${CMAKE_CURRENT_LIST_DIR} NAME)

list(APPEND moduleAbsDirsNoSlash ${CMAKE_CURRENT_LIST_DIR})

zj_paths_get_inc_no_slash("${moduleAbsDirsNoSlash}" libAbsIncDirs)
zj_paths_get_relative("${libAbsIncDirs}" libRelIncDirs)

zj_paths_get_src_no_slash("${moduleAbsDirsNoSlash}" libAbsSrcDirs)
zj_files_get_cpp("${libAbsSrcDirs}" libAbsCpps)

# ######################################################################################################################

add_library(${libName} ${libAbsCpps})

# * The include directories use relative paths with generator expression so the package can be installed
# * Link to any internal libraries that this library depends on
zj_target_include_directories_genex(${libName} "${libRelIncDirs}")
target_link_libraries(${libName})

# * Find and link to any external libraries that this library depends on
find_package(Boost REQUIRED)
find_package(spdlog REQUIRED)
target_link_libraries(${libName} Boost::boost)

# ######################################################################################################################

# Process and append the lib's relative include dirs with slash to the root-level variable
zj_paths_add_slash("${libRelIncDirs}" libRelIncDirsSlash)
set(zjPkgRelIncDirsSlash "${zjPkgRelIncDirsSlash};${libRelIncDirsSlash}" PARENT_SCOPE)
