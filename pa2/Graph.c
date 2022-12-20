#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Graph.h"
#include "List.h"

enum color {WHITE, GREY, BLACK};

typedef struct GraphObj {
    int vertices;
    int edges;
    int vertex_source;
    bool BFS_run;
    List* neighbors;
    int* color;
    int* parent;
    int* distance;
} GraphObj;

Graph newGraph(int n) {
    Graph g = malloc(sizeof(GraphObj));
    g->vertices = n;
    g->edges = 0;
    g->vertex_source = NIL;
    g->color = (int *) calloc(n+1, sizeof(int));
    g->parent = (int *) calloc(n+1, sizeof(int));
    g->distance = (int *) calloc(n+1, sizeof(int));
    g->neighbors = (List*) calloc(n+1, sizeof(List));

    for(int i = 0; i < n+1; i++) {
        (g->color)[i] = WHITE;
        (g->parent)[i] = NIL;
        (g->distance)[i] = INF;
        (g->neighbors)[i] = newList();
    }
    return(g);
}

void freeGraph(Graph* pG) {
    if(pG != NULL && *pG != NULL) {
        if((*pG)->color != NULL) {
            free((*pG)->color);
            (*pG)->color = NULL;
        }
        if((*pG)->parent != NULL) {
            free((*pG)->parent);
            (*pG)->parent = NULL;
        }
        if((*pG)->distance != NULL) {
            free((*pG)->distance);
            (*pG)->distance = NULL;
        }
        if((*pG)->neighbors != NULL) {
            for(int i = 0; i < (*pG)->vertices; i++) {
                freeList((*pG)->neighbors);
            }
            free((*pG)->neighbors);
            (*pG)->neighbors = NULL;
        }
        free(*pG);
        *pG = NULL;
    }
}

int getOrder(Graph G) {
    return G->vertices;
}

int getSize(Graph G) {
    return G->edges;
}

int getSource(Graph G) {
    return G->vertex_source;
}

int getParent(Graph G, int u) {
    return (G->parent)[u];
}

getDist(Graph G, int u) {
    return (G->distance)[u];
}

void getPath(List L, Graph G, int u) {

}

void makeNull(Graph G) {
    
}