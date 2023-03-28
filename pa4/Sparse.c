//Tim Kraemer
//CruzID: tikraeme
//pa4

#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Matrix.h"

int main(int argc, char* argv[]) {
	if(argc != 3) {
		fprintf(stderr, "Error: Expected 2 arguements, got %d instead\n", argc-1);
		return(-1);
	}

	FILE* in_fp = fopen(argv[1], "r");
	FILE* out_fp = fopen(argv[2], "w");

	if(in_fp == NULL || out_fp == NULL) {
		fprintf(stderr, "Error: Could not open 1 of the input files\n");
	}

	int a;
	int b;
	int n;

	fscanf(in_fp, "%d %d %d", &n, &a, &b);
	Matrix A = newMatrix(n);
	Matrix B = newMatrix(n);

	int row;
	int column;
	double data;

	for(int i = 0; i < a; i++) {
		fscanf(in_fp, "%d %d %lf", &row, &column, &data);
		changeEntry(A, row, column, data);
	}
	for(int i = 0; i < b; i++) {
		fscanf(in_fp, "%d %d %lf", &row, &column, &data);
		changeEntry(B, row, column, data);
	}
	fprintf(out_fp, "A has %d non-zero entries:\n", NNZ(A));
	printMatrix(out_fp, A);
	fprintf(out_fp, "\n");
	fprintf(out_fp, "B has %d non-zero entries:\n", NNZ(B));
	printMatrix(out_fp, B);

	fprintf(out_fp, "\n");
	
	fprintf(out_fp, "(1.5)*A =\n");
	Matrix const_prod = scalarMult(1.5, A);
	printMatrix(out_fp, const_prod);
	fprintf(out_fp, "\n");

	makeZero(const_prod);
	freeMatrix(&const_prod);

	fprintf(out_fp, "A+B =\n");
	Matrix add1 = sum(A, B);
	printMatrix(out_fp, add1);
	fprintf(out_fp, "\n");

	makeZero(add1);
	freeMatrix(&add1);

	fprintf(out_fp, "A+A =\n");
	Matrix add2 = sum(A, A);
	printMatrix(out_fp, add2);
	fprintf(out_fp, "\n");

	makeZero(add2);
	freeMatrix(&add2);

	fprintf(out_fp, "B-A =\n");
	Matrix sub1 = diff(B, A);
	printMatrix(out_fp, sub1);
	fprintf(out_fp, "\n");

	makeZero(sub1);
	freeMatrix(&sub1);

	fprintf(out_fp, "A-A =\n");
	Matrix sub2 = diff(A, A);
	printMatrix(out_fp, sub2);
	fprintf(out_fp, "\n");

	makeZero(sub2);
	freeMatrix(&sub2);

	fprintf(out_fp, "Transpose(A) =\n");
	Matrix tr_A = transpose(A);
	printMatrix(out_fp, tr_A);
	fprintf(out_fp, "\n");
	
	makeZero(tr_A);
	freeMatrix(&tr_A);

	fprintf(out_fp, "A*B =\n");
	Matrix prod1 = product(A, B);
	printMatrix(out_fp, prod1);
	fprintf(out_fp, "\n");

	makeZero(prod1);
	freeMatrix(&prod1);

	fprintf(out_fp, "B*B =\n");
	Matrix prod2 = product(B, B);
	printMatrix(out_fp, prod2);

	makeZero(prod2);
	freeMatrix(&prod2);

	makeZero(A);
	freeMatrix(&A);

	makeZero(B);
	freeMatrix(&B);

	fclose(in_fp);
	fclose(out_fp);
}
