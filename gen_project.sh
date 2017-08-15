#!/bin/bash

if [ ! -d build ]; then
	mkdir build
fi

cd build

if [[ "$OSTYPE" == "darwin"* ]]; then
cmake -G Xcode ../
else
cmake ../
fi

if [ ! $? -eq 0 ]; then
echo "error - cmake"
fi

cd ..

