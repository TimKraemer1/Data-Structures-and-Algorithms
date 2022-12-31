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

Graph newGraph(int n) {
    Graph g = malloc(sizeof(GraphObj));
    g->vertices = n;
    g->edges = 0;
    g->color = (int *) calloc(n+1, sizeof(int));
    g->parent = (int *) calloc(n+1, sizeof(int));
    g->discover_time = (int *) calloc(n+1, sizeof(int));
    g->finish_time = (int *) calloc(n+1, sizeof(int));
    g->neighbors = (List *) calloc(n+1, sizeof(List));

    for(int i = 0; i < n+1; i++) {
        (g->color)[i] = WHITE;
        (g->parent)[i] = NIL;
        (g->discover_time)[i] = UNDEF;
        (g->finish_time)[i] = UNDEF;
        (g->neighbors)[i] = newList();
    }
    return g;
}

void freeGraph(Graph* pG) {
    if(pG != NULL && pG != NULL) {
        if((*pG)->color != NULL) {
            free((*pG)->color);
            (*pG)->color = NULL;
        }
        if((*pG)->parent != NULL) {
            free((*pG)->parent);
            (*pG)->parent = NULL;
        }
        if((*pG)->discover_time != NULL) {
            free((*pG)->discover_time);
            (*pG)->discover_time = NULL;
        }
        if((*pG)->finish_time != NULL) {
            free((*pG)->finish_time);
            (*pG)->finish_time = NULL;
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
//-------Helper function that sorts an element into list------------------------------------------------
void in_order(List L, int a, int edges) {
    if(length(L) == 0) {
        append(L, a);
    }
    else {
        moveFront(L);
        while(index(L) != -1) {
            if(a < get(L)) {
                insertBefore(L, a);
                edges++;
                break;
            }
            //if the target element is equal to comparative element, then it already exists and not do anything else
            else if(a == get(L)) {
                return;
            }
            moveNext(L);
        }
        //if int hasnt been inserted at this point, it is the largest value and gets appended at the end
        if(index(L) == -1 && a > back(L)) {
            append(L, a);
            edges++;
        }
    }
}
//-------------------------------------------------------------------------------------------------------

//Helper function for DFS()
void visit(Graph G, int x, int* time) {
    (G->discover_time)[x] = ++(*time);
    (G->color)[x] = GREY;
    int y;
    if(length((G->neighbors)[x]) > 0) {
        moveFront((G->neighbors)[x]);
        while(index((G->neighbors)[x]) != -1) {
            y = get((G->neighbors)[x]);
            if((G->color)[y] == WHITE) {
                (G->parent)[y] = x;
                visit(G, y, time);
            }
            moveNext((G->neighbors)[x]);
        }
    }
    (G->color)[x] = BLACK;
    (G->finish_time)[x] = ++(*time);
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
        printf("Graph Error: Calling getSize with a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->edges;
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

int getDiscover(Graph G, int u) {
    if(G == NULL) {
        printf("Graph Error: Calling getDiscover with a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u > G->vertices || u < 1) {
        printf("Graph Error: Calling getDiscover() with an invalid vertex value\n");
    }
    return (G->discover_time)[u];
}
int getFinish(Graph G, int u) {
    if(G == NULL) {
        printf("Graph Error: Calling getDiscover with a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u > G->vertices || u < 1) {
        printf("Graph Error: Calling getDiscover() with an invalid vertex value\n");
    }
    return (G->finish_time)[u];
}

void addArc(Graph G, int u, int v) {
    if(G == NULL) {
        printf("Graph Error: Calling addArc() with a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G)) {
        printf("Graph Error: Calling addArc() with an invalid vertex value\n");
        exit(EXIT_FAILURE);
    }
    in_order((G->neighbors)[u], v, G->edges);
}

void addEdge(Graph G, int u, int v) {
    if(G == NULL) {
        printf("Graph Error: Calling addEdge() with a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G)) {
        printf("Graph Error: Calling addEdge() with an invalid vertex value\n");
        exit(EXIT_FAILURE);
    }
    
    in_order((G->neighbors)[u], v, G->edges);
    in_order((G->neighbors)[v], u, G->edges);
}

void DFS(Graph G, List S) {
    if(G == NULL) {
        printf("Graph Error: Calling DFS() with a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(S) != getOrder(G)) {
        printf("Graph Error: Calling DFS() with an invalid List length\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 1; i < G->vertices + 1; i++) {
        (G->color)[i] = WHITE;
        (G->parent)[i] = NIL;
    }

    int time = 0;
    for(int i = 1; i <= getOrder(G); i++) {
        if((G->color)[i] == WHITE) {
            visit(G, i, &time);
        }
    }
}

Graph transpose(Graph G) {
    if(G == NULL) {
        printf("Graph Error: calling transpose() on a NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    Graph q = newGraph(G->vertices);
    int j = 0;

    for(int i = 1; i < G->vertices + 1; i++) {
        moveFront((G->neighbors)[i]);
        while(index((G->neighbors)[i]) != -1) {
            j = get((G->neighbors)[i]);
            addArc(q, j, i);
            moveNext((G->neighbors)[i]);
        }
    }
    return q;
}

Graph copyGraph(Graph G) {
    if(G == NULL) {
        printf("Graph Error: calling copyGraph() on a NULL graph reference\n");
        exit(EXIT_FAILURE);
    }

    Graph q = newGraph(G->vertices);
    //this frees all of the lists that are allocated by default in the neighbors array, to avoid double allocation and mem leaks
    for(int i = 0; i < G->vertices + 1; i++) {
        freeList(&((q->neighbors)[i]));
    }

    for(int i = 0; i < G->vertices + 1; i++) {
        (q->color)[i] = (G->color)[i];
        (q->parent)[i] = (G->parent)[i];
        (q->discover_time)[i] = (G->discover_time)[i];
        (q->finish_time)[i] = (G->finish_time)[i];
        (q->neighbors)[i] = copyList((G->neighbors)[i]);
    }
    q->edges = G->edges;
    return q;
}

void printGraph(FILE* out, Graph G) {
    if(G == NULL) {
        printf("Graph Error: calling printGraph() on a NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 1; i <= G->vertices; i++) {
        fprintf(out, "%d: ", i);
        if(length((G->neighbors)[i]) > 0) {
            moveFront((G->neighbors)[i]);
            while(index((G->neighbors)[i]) != -1) {
                fprintf(out, "%d ", get((G->neighbors)[i]));
                moveNext((G->neighbors)[i]);
            }
        }
        fprintf(out, "\n");
    }
}
