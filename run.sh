#!/bin/bash

mkdir build
cd build

# Generate cmake project in the "build" folder
cmake ..

# Make it
make

# Copy data folder's contents to build
cp -rf ../data/* .

# Run executable
./gauntmore