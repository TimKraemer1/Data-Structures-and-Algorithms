//Tim Kraemer
//CruzID: tikraeme
//pa4

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "List.h"
#include "Matrix.h"

typedef struct EntryObj* Entry;
typedef struct EntryObj {
	int column;
	double data;
} EntryObj;

typedef struct MatrixObj {
	int size;
	int nonzeros;
	List* row;
} MatrixObj;

Entry newEntry(int column, double data) {
	Entry e = malloc(sizeof(EntryObj));
	if(e) {
		e->column = column;
		e->data = data;
	}
	return e;
}

void freeEntry(Entry* pE) {
	if(pE && *pE) {
		free(*pE);
		*pE = NULL;
	}
}

//Yee Olde Matrix Constructeth'r
Matrix newMatrix(int n) {
	Matrix m = malloc(sizeof(MatrixObj));
	if(m) {
		m->size = n;
		m->nonzeros = 0;
		m->row = (List *)calloc(n+1, sizeof(List));
		for(int i = 0; i <= n; i++) {
			(m->row)[i] = newList();
		}
	}
	return m;
}

//the destroyeth'r of matrices
void freeMatrix(Matrix* pM) {
	if(pM && *pM) {
		for(int i = 0; i <= (*pM)->size; i++) {
			List l = ((*pM)->row)[i];
			moveFront(l);
			while(index(l) != -1 && length(l) > 0) {
				Entry e = get(l);
				freeEntry(&e);
				moveNext(l);
			}
			freeList(&l);
		}
		free((*pM)->row);
		(*pM)->row = NULL;
		free(*pM);
		*pM = NULL;
	}
}

int size(Matrix M) {
	if(M == NULL) {
		printf("Matrix Error: Calling size() on a NULL Matrix referencen\n");
		exit(EXIT_FAILURE);
	}
	return M->size;
}

int NNZ(Matrix M) {
	if(M == NULL) {
		printf("Matrix Error: Calling NNZ() on a NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	return M->nonzeros;
}

int equals(Matrix A, Matrix B) {
	if(A == NULL || B == NULL) {
		printf("Matrix Error: Calling equals on NULL Matrix reference(s)\n");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)) {
		return 0;
	}
	Entry x;
	Entry y;
	for(int i = 1; i <= size(A); i++) {
		List a = (A->row)[i];
		List b = (B->row)[i];
		if(length(a) != length(b)) {
			return 0;
		}
		moveFront(a);
		moveFront(b);
		while(index(a) != -1 && length(a) > 0) {
			x = get(a);
			y = get(b);
			if((x->data != y->data) || (x->column != y->column)) {
				return 0;
			}
			moveNext(a);
			moveNext(b);
		}
	}
	return 1;
}

void makeZero(Matrix M) {
	if(M == NULL) {
		printf("Matrix Error: Calling makeZero() on a NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i <= size(M); i++) {
		List l = (M->row)[i];
		moveFront(l);
		while(index(l) != -1 && length(l) > 0) {
			Entry e = get(l);
			freeEntry(&e);
			moveNext(l);
		}
		clear(l);
	}
	M->nonzeros = 0;
}

//-----------------------------------------------------------
int insert(List l, int col, double x, int zeros) {
	moveFront(l);
	Entry e;
	while(index(l) != -1 && length(l) > 0) {
		e = get(l);
		if(e->column == col) {
			if(x == 0) {
				freeEntry(&e);
				delete(l);
				return -1;
			}
			e->data = x;
			return 0;
		}
		else if(col < e->column) {
			if(x == 0) {
				return 0;
			}
			Entry f = newEntry(col, x);
			insertBefore(l, f);
			return 1;
		}
		moveNext(l);
	}
	if(x == 0) {
		return 0;
	}
	Entry f = newEntry(col, x);
	append(l, f);
	return 1;
}
//----------------------------------------------------------

void changeEntry(Matrix M, int i, int j, double x) {
	if(M == NULL) {
		printf("Matrix Error: Calling changeEntry()\n");
		exit(EXIT_FAILURE);
	}
	if(i < 0 || j < 0 || i > size(M) || j > size(M)) {
		printf("Matrix Error: Calling changeEntry() using out of bounds indexes (i or j)\n");
		exit(EXIT_FAILURE);
	}
	List temp = (M->row)[i];
	int res = insert(temp, j, x, M->nonzeros);
	if(res == -1) {
		M->nonzeros -= 1;
	}
	else if(res == 1) {
		M->nonzeros += 1;
	}
}

Matrix copy(Matrix A) {
	if(A == NULL) {
		printf("Matrix Error: Calling copy() on a NULL Matrix Reference\n");
		exit(EXIT_FAILURE);
	}
	Matrix m = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++) {
		moveFront((A->row)[i]);
		while(index((A->row)[i]) != -1 && length((A->row)[i]) > 0) {
			Entry e = get((A->row)[i]);
			changeEntry(m, i, e->column, e->data);
			moveNext((A->row)[i]);
		}
	}
	return m;
}
//Verily, milady, this function dost perform a task most wondrous and wise. 
//With the speed of Mercury and the grace of Venus, it taketh a matrix of thy choosing, and doth return its transpose with alacrity. 
//Mark well, the transpose be a mirror image of sorts, with the rows becoming columns and the columns becoming rows. 
//Behold, this function is a true master of linear algebra, and shall serve thee well in thy computations.
Matrix transpose(Matrix A) {
	if(A == NULL) {
		printf("Matrix Error: Calling transpose on a NULL Matrix Reference\n");
		exit(EXIT_FAILURE);
	}
	Matrix m = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++) {
		moveFront((A->row)[i]);
		while(index((A->row)[i]) != -1 && length((A->row)[i]) > 0) {
			Entry e = get((A->row)[i]);
			changeEntry(m, e->column, i, e->data);
			moveNext((A->row)[i]);
		}
	}
	return m;
}

