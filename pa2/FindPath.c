#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"
#include "Graph.h"

int main(int arc, char* argv[]) {

    if(arc != 3) {
        fprintf(stderr, "Error: Expected 2 arguements (input and output file)\n");
        return -1;
    }

    int line_count = 0;
    FILE* in_fp = fopen(argv[1], "r");

    if(in_fp == NULL) {
        printf(stderr, "IO Error: Could not open file %s\n", argv[1]);
        return -1;
    }
    int num_vert;
    if(fscanf(in_fp, "%d", &num_vert) == 0) {
        printf(stderr, "Error: file format incorrect\n");
        return -1;
    }

    Graph graph1 = newGraph(num_vert);

    freeGraph(&graph1);
}