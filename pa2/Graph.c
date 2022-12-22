#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Graph.h"
#include "List.h"

void in_order(List L, int a) {
    if(length(L) == 0) {
        append(L, a);
    }
    else {
        moveFront(L);
        while(index(L) != -1) {
            if(a <= get(L)) {
                insertBefore(L, a);
                break;
            }
            moveNext(L);
        }
        //if int hasnt been inserted at this point, it is the largest value and gets appended at the end
        if(index(L) == -1) {
            append(L, a);
        }
    }
}

enum color {WHITE, GREY, BLACK};

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
            for(int i = 0; i < (*pG)->vertices+1; i++) {
                freeList(&(((*pG)->neighbors)[i]));
            }
            free((*pG)->neighbors);
            (*pG)->neighbors = NULL;
        }
        free(*pG);
        *pG = NULL;
    }
}

int getOrder(Graph G) {
    if(G == NULL) {
        printf("Graph Error: Calling getParent with a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->vertices;
}

int getSize(Graph G) {
    if(G == NULL) {
        printf("Graph Error: Calling getParent with a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->edges;
}

int getSource(Graph G) {
    if(G == NULL) {
        printf("Graph Error: Calling getParent with a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->vertex_source;
}

int getParent(Graph G, int u) {
    if(G == NULL) {
        printf("Graph Error: Calling getParent with a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u > G->vertices || u < 1) {
        printf("Graph Error: Calling getParent with an invalid vertex value\n");
        exit(EXIT_FAILURE);
    }
    return (G->parent)[u];
}

int getDist(Graph G, int u) {
    if(G == NULL) {
        printf("Graph Error: Calling getDist with a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u > G->vertices || u < 1) {
        printf("Graph Error: Calling getDist with an invalid vertex value\n");
        exit(EXIT_FAILURE);
    }
    return (G->distance)[u];
}

//not finished
void getPath(List L, Graph G, int u) {
    if(G == NULL) {
        printf("Graph Error: Calling getDist with a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u > G->vertices || u < 1) {
        printf("Graph Error: Calling getDist with an invalid vertex value\n");
        exit(EXIT_FAILURE);
    }
    if(getSource(G) == NIL) {
        printf("Graph Error: calling getSource when BFS has not been run\n");
        exit(EXIT_FAILURE);
    }
}

void makeNull(Graph G) {
    if(G == NULL) {
        printf("Graph Error: Calling addEdge() with Null Graph reference\n");
        exit(EXIT_FAILURE);
    }
    G->edges = 0;
    G->vertex_source = NIL;
    for(int i = 0; i < G->vertices + 1; i++) {
        (G->color)[i] = WHITE;
        (G->distance)[i] = INF;
        (G->parent)[i] = NIL;
        clear((G->neighbors)[i]);
    }
}

void addEdge(Graph G, int u, int v) {
    if(G == NULL) {
        printf("Graph Error: Calling addEdge() with Null Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || v < 1 || u > G->vertices || v > G->vertices) {
        printf("Graph Error: Calling addEdge with invalid vertex values\n");
        exit(EXIT_FAILURE);
    }
    //add check to see if Edge already exists
    G->edges++;
    in_order((G->neighbors)[u], v);
    in_order((G->neighbors)[v], u);
}

void addArc(Graph G, int u, int v) {
    if(G == NULL) {
        printf("Graph Error: Calling addEdge() with Null Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || v < 1 || u > G->vertices || v > G->vertices) {
        printf("Graph Error: Calling addEdge with invalid vertex values\n");
        exit(EXIT_FAILURE);
    }
    G->edges++;
    in_order((G->neighbors)[u], v);
}

void BFS(Graph G, int s) {
    if(G == NULL) {
        printf("Graph Error: Calling BFS() with a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(s < 1 && s > G->vertices) {
        printf("Graph Error: Calling BFS() with an invalid vertex input\n");
        exit(EXIT_FAILURE);
    }
    for(int x = 1; x < G->vertices + 1; x++) {
        (G->color)[x] = WHITE;
        (G->distance)[x] = INF;
        (G->parent)[x] = NIL;
    }
    (G->color)[s] = GREY;
    List queue = newList();
    append(queue, s);
    while(length(queue) != 0) {
        int x = back(queue);
        deleteBack(queue);
        moveFront((G->neighbors)[x]);
        while((G->neighbors)[x] != NULL) {
            int y = get((G->neighbors)[x]);
            if((G->color)[y] == WHITE) {
                (G->color)[y] = GREY;
                (G->distance)[y] = (G->distance)[x] + 1;
                (G->parent)[y] = x;
                append(queue, y);
            }
            moveNext((G->neighbors)[x]);
        }
        (G->color)[x] = BLACK;
    }
    freeList(&queue);
}

//additional function for debugging
void printNeighbors(Graph G) {
    for(int i = 1; i < G->vertices+1; i++) {
        printList(stdout, (G->neighbors)[i]);
        printf("\n");
    }
}