Matrix scalarMult(double x, Matrix A) {
	if(A == NULL) {
		printf("Matrix Error: Calling scalarMult() on a NULL Matrix Reference\n");
		exit(EXIT_FAILURE);
	}
	Matrix m = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++) {
		moveFront((A->row)[i]);
		while(index((A->row)[i]) != -1 && length((A->row)[i]) > 0) {
			Entry e = get((A->row)[i]);
			changeEntry(m, i, e->column, x*e->data);
			moveNext((A->row)[i]);
		}
	}
	return m;
}

void add_row(Matrix M, int row, List A, List B, int size) {
	moveFront(A);
	moveFront(B);
	Entry a;
	Entry b;

	if(A == B) {
		while(index(A) != -1 && length(A) > 0) {
			a = get(A);
			changeEntry(M, row, a->column, 2*a->data);
			moveNext(A);
		}
		return;
	}

	while(index(A) != -1 || index(B) != -1) {
		if(index(A) == -1 && index(B) != -1) {
			b = get(B);
			changeEntry(M, row, b->column, b->data);
			moveNext(B);
		}
		else if(index(A) != -1 && index(B) == -1) {
			a = get(A);
			changeEntry(M, row, a->column, a->data);
			moveNext(A);
		}
		else {
			a = get(A);
			b = get(B);
			if(a->column == b->column) {
				changeEntry(M, row, a->column, a->data + b->data);
				moveNext(A);
				moveNext(B);
			}
			else if(b->column < a->column) {
				changeEntry(M, row, b->column, b->data);
				moveNext(B);
			}
			else if(a->column < b->column) {
				changeEntry(M, row, a->column, a->data);
				moveNext(A);
			}
		}
	}
}

