#!/bin/bash

# Exit the script on any error
set -e

# Script absolute path
script_abs_path="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"

# Install system-level package managment dependencies
sudo apt update -y
sudo apt upgrade -y
sudo apt install -y libgtest-dev libspdlog-dev libeigen3-dev libboost-all-dev
