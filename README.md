# HexHPC

## login:
ssh xx12345@hexhpc.th-deg.de

each student in THD has a specific user name. for example sm02969


## make file:
nano hello.cpp or you can use vim. --> code is at the repo named hello.cpp

nano(vim) Makefile

add the following lines to it:

all:

  g++ hello.cpp -o hello

then in terminal --> make

then you should see the created file ./hello that if you call that, you will see the result.

## Cmake:

mkdir cmake_test

cd cmake_test

Nano hello.cpp --> add the same code

module load cmake

cmake -S . -B build --> (-S .) which means Source directory is the current folder (.) and (-B build) mean  → “Put all build files in a folder called build”

cmake --build build --> this command compiles the program. it goes to the build directory (generated from previous steps) and compile sthe code.

after that by (./build/hello) we can run the executable.

## Test MPI

module load openmpi5

nano mpi_hello.cpp --> refer to (mpi_hello.cpp)




  




