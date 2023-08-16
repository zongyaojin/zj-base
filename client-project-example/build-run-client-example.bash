#!/bin/bash

# https://gist.github.com/mohanpedala/1e2ff5661761d3abd0385e8223e16425
set -euxo pipefail

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
    cmake .. \
        -D CMAKE_PREFIX_PATH=$zj_pkg_install_path \
        -D CMAKE_BUILD_TYPE=Release
    make
    ./client-project-example
)
