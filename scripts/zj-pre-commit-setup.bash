#!/bin/bash

# Exit the script on any error
set -e

# Script absolute path
script_abs_path="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"

# Path definitions
source_path=$script_abs_path/..

# Go to the build directory, build and install
(
    cd $source_path
    pre-commit autoupdate
    pre-commit install
    pre-commit run -a
)
