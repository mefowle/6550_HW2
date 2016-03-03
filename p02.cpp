
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  const int PING_PONG_LIMIT = 10;

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

  int ping_pong_count = 0;
	
  int partner_rank = (world_rank + 1) % 2;
  
  double start, end, total;
  
  while (ping_pong_count < PING_PONG_LIMIT) {
	  char *ptr = (char *) malloc(sizeof(char*)*ping_pong_count);
	
		start = MPI_Wtime();
	  
    if (world_rank == ping_pong_count % 2) {
      // Increment the ping pong count before you send it
      ping_pong_count++;
      MPI_Send(&ptr, ping_pong_count, MPI_CHAR, partner_rank, 0, MPI_COMM_WORLD);
      
	  
	  printf("%d sent %d  bytes to %d\n",
             world_rank, ptr, partner_rank);
    } else {
      MPI_Recv(&ptr, ping_pong_count, MPI_CHAR, partner_rank, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
      printf("%d received %d bytes from %d\n",
             world_rank, ptr, partner_rank);
    }
	
		end = MPI_Wtime();
		total = end - start;
		printf("total time: %f\n", total);
  }
  MPI_Finalize();
}
