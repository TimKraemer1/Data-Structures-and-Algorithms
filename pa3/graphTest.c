#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Graph.h"

int main(void) {
    Graph test = newGraph(10);

    addEdge(test, 2, 6);
    addEdge(test, 3, 8);

    Graph test_copy = copyGraph(test);


    printGraph(stdout, test);
    printf("\n");
    printGraph(stdout, test_copy);
    printf("\n");
    printf("Edges in Copy: %d\n", getSize(test_copy));

    freeGraph(&test);
    freeGraph(&test_copy);
}