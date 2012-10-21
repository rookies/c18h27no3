#!/bin/bash
## Create build directory:
if [[ ! -d build ]]; then
	echo " ==> Creating build directory..."
	mkdir build || exit 1
fi
## Change into build directory:
cd build || exit 1
## Run CMake:
echo " ==> Running CMake..."
cmake .. || exit 1
## Run make:
echo " ==> Running make..."
make || exit 1
