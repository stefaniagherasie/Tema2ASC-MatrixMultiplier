/*
 * Tema 2 ASC
 * 2021 Spring
 */

//#include "cblas.h"
#include "utils.h"


double *add_matrix(int N, double *A, double *B) {
	int i, j;

	double *result = (double *) calloc(N * N, sizeof(double));
	if (result == NULL) {
		return NULL;
	}

	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			result[i * N + j] += A[i * N + j] + B[i * N + j];
		}
	}

	return result;
}

double *multiply_matrix(int N, double *A, double *B) {
    int i, j, k;

    double *result = (double *) calloc(N * N, sizeof(double));
	if (result == NULL) {
		return NULL;
	}

	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			for (k = 0; k < N; ++k) {
				result[i * N + j] += A[i * N + k] * B[k * N + j];
			}
		}
	}

	return result;
}


double* make_copy(int N, double *mat) {
	int i, j;

	double *copy_mat = (double *) calloc(N * N, sizeof(double));
	if (copy_mat == NULL) {
		return NULL;
	}

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

	/* 
		C = A x B x Bt  +  At x A 			(M  = A x B)
		C = M x Bt  	+  At x A 			(P = At x A)
		C = M x Bt  	+  P
		C = P
	*/


/*	double *M = make_copy(N, B);
	if (M == NULL) 
		return NULL;

	// Y := alpha*op( X )*Y
	// M = A * B
	cblas_dtrmm(
		CblasRowMajor,		// Row major
		CblasLeft, 			// Side left
		CblasUpper,			// X is upper triungular matrix
		CblasNoTrans,		// op( X ) = A
		CblasNonUnit,		// X is not assumed to be unit triangular
		N,
		N,
		1.0,				// alpha = 1.0
		A,					// X = A
		N,
		M,					// Y = M = B
		N 
	);



	double *P = make_copy(N, A);
	if (P == NULL) 
		return NULL;

	// Y := alpha*op( X )*Y
	// P = At * A;
	cblas_dtrmm(
		CblasRowMajor,		// Row major
		CblasLeft, 			// Side left
		CblasUpper,			// X is upper triungular matrix
		CblasTrans,			// op( X ) = At
		CblasNonUnit,		// X is not assumed to be unit triangular
		N,
		N,
		1.0,				// alpha = 1.0
		A,					// X = A
		N,
		P,					// Y = P = A
		N
	);



	// Z := alpha*op( X )*op( Y ) + beta*Z
	// P = M x Bt  +  P
	
	cblas_dgemm(
		CblasRowMajor,		// Row major
		CblasNoTrans,		// op( X ) = M
		CblasTrans,			// op( Y ) = Bti
		N,
		N,
		N,
		1.0,				// alpha = 1.0
		M,					// X = M
		N,
		B,					// Y = B
		N,
		1.0,				// beta = 1.0
		P,					// Z = P
		N
	); 

	double *Z = multiply_matrix(N, M, Bt);
	double *X = add_matrix(N, Z, P);

	free(M);

	return X;
*/
	return NULL;
}