Matrix sum(Matrix A, Matrix B) {
	if(A == NULL || B == NULL) {
		printf("Matrix Error: Calling sum() on NULL Matrix Reference(s)\n");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)) {
		printf("Matrix Error: calling sum() with different size Matrices\n");
		exit(EXIT_FAILURE);
	}
	Matrix new = newMatrix(size(A));
	for(int i = 1; i <= size(B); i++) {
		int size1 = size(A);
		add_row(new, i, (A->row)[i], (B->row)[i], size1);
	}
	return new;
}

//X-Y
void sub_row(Matrix m, int row, List A, List B, int size) {
	moveFront(A);
	moveFront(B);
	Entry a;
	Entry b;
	while(index(A) != -1 || index(B) != -1) {
		if(index(A) == -1 && index(B) != -1) {
			b = get(B);
			changeEntry(m, row, b->column, -1*b->data);
			moveNext(B);
		}
		else if(index(A) != -1 && index(B) == -1) {
			a = get(A);
			changeEntry(m, row, a->column, a->data);
			moveNext(A);
		}
		else {
			a = get(A);
			b = get(B);
			if(a->column == b->column) {
				changeEntry(m, row, a->column, a->data - b->data);
				moveNext(A);
				moveNext(B);
			}
			else if(a->column < b->column) {
				changeEntry(m, row, a->column, a->data);
				moveNext(A);
			}
			else if(b->column < a->column) {
				changeEntry(m, row, b->column, -1*b->data);
				moveNext(B);
			}
		}
	}
}

Matrix diff(Matrix A, Matrix B) {
	if(A == NULL || B == NULL) {
		printf("Matrix Error: Calling diff() on NULL Matrix Reference(s)\n");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)) {
		printf("Matrix Error: Calling diff() with different size Matrices\n");
		exit(EXIT_FAILURE);
	}
	Matrix new = newMatrix(size(A));
	for(int i = 1; i <= size(B); i++) {
		int sizeA = size(A);
		sub_row(new, i, (A->row)[i], (B->row)[i], sizeA);
	}
	return new;
}

double vectorDot(List P, List Q) {
	moveFront(P);
	moveFront(Q);
	double sum = 0;
	while(index(P) != -1 || index(Q) != -1) {
		if(index(P) == -1 && index(Q) != -1) {
			break;
		}
		else if(index(P) != -1 && index(Q) == -1) {
			break;
		}
		else {
			Entry p = get(P);
			Entry q = get(Q);
			if(p->column == q->column) {
				sum += p->data * q->data;
				moveNext(P);
				moveNext(Q);
			}
			else if(p->column < q->column) {
				moveNext(P);
			}
			else if(p->column > q->column) {
				moveNext(Q);
			}
		}
	}
	return sum;
}

Matrix product(Matrix A, Matrix B) {
	if(A == NULL || B == NULL) {
		printf("Matrix Error: Calling product() on NULL Matrix Reference(s)\n");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)) {
		printf("Matrix Error: Calling product() with different size Matrices\n");
		exit(EXIT_FAILURE);
	}
	Matrix prod = newMatrix(size(A));
	double row_dot;
	Matrix tr_B = transpose(B);
	for(int i = 1; i <= size(A); i++) {
		for(int j = 1; j <= size(tr_B); j++) {
			row_dot = vectorDot((A->row)[i], ((tr_B->row)[j]));
			changeEntry(prod, i, j, row_dot);
		}
	}
	makeZero(tr_B);
	freeMatrix(&tr_B);
	//code given to me by Nomvus
	return prod;
}

void printMatrix(FILE* out, Matrix M) {
	if(M == NULL) {
		printf("Matrix Error: Calling printMatrix() using NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i <= size(M); i++) {
		List l = (M->row)[i];
		if(length(l)) {
			fprintf(out, "%d: ", i);
			moveFront(l);
			while(index(l) != -1 && length(l) > 0) {
				Entry e = get(l);
				fprintf(out, "(%d, %.1f) ", e->column, e->data);
				moveNext(l);
			}
			fprintf(out, "\n");
		}
	}
}

