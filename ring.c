
#include <unistd.h>
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

  if (size < 2) {
    printf("Needs at least 2 processes.\n");
    return -1;
  }

  int nextRank = (rank + 1) % size;

  int previousRank;
  if (rank == 0) {
    previousRank = size - 1;
  } else {
    previousRank = rank - 1;
  }

  int counter = 0;

  if (counter == 0 && rank == 0) {
    ++counter;
    printf("node %d: %d\n", rank, counter);
    rc = MPI_Send(&counter, 1, MPI_INT, nextRank, tag, MPI_COMM_WORLD);
    sleep(1);
  }

  while (1) {
    rc = MPI_Recv(&counter, 1, MPI_INT, previousRank, tag, MPI_COMM_WORLD, &status);
    ++counter;
    printf("node %d: %d\n", rank, counter);
    rc = MPI_Send(&counter, 1, MPI_INT, nextRank, tag, MPI_COMM_WORLD);
    sleep(1);
  }

  rc = MPI_Finalize();
}
