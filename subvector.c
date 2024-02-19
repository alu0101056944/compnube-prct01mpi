#include <stdio.h>
#include "mpi.h"

int main(int  argc, char **argv) {
  int rank, size, tag, rc, i;
  MPI_Status status;

  MPI_Init( &argc, &argv );
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );

  if (size < 11) {
    printf("Expected at least 11 processes");
    return -1;
  }

  if (rank == 0) {
    int counters[10] = {0};
    for (size_t i = 0; i < 10; i++) {
      rc = MPI_Send(&counters[i], 1, MPI_INT, i + 1, tag, MPI_COMM_WORLD);
    }

    for (size_t i = 0; i < 10; i++) {
      int newCounter;
      rc = MPI_Recv(&newCounter, 1, MPI_INT, i + 1, tag, MPI_COMM_WORLD, &status);
      counters[i] = newCounter;
    }

    printf("Final counters: ");
    for (size_t i = 0; i < 10; i++) {
      printf("%d", counters[i]);
      if (i < 9) {
        printf(" ");
      }
    }
    printf("\n");
  } else {
    int oldCounter;
    rc = MPI_Recv(&oldCounter, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
    ++oldCounter;
    rc = MPI_Send(&oldCounter, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
  }

  MPI_Finalize();
}