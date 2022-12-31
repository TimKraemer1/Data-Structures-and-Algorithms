#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]) {

    if(argc != 3) {
        fprintf(stderr, "Error: Expected 2 arguements (input and output file)\n");
        return -1;
    }

    FILE* in_fp = fopen(argv[1], "r");
    FILE* out_fp = fopen(argv[2], "w");

    if(in_fp == NULL || out_fp == NULL) {
        fprintf(stderr, "IO Error: Could not open file\n");
        return -1;
    }

    int num_vert;
    fscanf(in_fp, "%d", &num_vert);

    Graph q = newGraph(num_vert);

    fprintf(out_fp, "Adjacency list representation of G:\n");

    int vert1;
    int vert2;

    while(1) {
        fscanf(in_fp, "%d %d", &vert1, &vert2);
        if(vert1 == 0 && vert2 == 0) {
            break;
        }
        addEdge(q, vert1, vert2);
    }

    printGraph(out_fp, q);

    fprintf(out_fp, "\n");

    List DFS_list = newList();
    for(int i = 1; i <=num_vert; i++) {
        append(DFS_list, i);
    }

    DFS(q, DFS_list);

    List opp_list = newList();
    moveBack(DFS_list);

    while(index(DFS_list) != -1) {
        append(opp_list, get(DFS_list));
        moveBack(DFS_list);
    }
    Graph transp_q = newGraph(num_vert);
    DFS(transp_q, opp_list);
}