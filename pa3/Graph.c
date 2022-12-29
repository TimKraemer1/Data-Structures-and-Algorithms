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
            if(a < get(L)) {
                insertBefore(L, a);
                break;
            }
            moveNext(L);
        }
        //if int hasnt been inserted at this point, it is the largest value and gets appended at the end
        if(index(L) == -1 && a > back(L)) {
            append(L, a);
        }
    }
}

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

//Helper function for DFS()
void visit(Graph G, int x, int time) {
    (G->discover_time)[x] = ++time;
    (G->discover_time)[x] = GREY;
    if(length((G->neighbors)[x]) > 1) {
        moveFront((G->neighbors)[x]);
        for(int i = 1; index((G->neighbors)[x]) != -1; moveNext((G->neighbors)[x])) {
            if((G->color)[i] == WHITE) {
                (G->parent)[i] = x;
                visit(G, i, time);
            }
        }
    }
    (G->color)[x] = BLACK;
    (G->finish_time)[x] = ++time;
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
    int edge_num_u = length((G->neighbors)[u]);
    in_order((G->neighbors)[u], v);

    //checking whether a new edge was actually inserted, or whether a repeating edge was ignored
    if(edge_num_u != length((G->neighbors)[u])) {
        G->edges++;
    }

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
    int edge_num_u = length((G->neighbors)[u]);
    int edge_num_v = length((G->neighbors)[v]);
    
    in_order((G->neighbors)[u], v);
    in_order((G->neighbors)[v], u);

    //checking whether a new edge was actually inserted, or whether a repeating edge was ignored
    if(edge_num_u != length((G->neighbors)[u]) && edge_num_v != length((G->neighbors)[v])) {
        G->edges++;
    }
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
    if(getOrder(G) > 0) {
        for(int i = 1; i < getOrder(G)+1; i++) {
            if((G->color)[i] == WHITE) {
                visit(G, i, time);
            }
        }
    }
}

Graph transpose(Graph G) {
    return NULL;
}

Graph copyGraph(Graph G) {
    Graph q = newGraph(G->vertices);
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
