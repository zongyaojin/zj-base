#!/bin/bash

# https://gist.github.com/mohanpedala/1e2ff5661761d3abd0385e8223e16425
set -euxo pipefail

# Script absolute path
script_abs_path="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"

# Path definitions
build_path=$script_abs_path/../build

# Go to the build directory, build and install
(
    cd $build_path

    # Build with ZJ_CODE_COVERAGE=ON is necessary for generating code coverage
    cmake .. \
        -D ZJ_CODE_COVERAGE=ON \
        -D CMAKE_BUILD_TYPE=Release \
        -D BUILD_SHARED_LIBS=OFF \
        -D BUILD_TESTING=ON
    make

    # You need to test first, then you can get the code coverage report
    ctest

    # Generating code coverage report
    # https://subscription.packtpub.com/book/programming/9781803239729/9/ch09lvl1sec56/generating-code-coverage-reports

    # Get the tests/ folder's real path no ".." so "--exclude" and interpret
    tests_abs_real_path="$(realpath "$script_abs_path/../tests/")"
    # Exclude system "/usr" stuff and local "./tests" stuff
    lcov --directory . --exclude '/usr/*' --exclude "${tests_abs_real_path}/*" --capture --output-file coverage.info
    genhtml coverage.info --output-directory coverage-report
    firefox coverage-report/index.html
)
