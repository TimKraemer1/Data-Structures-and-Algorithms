#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "List.h"

typedef struct GraphObj {
    int vertices;
    int edges;
    int vertex_source;
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
    g->color = (int *) calloc(n, sizeof(int));
    g->parent = (int *) calloc(n, sizeof(int));
    g->distance = (int *) calloc(n, sizeof(int));
    g->neighbors = (List*) calloc(n, sizeof(List));
    return(g);
}

void freeGraph(Graph* pG) {
    if(pG != NULL && *pG != NULL) {
        if(&((*pG)->color) != NULL && ((*pG)->color) != NULL) {
            free(&((*pG)->color));
            (*pG)->color = NULL;
        }
        if(&((*pG)->parent) != NULL && ((*pG)->parent) != NULL) {
            free(&((*pG)->parent));
            (*pG)->parent = NULL;
        }
        if(&((*pG)->distance) != NULL && ((*pG)->distance) != NULL) {
            free(&((*pG)->distance));
            (*pG)->distance = NULL;
        }
        if(&((*pG)->neighbors) != NULL && ((*pG)->neighbors) != NULL) {
            for(int i = 0; i < (*pG)->vertices; i++) {
                freeList((*pG)->neighbors);
            }
            (*pG)->neighbors = NULL;
        }
        free(*pG);
        *pG = NULL;
    }
}