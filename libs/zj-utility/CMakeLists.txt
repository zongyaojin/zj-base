# Use the folder name as the lib name
get_filename_component(libName ${CMAKE_CURRENT_LIST_DIR} NAME)

list(APPEND modulesAbsDirsNoSlash ${CMAKE_CURRENT_LIST_DIR})

zj_paths_get_inc_no_slash("${modulesAbsDirsNoSlash}" libAbsIncDirs)
zj_paths_get_relative("${libAbsIncDirs}" libRelIncDirs)

zj_paths_get_src_no_slash("${modulesAbsDirsNoSlash}" libAbsSrcDirs)
zj_files_get_cpp("${libAbsSrcDirs}" libAbsCpps)

# ######################################################################################################################

add_library(${libName} ${libAbsCpps})

zj_target_include_directories_genex(${libName} "${libRelIncDirs}")
target_link_libraries(${libName} zj-debug)

# ~~~
# find_package(Boost REQUIRED)
# target_link_libraries(${libName} Boost::boost)
# ~~~

# ######################################################################################################################

zj_paths_add_slash("${libRelIncDirs}" libRelIncDirsSlash)
set(zjPkgRelIncDirsSlash "${zjPkgRelIncDirsSlash};${libRelIncDirsSlash}" PARENT_SCOPE)
