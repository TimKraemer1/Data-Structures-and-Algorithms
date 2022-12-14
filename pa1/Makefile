#------------------------------------------------------------------------------
#  Makefile for List ADT
#
#  make             makes ListTest
#  make clean       removes object files
#  make check       runs valgrind to check for memory errors
#------------------------------------------------------------------------------

ListTest : ListTest.o List.o
	gcc -std=c17 -Wall -o ListTest ListTest.o List.o 

ListTest.o : List.h ListTest.c
	gcc -std=c17 -Wall -c -g ListTest.c

List.o : List.h List.c
	gcc -std=c17 -Wall -c -g List.c

clean :
	rm -f ListTest ListTest.o List.o

check : ListTest
	valgrind --leak-check=full ListTest
