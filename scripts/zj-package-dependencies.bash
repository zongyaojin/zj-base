#!/bin/bash
set -exo pipefail

# Update and install system-level package managment dependencies
sudo apt update -y
sudo apt upgrade -y

# Install package-specific dependencies
sudo apt install -y libgtest-dev libspdlog-dev libeigen3-dev libboost-all-dev
