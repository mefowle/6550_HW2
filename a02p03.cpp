/*
 ============================================================================
 Name        : trapezoid.c
 Author      : Xizhou Feng
 Version     :
 Copyright   : 
 Description : Numerical Quadrature Example in MPI
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mpi.h>

double f(int k, double x) {
	return pow(x, k) * exp(x);
}

double trapezoid(int k, double left_enpt, double right_endp, int count, double base_len) {
	double estimate, x;

	int i;
	estimate = (f(k, left_enpt) + f(k, right_endp))/2.0;
	for (i=1; i<count; i++) {
		x = left_enpt + i * base_len;
		estimate += f(k, x);
	}
	estimate *= base_len * exp(-1.0);

	return estimate;
}

void get_chunk(int rank, int np, int elems, int* counts, int *start_idx, int *end_idx) {

	int min_chunk_size = elems / np;
	int max_chunk_size = (elems + np - 1) / np;
	int remainder = elems % np;

	if (rank < remainder) {
		*counts = max_chunk_size;
	} else {
		*counts = min_chunk_size;
	}

	if (rank <= remainder) {
		*start_idx = rank * max_chunk_size;
	} else {
		*start_idx = remainder * max_chunk_size + (rank - remainder) * min_chunk_size;
	}

	*end_idx = *start_idx + *counts;
	//printf("rank=%d start_K=%d end_K=%d chunk_size=%d\n", rank, *start_idx, *end_idx, *counts);
}


void build_mpi_type(double* a_ptr,
double* b_ptr,
int* n_ptr,
int* k_ptr,
MPI_Datatype* input_mpi_type) {
	MPI_Datatype array_of_types[4] = {MPI_DOUBLE, MPI_DOUBLE, MPI_INT, MPI_INT};
	int array_of_blocklengths[4] = {1, 1, 1, 1};

	MPI_Aint a_addr, b_addr, n_addr, k_addr;
	MPI_Get_address(a_ptr, &a_addr);
	MPI_Get_address(b_ptr, &b_addr);
	MPI_Get_address(n_ptr, &n_addr);
	MPI_Get_address(k_ptr, &k_addr);

	MPI_Aint array_of_displacement[4] = {0};
	array_of_displacement[1] = b_addr - a_addr;
	array_of_displacement[2] = n_addr - a_addr;
	array_of_displacement[3] = k_addr - a_addr;

	int my_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Type_create_struct(4, array_of_blocklengths, array_of_displacement, array_of_types, input_mpi_type);
	MPI_Type_commit(input_mpi_type);
}

void get_input(
		int my_rank,
		int comm_sz,
		double* a_ptr,
		double* b_ptr,
		int*	n_ptr,
		int* 	k_ptr)
{
	MPI_Datatype input_mpi_t;
	build_mpi_type(a_ptr, b_ptr, n_ptr, k_ptr, &input_mpi_t);

	if (my_rank == 0) {
		while(1) {
			printf("Enter a, b, n, and k\n");
			scanf("%lf%lf%d%d", a_ptr, b_ptr, n_ptr, k_ptr);
			if (*n_ptr < 1 || *a_ptr > *b_ptr) {
				printf("Incorrect input. Please make sure n > 0 and a < b\n");
				continue;
			} else {
				break;
			}
		}
	}
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(a_ptr, 1, input_mpi_t, 0, MPI_COMM_WORLD);
	MPI_Type_free(&input_mpi_t);

	return;
}

int 
main(int argc, char *argv[])
{
	int 		K;
	double 		a;
	double 		b;
	int 		N;
	int			my_rank;
	int			num_procs;

	// Initialize MPI Environment
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

	// get input
	int input_ok = 0;
	if (argc >=5) {
		a = atof(argv[1]);
		b = atof(argv[2]);
		N = atoi(argv[3]);
		K = atoi(argv[4]);
		if (N > 1 && a < b) {
			input_ok = 1;
		}
	}
	if (!input_ok) {
		get_input(my_rank, num_procs, &a, &b, &N, &K);
	}

	double local_start = MPI_Wtime();

	int k = 0;

	// calculate integral Ik
	double Ik = 0.0;
	double h = (b - a) / N;

	int start_K, end_K, local_K;
	get_chunk(my_rank, num_procs, K+1, &local_K, &start_K, &end_K);

	// allocate local_Iks for keeping Iks computed on each process
	double *local_Iks = (double *)malloc(sizeof(double) * local_K);
	/*
	 * TODO: Collect all values of Ik to the process 0f rank 0
	 */
	//=========Start Computing Iks====================================
	//
	//  Write code to compute local_Iks
	//
	//=========End Computing Iks====================================


	// allocate recv_buf for keeping all Iks
	double *recv_buf = (double *)malloc(sizeof(double) * (K+1));
	/*
	 * TODO: Collect all values of Ik to the process 0f rank 0
	 */
	//=========Start Collecting Data====================================
	//
	//  Write code to collect the data (Iks) from all processes
	//
	//=========End Collecting Data====================================

	double local_finish = MPI_Wtime();
	double local_elapsed = local_finish - local_start;
	double elapsed;
	MPI_Reduce(&local_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

	if (my_rank == 0) {
		char *fname = "numerical.dat";
		FILE *fp = fopen(fname, "w+");
		if (fp) { // creating file succeeds
			fprintf(fp, "#%s\t%s\t%s\t%s\n", "a", "b", "N", "K");
			fprintf(fp, "%.6f\t%.6f\t%d\t%10d\n", a, b, N, K);
			fprintf(fp, "#%4s\t%10s\t%10s\t%10s\n", "k", "I(k)", "kI(k-1)", "I(k)+kI(k-1)");
			int i = 0;
			for (i=1; i<=K; i++) {
				fprintf(fp, "%5d\t%10.6f\t%10.6f\t%10.6f\n", i, recv_buf[i], recv_buf[i-1] * i, recv_buf[i] + i * recv_buf[i-1]);
			}
			fclose(fp);
		} else {
			fprintf(stderr, "ERROR: failed to create %s\n", fname);
		}

	}
	// Clean up MPI environment
	MPI_Finalize(); 
	return 0;
}
