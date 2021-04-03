#!/bin/bash

mkdir build
cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Release
cd build
make exe
cp ./Release/bin/exe ..
cd ..

if [ "$1" == "clean" ]
then
   rm -r ./build
fi
