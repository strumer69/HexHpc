#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define ITERATIONS 10000

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char buffer[1];
    MPI_Barrier(MPI_COMM_WORLD);

    double start, end;

    if(rank == 0)
    {
        start = MPI_Wtime();

        for(int i=0;i<ITERATIONS;i++)
        {
            MPI_Send(buffer,1,MPI_CHAR,1,0,MPI_COMM_WORLD);
            MPI_Recv(buffer,1,MPI_CHAR,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        }

        end = MPI_Wtime();

        double latency =
            (end-start)/(2.0*ITERATIONS)*1e6;

        printf("Average latency = %.3f us\n",latency);
    }

    else if(rank==1)
    {
        for(int i=0;i<ITERATIONS;i++)
        {
            MPI_Recv(buffer,1,MPI_CHAR,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            MPI_Send(buffer,1,MPI_CHAR,0,0,MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
}