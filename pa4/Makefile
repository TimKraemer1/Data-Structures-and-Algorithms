#Tim Kraemer
#CruzID: tikraeme
#pa4

Sparse: Sparse.o Matrix.o List.o
	gcc -std=c17 -Wall -o Sparse Sparse.o Matrix.o List.o 

Sparse.o : Matrix.h List.h Sparse.c
	gcc -std=c17 -Wall -c -g Sparse.c

MatrixTest: MatrixTest.o Matrix.o List.o
	gcc -std=c17 -Wall -o MatrixTest MatrixTest.o Matrix.o List.o

MatrixTest.o: Matrix.h List.h MatrixTest.c
	gcc -std=c17 -Wall -c -g MatrixTest.c

ListTest: ListTest.o Matrix.o List.o
	gcc -std=c17 -Wall -o ListTest ListTest.o Matrix.o List.o

ListTest.o: Matrix.h List.h ListTest.c
	gcc -std=c17 -Wall -c -g ListTest.c

Matrix.o : Matrix.h Matrix.c
	gcc -std=c17 -Wall -c -g Matrix.c

List.o : List.h List.c
	gcc -std=c17 -Wall -c -g List.c

clean :
	rm -f Sparse MatrixTest Sparse.o MatrixTest.o Matrix.o List.o ListTest ListTest.o

check : Sparse
	valgrind --leak-check=full Sparse
