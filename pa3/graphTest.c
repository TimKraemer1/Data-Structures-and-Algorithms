#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Graph.h"

int main(void) {
    Graph test = newGraph(10);

    addEdge(test, 2, 6);
    addArc(test, 6, 2);

    printf("%d\n", getOrder(test));
    printf("%d\n", getSize(test));

    printGraph(stdout, test);

    freeGraph(&test);
}