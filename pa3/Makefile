#------------------------------------------------------------------------------
#  Makefile for Graph ADT
#
#  make             makes graphTest
#  make clean       removes object files
#  make check       runs valgrind to check for memory errors
#------------------------------------------------------------------------------

graphTest : graphTest.o Graph.o List.o
	gcc -std=c17 -Wall -o graphTest graphTest.o Graph.o List.o 

graphTest.o : Graph.h List.h graphTest.c
	gcc -std=c17 -Wall -c -g graphTest.c

Graph.o : Graph.h Graph.c
	gcc -std=c17 -Wall -c -g Graph.c

List.o : List.h List.c
	gcc -std=c17 -Wall -c -g List.c

clean :
	rm -f graphTest graphTest.o Graph.o List.o

check : graphTest
	valgrind --leak-check=full graphTest