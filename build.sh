#!/bin/bash
## Create build directory:
if [[ ! -d build ]]; then
	mkdir build || return 1
fi
## Change into build directory:
cd build || return 1
## Run CMake:
cmake .. || return 1
## Run make:
make || return 1
