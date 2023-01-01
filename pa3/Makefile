#------------------------------------------------------------------------------
#  Makefile for Graph ADT
#
#  make             makes FindComponents
#  make clean       removes object files
#  make check       runs valgrind to check for memory errors
#------------------------------------------------------------------------------

FindComponents : FindComponents.o Graph.o List.o
	gcc -std=c17 -Wall -o FindComponents FindComponents.o Graph.o List.o 

FindComponents.o : Graph.h List.h FindComponents.c
	gcc -std=c17 -Wall -c -g FindComponents.c

Graph.o : Graph.h Graph.c
	gcc -std=c17 -Wall -c -g Graph.c

List.o : List.h List.c
	gcc -std=c17 -Wall -c -g List.c

clean :
	rm -f FindComponents FindComponents.o Graph.o List.o

check : FindComponents
	valgrind --leak-check=full FindComponents