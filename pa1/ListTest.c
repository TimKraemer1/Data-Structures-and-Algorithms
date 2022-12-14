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
    printf("Length: %d\n", length(test));

    moveFront(test);
    printf("Index: %d\n", index(test));
    printf("Value: %d\n", get(test));

    moveBack(test);
    printf("Index: %d\n", index(test));
    printf("Value: %d\n", get(test));

    printf("Back Data: %d\n", back(test));
    printf("Front Data: %d\n", front(test));

    set(test, 8);
    printList(test);

    moveFront(test);
    moveNext(test);
    moveNext(test);
    moveNext(test);

    printf("Index: %d, Value: %d\n", index(test), get(test));

    freeList(&test);
}
