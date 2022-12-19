#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "List.h"

int main(void) {
    printf("test\n");
    Graph test = newGraph(5);
    freeGraph(&test);
}