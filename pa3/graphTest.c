#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Graph.h"

int main(void) {
    Graph test = newGraph(6);

    addEdge(test, 1, 2);
    addEdge(test, 1, 3);
    addEdge(test, 2, 1);
    addEdge(test, 2, 4);
    addEdge(test, 2, 5);
    addEdge(test, 2, 6);
    addEdge(test, 3, 1);
    addEdge(test, 3, 4);
    addEdge(test, 4, 2);
    addEdge(test, 4, 3);
    addEdge(test, 4, 5);
    addEdge(test, 5, 2);
    addEdge(test, 5, 4);
    addEdge(test, 5, 6);
    addEdge(test, 6, 2);
    addEdge(test, 6, 5);

    List test_list = newList();
    for(int i = 6; i > 0; i--) {
        append(test_list, i+1);
    }

    printGraph(stdout, test);

    DFS(test, test_list);

    for(int i = 1; i < getOrder(test) + 1; i++) {
        printf("Discover Time: %d\n", getDiscover(test, i));
    }

    freeGraph(&test);
    freeList(&test_list);
}