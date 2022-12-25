#------------------------------------------------------------------------------
#  Makefile for Graph ADT
#
#  make             makes ModelGraphTest
#  make clean       removes object files
#  make check       runs valgrind to check for memory errors
#------------------------------------------------------------------------------

ModelGraphTest : ModelGraphTest.o Graph.o List.o
	gcc -std=c17 -Wall -o ModelGraphTest ModelGraphTest.o Graph.o List.o 

ModelGraphTest.o : Graph.h List.h ModelGraphTest.c
	gcc -std=c17 -Wall -c -g ModelGraphTest.c

Graph.o : Graph.h Graph.c
	gcc -std=c17 -Wall -c -g Graph.c

List.o : List.h List.c
	gcc -std=c17 -Wall -c -g List.c

clean :
	rm -f FindPath FindPath.o Graph.o List.o

check : graphTest
	valgrind --leak-check=full ModelGraphTest