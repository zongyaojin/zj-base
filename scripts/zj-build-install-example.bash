#!/bin/bash

# https://gist.github.com/mohanpedala/1e2ff5661761d3abd0385e8223e16425
set -euxo pipefail

# Script absolute path
script_abs_path="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"

# Path definitions
build_path=$script_abs_path/../build
client_project_example_path=$script_abs_path/../client-project-example
install_path=$client_project_example_path/install

# Remove the build and install path for a fresh start
rm -rf $build_path
rm -rf $install_path

# Make directories
mkdir -p $build_path
mkdir -p $install_path

# Go to the build directory, build and install
(
    cd $build_path
    cmake .. \
        -D ZJ_CODE_COVERAGE=OFF \
        -D CMAKE_INSTALL_PREFIX=$install_path \
        -D CMAKE_BUILD_TYPE=Release \
        -D BUILD_SHARED_LIBS=OFF \
        -D BUILD_TESTING=ON
    make install
    ctest
)
