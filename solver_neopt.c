/*
 * Tema 2 ASC
 * 2021 Spring
 */

#include "utils.h"


/* Matrix addition */
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


/* Find transpose of a regular matrix */
double *transpose_matrix(int N, double *A) {
	int i, j;

	double *result = (double *) calloc(N * N, sizeof(double));
	if (result == NULL) {
		return NULL;
	}

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			result[j * N + i] = A[i * N + j];
		}
	}

	return result;
}


/* Find transpose of an upper triangular matrix */
double *transpose_upper_matrix(int N, double *A) {
	int i, j;

	double *result = (double *) calloc(N * N, sizeof(double));
	if (result == NULL) {
		return NULL;
	}

	for (i = 0; i < N; ++i) {
		for (j = i; j < N; ++j) {
			result[j * N + i] = A[i * N + j];
		}
	}

	return result;
}


/* Multiply two regular matrices */
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


/* Multiply two matrices, the first one being an upper triangular matrix */
double *multiply_upper_matrix(int N, double *A, double *B) {
    int i, j, k;

    double *result = (double *) calloc(N * N, sizeof(double));
	if (result == NULL) {
		return NULL;
	}

	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			for (k = i; k < N; ++k) {
				result[i * N + j] += A[i * N + k] * B[k * N + j];
			}
		}
	}

	return result;
}


/* Multiply two matrices, the first one being a lower triangular matrix */
double *multiply_lower_matrix(int N, double *A, double *B) {
    int i, j, k;

    double *result = (double *) calloc(N * N, sizeof(double));
	if (result == NULL) {
		return NULL;
	}

	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			for (k = 0; k < i + 1; ++k) {
				result[i * N + j] += A[i * N + k] * B[k * N + j];
			}
		}
	}

	return result;
}


/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double* B) {

	/* 
		C = A x B x Bt  +  At x A 			(M = B x Bt)
		C = A x M  		+  At x A 			(P = A x M )
		C = P 		  	+  At x A 			(L = At x A)
		C = P 			+  L
		C = result
	*/
	

	// B_trans = Bt
	double *B_trans = transpose_matrix(N, B);
	if (B_trans == NULL) {
		return NULL;
	}


	// M = B x Bt
	double *M = multiply_matrix(N, B, B_trans);
	if (M == NULL) {
		return NULL;
	}


	// P = A x M = A x B x Bt
	double *P = multiply_upper_matrix(N, A, M);
	if (P == NULL) {
		return NULL;
	}


	// A_trans = At
	double *A_trans = transpose_matrix(N, A);
	if (A_trans == NULL) {
		return NULL;
	}


	// L = At x A
	double *L = multiply_lower_matrix(N, A_trans, A);
	if (L == NULL) {
		return NULL;
	}


	// result = P + L
	double *result = add_matrix(N, P, L);
	if (result == NULL) {
		return NULL;
	}


	free(B_trans);
	free(M);
	free(P);
	free(A_trans);
	free(L);

	return result;
}
