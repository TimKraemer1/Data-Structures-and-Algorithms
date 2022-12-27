#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Graph.h"
#include "List.h"

enum color {WHITE, GREY, BLACK};

typedef struct GraphObj {
    int vertices;
    int edges;
    List* neighbors;
    int* color;
    int* discover_time;
    int* finish_time;
    int* parent;
} GraphObj;

Graph newGraph(int n);