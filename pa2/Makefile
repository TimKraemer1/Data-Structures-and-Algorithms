#------------------------------------------------------------------------------
#  Makefile for Graph ADT
#
#  make             makes FindPath
#  make clean       removes object files
#  make check       runs valgrind to check for memory errors
#------------------------------------------------------------------------------

FindPath : FindPath.o Graph.o List.o
	gcc -std=c17 -Wall -o FindPath FindPath.o Graph.o List.o 

FindPath.o : Graph.h List.h FindPath.c
	gcc -std=c17 -Wall -c -g FindPath.c

Graph.o : Graph.h Graph.c
	gcc -std=c17 -Wall -c -g Graph.c

List.o : List.h List.c
	gcc -std=c17 -Wall -c -g List.c

clean :
	rm -f FindPath FindPath.o Graph.o List.o

check : FindPath
	valgrind --leak-check=full FindPath