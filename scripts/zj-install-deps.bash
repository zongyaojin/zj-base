#!/bin/bash

# https://gist.github.com/mohanpedala/1e2ff5661761d3abd0385e8223e16425
set -euxo pipefail

# Script absolute path
script_abs_path="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"

# Update and install system-level package managment dependencies
sudo apt update -y && sudo apt upgrade -y
# From top to bottom, build, cmake, doxygen related, and package specific dependencies
sudo apt install -y \
    autoconf build-essential git libtool pkg-config shfmt wget \
    cmake lcov \
    doxygen doxygen-latex doxygen-doc doxygen-gui graphviz texlive-extra-utils texlive-latex-extra \
    libgtest-dev libspdlog-dev libeigen3-dev libboost-all-dev

# Python dependencies
sudo apt install -y python3-pip
pip install --upgrade pip setuptools

# Code format and check tools
sudo apt install -y \
    cppcheck

pip install --user pre-commit \
    cmakelang isort cpplint
