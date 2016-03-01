/*
 * Name			: a02p02.cpp
 * Author			: Megan Fowler
 * Version			:
 * Copyright		: Copyright @ 2016 Megan Folwer
 * Description	: MPI Point-to-Point Communication
 *
 */
#include <iostream>
#include <cstdlib>

#include "mpi.h"

using namespace std;

int main(int argc, char *argv[]){

  int ierr, my_id, num_procs;

  ierr = MPI_Init(&argc, &argv);
  ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
  ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

  cout << "Hello from : " << my_id << endl;

  ierr = MPI_Finalize();
  return EXIT_SUCCESS;

}