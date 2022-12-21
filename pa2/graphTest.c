#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "List.h"

int main(void) {
    printf("test\n");
    Graph test = newGraph(5);

    addEdge(test, 1, 5);
    addEdge(test, 2, 5);
    addEdge(test, 4, 2);
    addEdge(test, 2, 3);
    addEdge(test, 4, 3);

    printNeighbors(test);

    freeGraph(&test);
}