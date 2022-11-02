mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make modular
./modular.exe