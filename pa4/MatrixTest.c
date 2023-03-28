//Tim Kraemer
//CruzID: tikraeme
//pa4

#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Matrix.h"

int main(void) {
	Matrix A = newMatrix(10);

	changeEntry(A, 1, 1, 4);
	changeEntry(A, 1, 2, 2);
	changeEntry(A, 1, 3, 0);
	changeEntry(A, 2, 1, 7);
	changeEntry(A, 3, 1, 0);
	changeEntry(A, 2, 2, 2);
	changeEntry(A, 3, 3, 0);

	printf("Size: %d\n", size(A));
	printf("NNZ: %d\n", NNZ(A));

	Matrix B = copy(A);

	changeEntry(B, 1, 1, 3);

	printf("\nMatrix A: \n");
	printMatrix(stdout, A);
	printf("\n");
	printf("\nMatrix B: \n");
	printMatrix(stdout, B);
	printf("\n");

	printf("Equals?: %d\n", equals(A, B));

	printf("\nTranspose A:\n");
	Matrix a_tr = transpose(A);
	printMatrix(stdout, a_tr);

	printf("\nA+B:\n");
	Matrix a_plus_b = sum(A, B);
	printMatrix(stdout, a_plus_b);

	printf("\n2*A\n");
	Matrix two_times_A = scalarMult(2, A);
	printMatrix(stdout, two_times_A);

	printf("\nB-A\n");
	Matrix B_minus_A = diff(B, A);
	printMatrix(stdout, B_minus_A);

	printf("\nA*B\n");
	Matrix A_times_B = product(A, B);
	printMatrix(stdout, A_times_B);



	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&a_tr);
	freeMatrix(&a_plus_b);
	freeMatrix(&two_times_A);
	freeMatrix(&B_minus_A);
	freeMatrix(&A_times_B);
}
