# HexHPC Quick Start Guide

This guide introduces the basic workflow for using the **HexHPC** cluster at THD, including compiling C++ applications, using CMake, MPI, LAMMPS, and Apptainer.

---

# Logging in

Connect to the cluster using SSH:

```bash
ssh <username>@hexhpc.th-deg.de
```

Example:

```bash
ssh sm02969@hexhpc.th-deg.de
```

Every THD student has a unique username (e.g., `sm02969`).

---

# Module Management

HexHPC uses the **Environment Modules** system.

To save your currently loaded modules:

```bash
module save shahram
```

Later, restore them with:

```bash
module restore shahram
```

This saves you from loading the same modules every time you log in.

---

# Building a Simple C++ Program (Makefile)

Create a source file:

```bash
nano hello.cpp
```

*(or use `vim` if you prefer)*

The example source code is available in this repository as:

```
hello.cpp
```

Create a Makefile:

```bash
nano Makefile
```

Add the following content:

```Makefile
all:
	g++ hello.cpp -o hello
```

Build the program:

```bash
make
```

This creates an executable named:

```bash
./hello
```

Run it:

```bash
./hello
```

---

# Building with CMake

Create a project directory:

```bash
mkdir cmake_test
cd cmake_test
```

Create the source file:

```bash
nano hello.cpp
```

Load CMake:

```bash
module load cmake
```

Configure the project:

```bash
cmake -S . -B build
```

where

* `-S .` → use the current directory as the source directory.
* `-B build` → place all generated build files inside the `build/` directory.

Compile the project:

```bash
cmake --build build
```

Run the executable:

```bash
./build/hello
```

---

# MPI Example

Load MPI:

```bash
module load openmpi5
```

Create a project:

```bash
mkdir mpi_test
cd mpi_test
```

Create the source file:

```bash
nano mpi_hello.cpp
```

(Use the `mpi_hello.cpp` example provided in this repository.)

Compile:

```bash
mpicxx mpi_hello.cpp -o mpi_hello
```

Run:

```bash
mpirun -np 12 ./mpi_hello
```

> **Note**
>
> Requesting more than 12 processes (for example `-np 13`) on a single node results in an error because each compute node provides **12 CPU slots (cores)**.

---

# MPI with CMake

Create a new project:

```bash
mkdir cmake_mpi
cd cmake_mpi
```

Create the source file (`mpi_hello.cpp`) and the following `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.10)

project(MPIHello)

find_package(MPI REQUIRED)

add_executable(mpi_hello mpi_hello.cpp)

target_link_libraries(mpi_hello MPI::MPI_CXX)
```

Configure:

```bash
cmake -S . -B build
```

Build:

```bash
cmake --build build
```

Run:

```bash
mpirun -np 4 ./build/mpi_hello
```

---

# Building LAMMPS with CMake

Clone the repository:

```bash
git clone https://github.com/lammps/lammps.git
```

Enter the project:

```bash
cd lammps
mkdir build
cd build
```

Configure the build:

```bash
cmake ../cmake \
    -D BUILD_MPI=ON \
    -D BUILD_OMP=ON \
    -D CMAKE_BUILD_TYPE=Release
```

These commands tell CMake how the software should be built before compilation begins.

Compile:

```bash
cmake --build . -j
```

The `-j` option enables parallel compilation using multiple CPU cores.

The executable will be created as:

```bash
./lmp
```

Benchmark examples are available in:

```bash
cd ../bench
```

---

# Example Slurm Job

Create a job script:

```bash
#!/bin/bash

#SBATCH --job-name=lammps_bench
#SBATCH --nodes=1
#SBATCH --ntasks=8
#SBATCH --time=00:10:00
```

Submit the job:

```bash
sbatch job.sh
```

---

# Using Apptainer

Because some software dependencies may be unavailable on the cluster, running applications inside an **Apptainer** container is often the easiest solution.

Load Apptainer:

```bash
module load apptainer-hpc/1.4.5
```

Verify the installation:

```bash
apptainer --version
```

Download an NVIDIA CUDA container:

```bash
apptainer pull docker://nvcr.io/nvidia/cuda:12.3.0-devel-ubuntu22.04
```

This creates the image:

```text
cuda_12.3.0-devel-ubuntu22.04.sif
```

---

# Troubleshooting Apptainer

If Apptainer fails because of inherited environment variables, clear them first:

```bash
unset APPTAINER_BINDPATH
unset SINGULARITY_BINDPATH
```

Verify your compiler versions:

```bash
nvcc --version
```

```bash
gcc --version
```

Typical setup:

* CUDA installed
* GCC version 11 or 12

---

# Compiling CUDA Code

Compile a CUDA source file:

```bash
nvcc hello_cuda.cu -o hello_cuda
```

Run it:

```bash
./hello_cuda
```

---

# Repository Files

This repository contains example source files used throughout this guide:

* `hello.cpp`
* `mpi_hello.cpp`
* `hello_cuda.cu`
* `Makefile`
* `CMakeLists.txt`

These examples provide a simple starting point for learning software development and HPC workflows on HexHPC.
