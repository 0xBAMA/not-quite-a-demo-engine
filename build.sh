mkdir build
cmake -S . -B ./build
cd build
make
cp ./exe ..
cd ..
rm -r ./build
