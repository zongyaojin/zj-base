#!/bin/bash
# Google style guide: https://google.github.io/styleguide/shellguide.html#s7.4-source-filenames

# Exit the script on any error
set -e

# Script absolute path
script_abs_path="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"

# Update and install system-level package managment dependencies
sudo apt update -y && sudo apt upgrade -y
# From top to bottom, build, cmake, doxygen related, and package specific dependencies
sudo apt install -y \
    autoconf build-essential git libtool pkg-config shfmt wget \
    cmake \
    doxygen doxygen-latex doxygen-doc doxygen-gui graphviz texlive-extra-utils texlive-latex-extra \
    libgtest-dev libspdlog-dev libeigen3-dev libboost-all-dev

# Install python dependencies
sudo apt install -y python3-pip
pip install --upgrade pip setuptools
pip install --user cmakelang
