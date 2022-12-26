#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"
#include "Graph.h"

int main(int arc, char* argv[]) {

    Graph A = newGraph(100);
    List L = newList();
    List C = newList();
    addArc(A, 64, 4);
    addArc(A, 64, 3);
    addArc(A, 42, 2);
    addArc(A, 2, 64);
    addArc(A, 4, 2);
    addArc(A, 3, 42);
    BFS(A, 3);
    getPath(L, A, 64);
    append(C, 3);
    append(C, 42);
    append(C, 2);
    append(C, 64);
    if (!equals(L, C)) printf("Test 1 Failed\n");
    moveFront(L);
    BFS(A, 2);
    getPath(L, A, 2);
    append(C, 2);
    if (!equals(L, C)) printf("Test 2 Failed\n");
    getPath(L, A, 99);
    if (equals(L, C)) printf("Test 3 Failed\n");
    clear(L);
    clear(C);
    append(C, NIL);
    BFS(A, 99);
    getPath(L, A, 2);
    if (!equals(C ,L)) printf("Test 4 Failed\n");

    if(arc != 3) {
        fprintf(stderr, "Error: Expected 2 arguements (input and output file)\n");
        return -1;
    }

    FILE* in_fp = fopen(argv[1], "r");
    FILE* out_fp = fopen(argv[2], "w");

    

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
    
    while(1) {
        fscanf(in_fp, "%d %d", &vert1, &vert2);
        if(vert1 == 0 && vert2 == 0) {
            break;
        }
        addEdge(graph1, vert1, vert2);
    }

    printGraph(out_fp, graph1);

    fprintf(out_fp, "\n");

    int source;
    int dest;
    int i = 1;

    while(1) {
        fscanf(in_fp, "%d %d", &source, &dest);
        if(source == 0 && dest == 0) {
            break;
        }
        BFS(graph1, source);
        //printing the distance of the two vertices
        if(getDist(graph1, dest) == INF) {
            fprintf(out_fp, "The distance from %d to %d is infinity\n", source, dest);
        }
        else {
            fprintf(out_fp, "The distance from %d to %d is %d\n", source, dest, getDist(graph1, dest));

        }
        //printing the path of the two vertices
        if(getDist(graph1, dest) == INF) {
            fprintf(out_fp, "No %d-%d path exists\n", source, dest);
        }
        else {
            fprintf(out_fp, "A shortest %d-%d path is: ", source, dest);
            List temp = newList();
            getPath(temp, graph1, dest);
            printList(out_fp, temp);
            freeList(&temp);
            fprintf(out_fp, "\n");
        }
        i++;
    }

    fclose(in_fp);
    fclose(out_fp);

    freeGraph(&graph1);
}