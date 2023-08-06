#!/bin/bash

# Exit the script on any error
set -e

# Script absolute path
script_abs_path="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"

# Path definitions
build_path=$script_abs_path/build
zj_pkg_install_path=$script_abs_path/install

# Remove the build path for a fresh start
rm -rf $build_path

# Make directories
mkdir -p $build_path

# Go to the build directory, build and install
(
    cd $build_path
    echo -e "\n\n ---- Building client-project-example project ---- \n\n"
    cmake .. \
        -D CMAKE_PREFIX_PATH=$zj_pkg_install_path \
        -D CMAKE_BUILD_TYPE=Release
    make
    echo -e "\n\n ---- Build done, running the executable ---- \n\n"
    ./client-project-example
    echo -e "\n"
)