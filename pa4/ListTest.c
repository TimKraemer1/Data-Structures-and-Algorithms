//Tim Kraemer
//CruzID: tikraeme
//pa4

//These are a few tests that test the functionality of the generic pointer List, using strings as an example. 
//All other functions should work since they have had no changes done

#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Matrix.h"

int main(void) {
	List a = newList();
	char* b1 = "test1\0";
	char* b2 = "test2\0";
	char* b3 = "test3\0";
	char* b4 = "test4\0";
	char* b5 = "test5\0";

	append(a, b1);
	append(a, b2);
	append(a, b3);

	printf("%s\n", (char *)front(a));
	printf("%s\n", (char *)back(a));
	moveFront(a);
	moveNext(a);
	printf("%s\n", (char *)get(a));
	insertBefore(a, b4);
	insertAfter(a, b5);

	printf("\n");

	moveFront(a);
	for(int i = 0; i < length(a); i++) {
		printf("%s\n", (char *)get(a));
		moveNext(a);
	}
}
