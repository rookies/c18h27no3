#!/bin/bash
## Create build directory:
if [[ ! -d build ]]; then
	mkdir build || exit 1
fi
## Change into build directory:
cd build || exit 1
## Run CMake:
cmake .. || exit 1
## Run make:
make || exit 1
