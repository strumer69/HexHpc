#include <mpi.h>  //This includes the MPI API. it gives us functions like MPI_Init, MPI_Comm_rank, MPI_Send, etc.
#include <stdio.h>
#include <stdlib.h> // for malloc and free

#define ITERATIONS 100 //number of iterations to send/receive the buffer 

int main(int argc,char **argv)
{
    MPI_Init(&argc,&argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    const long SIZE = 100*1024*1024; //100 MB - Define message size. Every MPI_Send transfers this amount.

    char *buffer = malloc(SIZE); // Allocate memory of size SIZE for the buffer to send/receive
 
    MPI_Barrier(MPI_COMM_WORLD); // wait for synchronization of all processes before starting the timer

    double start,end;// Create timer variables

    if(rank==0)
    {
        start = MPI_Wtime(); // current wall clock time in seconds

        for(int i=0;i<ITERATIONS;i++)
        {
            MPI_Send(buffer,SIZE,MPI_CHAR,1,0,MPI_COMM_WORLD);// 1= destination(rank1) rank, 0=tag (0 = noraml data , 1 = control data) 
        }

        end = MPI_Wtime();

        double seconds = end-start;

        double bw =
            ((double)SIZE*ITERATIONS)/(1024.0*1024.0*1024.0)/seconds; // Bandwidth = Data / Time

        printf("Bandwidth = %.2f GB/s\n",bw);
    }

    else if(rank==1)
    {
        for(int i=0;i<ITERATIONS;i++)
        {
            MPI_Recv(buffer,SIZE,MPI_CHAR,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);// MPI_STATUS_IGNORE= ignore metadata
        }
    }

    free(buffer);

    MPI_Finalize();
}