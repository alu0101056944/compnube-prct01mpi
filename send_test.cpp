#include <vector>
#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char** argv) {
  MPI_Status status;
  int rank;
  int size;
  int tag;
  int rc;

  std::string message = "None";

  rc = MPI_Init(&argc, &argv);
  rc = MPI_Comm_size(MPI_COMM_WORLD, &size);
  rc = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  tag = 100;

  if(rank == 1) {
            std::cout << "Reached" << std::endl;

    rc = MPI_Send(&message, sizeof(std::string), MPI_CHAR, 0, tag,
        MPI_COMM_WORLD);
        std::cout << "Eexited" << std::endl;
  } else {
      std::cout << "Reached 2" << std::endl;

      std::string messageReceived;
      rc = MPI_Recv(&messageReceived, sizeof(std::string), MPI_CHAR,
              1, tag, MPI_COMM_WORLD, &status);
      std::cout << "node " << rank << " : " << messageReceived << std::endl;
  }

  rc = MPI_Finalize();
}
