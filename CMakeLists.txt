# ######################################################################################################################
# * Root level [CMakeLists.txt] template
# * It's not recommended to use CMake to install system-level package managment dependencies for portability reasons
# ######################################################################################################################

cmake_minimum_required(VERSION 3.22.1)

# * When finding a package, CMake will either look for "package-name-config.cmake" or "PackageNameConfig.cmake", so when
#   the ${PROJECT_NAME} is used to generate the package config file:
# * If the project name is formatted as "project-name", then the config file should be "${PROJECT_NAME}-config.cmake"
# * If the project name is formatted as "ProjectName", then the config file should be "${PROJECT_NAME}Config.cmake"
project(zj-base VERSION 0.0.1)

# ######################################################################################################################
# Scripts

include(${CMAKE_SOURCE_DIR}/cmake/zj-include-all.cmake)

# ######################################################################################################################
# System check

zj_system_ubuntu_2204(osSupported)
if(NOT osSupported)
    message(FATAL_ERROR "This package currently only supports Ubuntu 22.04")
endif()

# ######################################################################################################################
# Libraries

# All libraries in dependency order, this cannot be done by finding all folders in [libs/]; manually adding there here
# since the order matters
set(zjLibsInOrder "zj-basics" "zj-debug" "zj-utility")

# Root level variable to store all libray's relative include directories, so that they can be used to install package,
# since the generator expression requires relative paths
set(zjPkgRelIncDirsSlash "")

# Each library's CMake file will add a library named after their folder name, then update "zjPkgRelIncDirsSlash"
foreach(zjLib IN LISTS zjLibsInOrder)
    add_subdirectory(${CMAKE_SOURCE_DIR}/libs/${zjLib})
endforeach()

# Remove duplicates and empty entries
zj_variable_prune(zjPkgRelIncDirsSlash)

# ######################################################################################################################
# Examples

# Use RELATIVE to find all example folder names, order doesn't matter
file(GLOB zjExamples RELATIVE ${CMAKE_SOURCE_DIR}/examples ${CMAKE_SOURCE_DIR}/examples/*)
foreach(example IN LISTS zjExamples)
    add_subdirectory(${CMAKE_SOURCE_DIR}/examples/${example})
endforeach()

# ######################################################################################################################
# Installation

# Use the function to combine all targets as one interface target and install the combined target
set(zjHeaderPatterns "*.hpp" "*.h")
set(zjDataFolders "specs")
zj_combine_install_library("${zjLibsInOrder}" "${zjPkgRelIncDirsSlash}" "${zjHeaderPatterns}" "${zjExamples}"
                           "${zjDataFolders}")

# ######################################################################################################################
# Tests

if(BUILD_TESTING)
    enable_testing()
    # Collect all first-level subfolders and files in the tests/ directory
    file(GLOB zjAllTests RELATIVE "${CMAKE_SOURCE_DIR}/tests" "${CMAKE_SOURCE_DIR}/tests/*")
    zj_test_setup("${zjAllTests}")
endif()
