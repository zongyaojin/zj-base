#!/bin/bash
set -exo pipefail

# Get this script's filename with absolute path
script_file=$(realpath "$0")
# Get this script's absolute path without the filename
script_absolute_path=$(dirname "$script_file")

# Path definitions
build_path=$script_absolute_path/build
zj_package_install_path=$script_absolute_path/install

# Remove the build path for a fresh start
rm -rf $build_path

# Make directories
mkdir -p $build_path

# Go to the build path, build and install
(
    cd $build_path
    cmake .. \
        -D CMAKE_PREFIX_PATH=$zj_package_install_path \
        -D CMAKE_BUILD_TYPE=Release
    make
    ./client-project-example
)
