  #include <stdio.h>
  #include <string.h>
  #include "mpi.h"
  int main(int argc, char **argv)
  {
    int rank, size, tag, rc, i;
    MPI_Status status;
    char message[20];

    rc = MPI_Init(&argc, &argv);
    rc = MPI_Comm_size(MPI_COMM_WORLD, &size);
    rc = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    tag = 100;
      
    if(rank == 0) {
      strcpy(message, "Hello, world");
      for (i = 1; i < size; i++) 
        rc = MPI_Send(message, 13, MPI_CHAR, i, tag, MPI_COMM_WORLD);
    } 
    else 
      rc = MPI_Recv(message, 13, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);

    printf( "node %d : %.13s\n", rank, message);
    rc = MPI_Finalize();
  }


