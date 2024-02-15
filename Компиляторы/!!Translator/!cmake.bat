del /Q CMakeFiles
del /Q CMakeCache.txt

SET CC=clang-cl
SET CXX=clang-cl
SET CFLAGS=-m32
SET CXXFLAGS=-m32
cmake -G Ninja -Wno-dev --build CMakeLists.txt