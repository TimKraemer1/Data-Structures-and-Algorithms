#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"

int main() {
    List test1;

    test1 = newList();

    clear(test1);

    printf("List Length: %d, List index = %d\n", length(test1), index(test1));

    freeList(&test1);
}
