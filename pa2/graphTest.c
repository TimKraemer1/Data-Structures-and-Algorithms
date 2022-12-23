#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "List.h"

int main(void) {
    printf("test\n");
    Graph test = newGraph(6);

    addEdge(test, 1, 2);
    addEdge(test, 1, 3);
    addEdge(test, 3, 4);
    addEdge(test, 4, 5);
    addEdge(test, 5, 6);
    addEdge(test, 2, 4);
    addEdge(test, 2, 5);
    addEdge(test, 2, 6);

    BFS(test, 3);

    printGraph(stdout, test);

    freeGraph(&test);
}