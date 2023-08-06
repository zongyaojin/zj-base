#!/bin/bash

# Exit the script on any error
set -e

# Script absolute path
script_abs_path="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"

# Path definitions
build_path=$script_abs_path/../build
client_project_example_path=$script_abs_path/../client-project-example
install_path=$client_project_example_path/install

# Remove the build and install path for a fresh start
rm -rf $build_path
rm -rf $install_path

# Config cmake in file name and path
config_cmake_in_file=zj-cmake-template-config.cmake.in

# Make directories
mkdir -p $build_path
mkdir -p $install_path

# Go to the build directory, build and install
(
    cd $build_path
    cmake .. \
        -D CMAKE_INSTALL_PREFIX=$install_path \
        -D CMAKE_BUILD_TYPE=Release \
        -D BUILD_SHARED_LIBS=OFF \
        -D BUILD_TESTING=ON
    make install
    ctest
)
