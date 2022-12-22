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

    printf("Parent of 1: %d\n", getParent(test, 1));
    printf("Parent of 2: %d\n", getParent(test, 2));
    printf("Parent of 3: %d\n", getParent(test, 3));
    printf("Parent of 4: %d\n", getParent(test, 4));
    printf("Parent of 5: %d\n", getParent(test, 5));
    printf("Parent of 6: %d\n", getParent(test, 6));

    printf("Distance of 1: %d\n", getDist(test, 1));
    printf("Distance of 2: %d\n", getDist(test, 2));
    printf("Distance of 3: %d\n", getDist(test, 3));
    printf("Distance of 4: %d\n", getDist(test, 4));
    printf("Distance of 5: %d\n", getDist(test, 5));
    printf("Distance of 6: %d\n", getDist(test, 6));    

    freeGraph(&test);
}