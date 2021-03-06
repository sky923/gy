#!/bin/bash

set -e

cd "`dirname "$0"`"

if [ ! -d build ]; then
	mkdir build
fi

cd build

rm CMakeCache.txt

if [[ "$OSTYPE" == "darwin"* ]]; then
cmake -G Xcode ../
else
cmake ../
fi

if [ ! $? -eq 0 ]; then
echo "error - cmake"
fi

cd ..

