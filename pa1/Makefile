#------------------------------------------------------------------------------
#  Makefile for List ADT
#
#  make             makes ListTest
#  make clean       removes object files
#  make check       runs valgrind to check for memory errors
#------------------------------------------------------------------------------

Lex : Lex.o List.o
	gcc -std=c17 -Wall -o Lex Lex.o List.o 

Lex.o : List.h Lex.c
	gcc -std=c17 -Wall -c -g Lex.c

List.o : List.h List.c
	gcc -std=c17 -Wall -c -g List.c

clean :
	rm -f Lex Lex.o List.o

check : Lex
	valgrind --leak-check=full Lex
