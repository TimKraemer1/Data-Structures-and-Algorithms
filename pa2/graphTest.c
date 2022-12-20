#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "List.h"

int main(void) {
    printf("test\n");
    Graph test = newGraph(5);
    printf("Order: %d, Size: %d, Source: %d, Parent: %d, Distance: %d\n", getOrder(test), getSize(test), getSource(test), getParent(test, 3), getDist(test, 8));
    freeGraph(&test);
}