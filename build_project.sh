#!/bin/bash

CURRENT_DIR_NAME=$(basename "$PWD")

# Check if the current directory is named 'project'
if [ "$CURRENT_DIR_NAME" != "project" ]; then
    echo "This script must be run from a directory named 'project' inside the docker build container"
    exit 1
fi

mkdir -p build && cd build

cmake .. -DCMAKE_INSTALL_PREFIX=/aws-iot-device-sdk-cpp-v2/

make

# Check for make command success
if [ $? -eq 0 ]; then
    echo "Build successful."
else
    echo "Build failed."
    exit 1
fi
