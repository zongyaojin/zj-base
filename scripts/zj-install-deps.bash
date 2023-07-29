#!/bin/bash
# Google style guide: https://google.github.io/styleguide/shellguide.html#s7.4-source-filenames

# Exit the script on any error
set -e

# Script absolute path
script_abs_path="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"

# Install system-level package managment dependencies
sudo apt update -y
sudo apt upgrade -y
sudo apt install -y autoconf build-essential git libtool pkg-config shfmt wget
sudo apt install -y cmake
sudo apt install -y libgtest-dev libspdlog-dev libeigen3-dev libboost-all-dev

# Install python dependencies
sudo apt install -y python3-pip
pip install --upgrade pip setuptools
pip install --user cmakelang