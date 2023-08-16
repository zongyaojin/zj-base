#!/bin/bash

# https://gist.github.com/mohanpedala/1e2ff5661761d3abd0385e8223e16425
set -euxo pipefail

# Script absolute path
script_abs_path="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"

# Path definitions
source_path=$script_abs_path/..
doc_html_path=$script_abs_path/../build/doc/html

# Go to the build directory, build and install
(
    cd $source_path
    doxygen
    firefox $doc_html_path/index.html
)
