#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"

int main() {
    List test1;

    test1 = newList();

    append(test1, 2);
    append(test1, 3);
    append(test1, 4);
    append(test1, 5);
    prepend(test1, 0);

    printList(stdout, test1);

    freeList(&test1);
}
