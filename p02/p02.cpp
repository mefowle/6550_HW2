#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
 
  int LOOP_LIMIT;
  if(argc < 2){
    LOOP_LIMIT = 1000;
  }
  else{
    LOOP_LIMIT = atoi(argv[1];
  }
 
	

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
  double bandwidth;  

  for(int i = 1; i < pow(2,10); i = 2 * i) {
    
//    cout << i << " ";
    
    start = MPI_Wtime();

    while(int j = 0; j < LOOP_LIMIT; j++){
      char *ptr = new char[i];
	
      MPI_Send(ptr, i, MPI_CHAR, partner_rank, 0, MPI_COMM_WORLD);
	
      MPI_Recv(ptr, i, MPI_CHAR, partner_rank, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
	
      delete[] ptr;
    }
    
    end = MPI_Wtime();
    total = end - start;
    
    bandwith = 2*(i/total); 

    cout << total << " " << bandwidth << "\n";
  }   
  
  MPI_Finalize();
}
