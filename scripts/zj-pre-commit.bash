#!/bin/bash

# https://gist.github.com/mohanpedala/1e2ff5661761d3abd0385e8223e16425
set -euxo pipefail

# Script absolute path
script_abs_path="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"

# Path definitions
source_path=$script_abs_path/..

# Go to the source path, set up and run pre-commit
(
    cd $source_path
    pre-commit install
    pre-commit autoupdate
    pre-commit run -a
)
