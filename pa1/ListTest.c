#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"

int main() {
    List test;

    test = newList();

    append(test, 2);
    append(test, 3);
    append(test, 4);
    append(test, 5);
    prepend(test, 0);

    printList(test);

    moveFront(test);
    moveNext(test);

    deleteBack(test);
    printList(test);

    printf("Length = %d, Cursor Index = %d, Cursor Value = %d\n", length(test), index(test), get(test));

    freeList(&test);
}
