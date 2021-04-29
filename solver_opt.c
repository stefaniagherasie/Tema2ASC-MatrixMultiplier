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


	// Loop order k-i-j for optimization
	for (k = 0; k < N; ++k) {
		register double *orig_pb = &B[k * N + 0];
		register double *pa = &A[0 * N + k];

		for (i = 0; i < N; ++i) {
			register double *pc = &result[i * N + 0];
			register double *pb = orig_pb;

			for (j = 0; j < N; ++j) {
                *pc += *pa * *pb;
                pb++;
                pc++;
			}

			pa += N;
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
		register double *orig_pa = &A[i * N + i];

		for (j = 0; j < N; ++j) {
			register double *pa = orig_pa;
			register double *pb = &B[i * N + j];
			register double sum = 0.0;

			for (k = i; k < N; ++k) {
				sum += *pa * *pb;
				pa++;
				pb += N;
			}

			result[i * N + j] = sum;
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
		register double *orig_pa = &A[i * N];

		for (j = 0; j < N; ++j) {
			register double *pa = orig_pa;
			register double *pb = &B[j];
			register double sum = 0.0;

			for (k = 0; k < i + 1; ++k) {
				sum += *pa * *pb;
				pa++;
				pb += N;
			}

			result[i * N + j] = sum;
		}
	}

	return result;
}



/*
 * Add your optimized implementation here
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
	double *A_trans = transpose_upper_matrix(N, A);
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
	free(A_trans);
	free(M);
	free(P);
	free(L);

	return result;
}
