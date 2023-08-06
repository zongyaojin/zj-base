#!/bin/bash

# Exit the script on any error
set -e

# Script absolute path
script_abs_path="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"

# Path definitions
build_path=$script_abs_path/../build

# Remove the build and install path for a fresh start
rm -rf $build_path

# Make directories
mkdir -p $build_path

# Go to the build directory, build and install
(
    cd $build_path
    cmake .. \
        -D CMAKE_BUILD_TYPE=Release \
        -D BUILD_SHARED_LIBS=OFF \
        -D BUILD_TESTING=ON
    make install
    ctest
)
