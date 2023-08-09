#!/bin/bash

# Exit the script on any error
set -e

# Script absolute path
script_abs_path="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"

# Path definitions
build_path=$script_abs_path/../build

# Go to the build directory, build and install
(
    cd $build_path
    ctest
    # https://subscription.packtpub.com/book/programming/9781803239729/9/ch09lvl1sec56/generating-code-coverage-reports
    lcov --directory . --capture --output-file coverage.info
    genhtml coverage.info --output-directory coverage-report
    firefox coverage-report/index.html
)
