# MPI InfiniBand Bandwidth Benchmark

MPI-based benchmark to measure point-to-point communication performance between HPC compute nodes.

This project implements a simple bandwidth benchmark similar to OSU Micro-Benchmarks (`osu_bw`) to evaluate the performance of an InfiniBand-connected cluster.

---

## Overview

High Performance Computing applications often require communication between distributed compute nodes.

The communication path is:

```
Application
     |
     v
MPI
     |
     v
OpenMPI
     |
     v
UCX
     |
     v
InfiniBand Network
     |
     v
Remote Compute Node
```

This benchmark measures the effective communication bandwidth between two MPI ranks.

Example:

```
Rank 0 (Node A)                     Rank 1 (Node B)

100 MB buffer
      |
      |
      |  MPI_Send()
      |---------------------------->
                                   MPI_Recv()
```

---

# Features

* MPI point-to-point communication
* Large message transfer benchmark
* Slurm compatible
* Supports multi-node HPC clusters
* Measures effective network throughput

---

# Requirements

The benchmark requires:

* Linux
* MPI implementation (OpenMPI recommended)
* C compiler
* Slurm workload manager (for cluster execution)

Example environment:

```
Compiler:
GCC 15.2.0

MPI:
OpenMPI 5.0.10

Communication:
UCX 1.20.0

Network:
InfiniBand
```

---

# Files

```
.
├── bandwidth.c
├── bandwidth.slurm
└── README.md
```

---

# Compilation

Load MPI modules:

```bash
module purge

module load gnu15/15.2.0
module load openmpi5/5.0.10
```

Compile:

```bash
mpicc -O3 bandwidth.c -o bandwidth
```

This creates the executable:

```
bandwidth
```

Check dependencies:

```bash
ldd bandwidth
```

Expected:

```
libmpi.so
libucp.so
libuct.so
```

---

# Running Locally (Test)

For a quick MPI test:

```bash
mpirun -np 2 ./bandwidth
```

Expected output:

```
Bandwidth = XX.XX GB/s
```

---

# Running on Slurm Cluster

Example Slurm script:

`bandwidth.slurm`

```bash
#!/bin/bash

#SBATCH --partition=cpu-xeon-ib56
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1
#SBATCH --nodelist=ant10,ant11
#SBATCH --time=00:05:00
#SBATCH --job-name=mpi_bandwidth
#SBATCH --output=mpi_bandwidth_%j.out


module purge

module load gnu15/15.2.0
module load openmpi5/5.0.10


echo "Running on:"
hostname


echo "Loaded modules:"
module list


mpirun --map-by ppr:1:node ./bandwidth
```

Submit:

```bash
sbatch bandwidth.slurm
```

Monitor:

```bash
squeue
```

Check result:

```bash
cat mpi_bandwidth_JOBID.out
```

---

# Benchmark Methodology

The benchmark:

1. Allocates a memory buffer:

```
100 MB
```

2. Sends the buffer:

```
100 times
```

3. Measures communication time:

```
MPI_Wtime()
```

4. Calculates:

```
Bandwidth =
(total data transferred)
/
(total communication time)
```

---

# Example Calculation

If:

```
Message size = 100 MB

Iterations = 100

Total data = 10 GB

Time = 0.5 seconds
```

Then:

```
Bandwidth = 10 GB / 0.5 sec

Bandwidth = 20 GB/s
```

---

# Result Interpretation

Higher bandwidth means faster node-to-node communication.

Typical values:

| Network           |   Bandwidth |
| ----------------- | ----------: |
| 1 Gb Ethernet     |   ~0.1 GB/s |
| 10 Gb Ethernet    |     ~1 GB/s |
| 100 Gb InfiniBand | ~10-12 GB/s |
| 200 Gb InfiniBand | ~20-25 GB/s |

Actual results depend on:

* MPI implementation
* UCX configuration
* PCIe topology
* InfiniBand generation
* Network load

---

# Debugging InfiniBand Usage

Enable UCX logging:

```bash
export UCX_LOG_LEVEL=info
```

Run:

```bash
mpirun --map-by ppr:1:node ./bandwidth
```

A correct InfiniBand path should show:

```
mlx5
rc
```

If you see:

```
tcp
```

MPI is using Ethernet instead of InfiniBand.

---


# Read More:

* HPC Systems
* MPI Parallel Computing
* Scientific Computing
* Cluster Performance Optimization
