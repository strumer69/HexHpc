# HexHPC

## login:
ssh xx12345@hexhpc.th-deg.de

each student in THD has a specific user name. for example sm02969

## hint 

you can save the current loaded modules by command : module save shahram ---> then later use them by: --> module restore shahram

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

mkdir mpi_test

nano mpi_hello.cpp --> refer to (mpi_hello.cpp)

then compile it: --> mpicxx mpi_hello.cpp -o mpi_hello

Run the executable: --> mpirun -np 12 ./mpi_hello --> if -np=13 we will receive error. because the max number of slots (CPU core) in each node is 12.

## MPI and cmake

mkdir cmake_mpi --> and cd to it :) 

The same code should exist and  CMakeLists.txt should be as follow:

cmake_minimum_required(VERSION 3.10)

project(MPIHello)

find_package(MPI REQUIRED)

add_executable(mpi_hello mpi_hello.cpp)

target_link_libraries(mpi_hello MPI::MPI_CXX)

 build:
 
instead of (mkdir build --> cd build --> cmake ..) we can do use the following:

cmake -S . -B build
 
cmake --build build

Run:

mpirun -np 4 ./build/mpi_hello

## Build LAMMPS with CMake

git clone https://github.com/lammps/lammps.git

cd lammps 

mkdir build

cd build

The following steps tells CMake exactly how you want the software to be built before any actual compilation happens:

 cmake ../cmake \

  -D BUILD_MPI=ON \
  
  -D BUILD_OMP=ON \
  
  -D CMAKE_BUILD_TYPE=Release

Then compile:

While the previous commands we discussed were just configuring the project (making a plan), this one executes that plan.

cmake --build . -j

Output binary:

./lmp

Use a STANDARD benchmark case:

cd ../bench

Create a Slurm job script

#!/bin/bash

#SBATCH --job-name=lammps_bench

#SBATCH --nodes=1

#SBATCH --ntasks=8

#SBATCH --time=00:10:00










  




