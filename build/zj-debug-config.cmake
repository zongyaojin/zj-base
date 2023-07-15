# ######################################################################################################################
# Package config file [project-name-config.cmake.in] template
# ######################################################################################################################

include(CMakeFindDependencyMacro)

# Find dependencies
find_dependency(spdlog REQUIRED)

# * Include targets file
# * Notices that variable PROJECT_NAME should:
# * (1) be a single-valued variable, and
# * (2) it's value should styled as "project-name", rather than "ProjectName", since CMake's find_package function will
#   either look for "ProjectNameConfig.cmake" or "project-name-config" styled config file
include("${CMAKE_CURRENT_LIST_DIR}/zj-debug-targets.cmake")
