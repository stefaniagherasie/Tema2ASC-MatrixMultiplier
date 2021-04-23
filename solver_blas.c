/*
 * Tema 2 ASC
 * 2021 Spring
 */
#include <cblas.h>
#include "utils.h"

double* make_copy(int N, double *mat) {
	int i, j;

	double *copy_mat = (double *) calloc(N * N, sizeof(double));

	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			copy_mat[i * N + j] = mat[i * N + j];
		}
	}

	return copy_mat;
}

/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
	printf("BLAS SOLVER\n");

	/* 
		C = A x B x Bt  +  At x A 			(M  = A x B)
		C = M x Bt  	+  At x A 			(P = At x A)
		C = M x Bt  	+  P
		C = P
	*/


	double *M = make_copy(N, B);

	// Y := alpha*op( X )*Y
	// M = A * B
	cblas_dtrmm(
		l, 			// SIDE = left
		u, 			// X is upper triungular matrix
		n, 			// op( X ) = A
		n, 			// X is not assumed to be unit triangular
		N,
		N,
		1.0,		// alpha = 1
		A,			// X = A
		N,
		M,			// Y = M = B
		N 
		);



	double *P = make_copy(N, A);

	// Y := alpha*op( X )*Y
	// P = At * A;
	cblas_dtrmm(
		l, 			// SIDE = left
		u, 			// X is upper triungular matrix
		t, 			// op( X ) = At
		n, 			// X is not assumed to be unit triangular
		N,
		N,
		1.0,		// alpha = 1
		A,			// X = A
		N,
		P,			// Y = P = A
		N
	);



	// Z := alpha*op( X )*op( Y ) + beta*Z
	// P = M x Bt  +  P
	blas_dgemm(
		n, 			// op( X ) = M
		t, 			// op( Y ) = Bt
		N,
		N,
		N,
		1.0,		// alpha = 1
		M,			// X = M
		N,
		B,			// Y = B
		N,
		1.0,		// beta = 1
		P,			// Z = P
		N
	);

	free(M);

	return P;
}
