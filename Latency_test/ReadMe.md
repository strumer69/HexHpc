# compile 
- mpicc pingpong_latency.c -O3 -o latency

# run
- sbatch latency.sh

# result
- Average latency = 24.732 us


- This sequence is called a ping-pong communication.
- Rank 0  ---> Rank 1
- Rank 0  <--- Rank 1

- Only one byte is transferred.

- Why only one byte? 
- Because the goal is to measure the communication delay, not the speed of transferring large data.