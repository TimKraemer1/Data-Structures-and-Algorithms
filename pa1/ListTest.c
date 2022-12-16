#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"

int main() {
    List test1;
    List test2;

    test1 = newList();
    test2 = newList();

    append(test1, 2);
    append(test1, 3);
    append(test1, 4);
    append(test1, 5);
    prepend(test1, 0);

    append(test2, 2);
    append(test2, 3);
    append(test2, 4);
    append(test2, 5);
    prepend(test2, 0);

    printList(test1);
    printList(test2);

    printf("Are these lists equal?: %d\n", equals(test1, test2));
    
    List test3;

    test3 = copyList(test1);

    printList(test3);

    freeList(&test1);
    freeList(&test2);
    freeList(&test3);
}
