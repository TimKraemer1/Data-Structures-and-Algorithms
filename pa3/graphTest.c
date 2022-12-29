#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Graph.h"

int main(void) {
    Graph test = newGraph(10);

    addEdge(test, 2, 6);
    addEdge(test, 3, 8);
    addArc(test, 6, 8);
    addArc(test, 9, 1);

    Graph test_transpose = transpose(test);

    printGraph(stdout, test);
    printf("\n");
    printGraph(stdout, test_transpose);

    freeGraph(&test);
    freeGraph(&test_transpose);
}