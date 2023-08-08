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
        -D BUILD_TESTING=ON \
        -D ZJ_CODE_COVERAGE=ON
    make
    ctest
    # https://subscription.packtpub.com/book/programming/9781803239729/9/ch09lvl1sec56/generating-code-coverage-reports
    lcov --directory . --capture --output-file coverage.info
    genhtml coverage.info --output-directory coverage_report
    firefox coverage_report/index.html
)
