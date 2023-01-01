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

    Graph transp_q = newGraph(num_vert);
    DFS(transp_q, DFS_list);


    int counter = 0;

    moveFront(DFS_list);
    while(index(DFS_list) != -1) {
        if(getParent(transp_q, get(DFS_list)) == NIL) {
            counter++;
            moveNext(DFS_list);
        }
    }
    fprintf(out_fp, "G contains %d strongly connected components:\n", counter);

    List strn_comp = newList();
    counter = 0;
    moveFront(DFS_list);
    while(index(DFS_list) != -1) {
        prepend(strn_comp, get(DFS_list));
        if(getParent(transp_q, get(DFS_list)) == NIL) {
            counter++;
            fprintf(out_fp, "Component %d: ", counter);
            printList(out_fp, strn_comp);
            fprintf(out_fp, "\n");
            clear(strn_comp);
        }
    }
    freeGraph(&q);
    freeGraph(&transp_q);
    freeList(&DFS_list);
    freeList(&strn_comp);

    fclose(out_fp);
    fclose(in_fp);
}