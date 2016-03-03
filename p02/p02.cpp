
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  
  const int LOOP_LIMIT = argv[1];

  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  
  // Find out rank, size
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // We are assuming at least 2 processes for this task
  if (world_size != 2) {
    fprintf(stderr, "World size must be two for %s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }
	
  int partner_rank = (world_rank + 1) % 2;
  
  double start, end, total;
  
  for(int i = 1; i < pow(2,5); i = 2 * i) {
	  char *ptr = new char[i];
	
		start = MPI_Wtime();
	  

      MPI_Send(&ptr, ping_pong_count, MPI_CHAR, partner_rank, 0, MPI_COMM_WORLD);

      MPI_Recv(&ptr, ping_pong_count, MPI_CHAR, partner_rank, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);

    }
	
		end = MPI_Wtime();
		total = end - start;
		printf("total time: %f\n", total);
  }
  MPI_Finalize();
}
