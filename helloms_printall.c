#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char** argv) {
  int rank, size, tag, rc, i;
  MPI_Status status;

  rc = MPI_Init(&argc, &argv);
  rc = MPI_Comm_size(MPI_COMM_WORLD, &size);
  rc = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  tag = 100;

  printf("Executed!\n");
  if(rank == 0) {
    for (size_t i = 0; i < size - 1; i++) {
      char messageReceived[20];
      rc = MPI_Recv(&messageReceived, 20, MPI_CHAR, MPI_ANY_SOURCE, tag,
          MPI_COMM_WORLD, &status);
      printf("node %d: %s", rank, messageReceived);
    }
  } else {
    char messageToSend[20];
    strcpy(messageToSend, "Hello world! ");
    rc = MPI_Send(&messageToSend, 20, MPI_CHAR, 0, tag, MPI_COMM_WORLD);
  }

  rc = MPI_Finalize();
}
