# ######################################################################################################################
# * Root level [CMakeLists.txt] template
# * It's not recommended to use CMake to install system-level package managment dependencies for portability reasons
# ######################################################################################################################

cmake_minimum_required(VERSION 3.22.1)

# * When finding a package, CMake will either look for "package-name-config.cmake" or "PackageNameConfig.cmake", so when
#   the ${PROJECT_NAME} is used to generate the package config file:
# * If the project name is formatted as "project-name", then the config file should be "${PROJECT_NAME}-config.cmake"
# * If the project name is formatted as "ProjectName", then the config file should be "${PROJECT_NAME}Config.cmake"
project(zj-debug VERSION 0.0.1)

# ######################################################################################################################
# Scripts

include(${CMAKE_SOURCE_DIR}/cmake/definitions/ZJ-colors.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/definitions/ZJ-compiler-settings.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/definitions/ZJ-compile-definitions.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/definitions/ZJ-find-settings.cmake)

include(${CMAKE_SOURCE_DIR}/cmake/functions/zj_file_helpers.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/functions/zj_path_helpers.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/functions/zj_target_helpers.cmake)

include(${CMAKE_SOURCE_DIR}/cmake/installation/zj_install_helpers.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/utilities/CCache.cmake)

include(${CMAKE_SOURCE_DIR}/cmake/systems/zj-system-helpers.cmake)

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
set(zjLibsInOrder "zj-exception")

# Root level variable to store all libray's relative include directories, so that they can be used to install package,
# since the generator expression requires relative paths
set(zjPkgRelIncDirsSlash "")

# Each library's CMake file will add a library named after their folder name, then update "zjPkgRelIncDirsSlash"
foreach(zjLib IN LISTS zjLibsInOrder)
    add_subdirectory(${CMAKE_SOURCE_DIR}/libs/${zjLib})
endforeach()

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

include(CTest)

# Assuming tests are simple with only one cpp file, and there's no need to install tests since they are for client code
if(BUILD_TESTING)
    find_package(GTest REQUIRED)
    set(zjAllTests)

    foreach(zjTest IN LISTS zjAllTests)
        add_executable(${zjTest} ${CMAKE_SOURCE_DIR}/tests/${zjTest}.cpp)
        # Since the combined library is created by the install function, we can use it to link all libraries
        target_link_libraries(${zjTest} PUBLIC ${PROJECT_NAME}::${PROJECT_NAME} GTest::GTest GTest::Main)
        set_target_properties(${zjTest} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

        add_test(NAME ${zjTest} COMMAND ${CMAKE_BINARY_DIR}/tests/${zjTest})
    endforeach()
endif()
