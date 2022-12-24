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

    FILE* in_fp = fopen(argv[1], "r");

    if(in_fp == NULL) {
        fprintf(stderr, "IO Error: Could not open file %s\n", argv[1]);
        return -1;
    }
    int num_vert;
    if(fscanf(in_fp, "%d", &num_vert) == 0) {
        fprintf(stderr, "Error: file format incorrect\n");
        return -1;
    }

    Graph graph1 = newGraph(num_vert);

    int vert1;
    int vert2;
    for(int i = 1; i <= num_vert; i++) {
        if(fscanf(in_fp, "%d %d", &vert1, &vert2) == 0) {
            fprintf(stderr, "Error: file format incorrect\n");
            return -1;
        }
        addEdge(graph1, vert1, vert2);
    }

    fscanf(in_fp, "%d %d", &vert1, &vert2);
    if(vert1 != 0 || vert2 != 0) {
        fprintf(stderr, "Error: file format incorrect\n");
        return -1;
    }

    printGraph(stdout, graph1);

    fclose(in_fp);

    freeGraph(&graph1);
}