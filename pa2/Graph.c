//Tim Kraemer
//CruzID: tikraeme
//pa2

#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Graph.h"

//inserts an element into L in order, or doesnt if there is already an instance of a in the list
void inOrder(List L, int a) {
	if(length(L) == 0) {
		append(L, a);
	}
	else {
		moveFront(L);
		while(index(L) != -1) {
			if(a == get(L)) {
				return;
			}
			//take into account why we dont do <=, since we dont want duplicates in our neighbors list
			else if(a < get(L)) {
				insertBefore(L, a);
				break;
			}
			moveNext(L);
		}
		//if the element is larger than every element in the List, then append it at the end
		if(index(L) == -1) {
			append(L, a);
		}
	}			
}

enum color {WHITE, GREY, BLACK};

typedef struct GraphObj {
	int vertices;
	int edges;
	int source;
	List* neighbors;
	int* color;
	int* parent;
	int* distance;
} GraphObj;

//Graph Constructor
Graph newGraph(int n) {
	Graph g = malloc(sizeof(GraphObj));
	g->vertices = n;
	g->edges = 0;
	g->source = NIL;
	g->color = (int *)calloc(n+1, sizeof(int));
	g->parent = (int *)calloc(n+1, sizeof(int));
	g->distance = (int *)calloc(n+1, sizeof(int));
	g->neighbors = (List *)calloc(n+1, sizeof(List));	

	for(int i = 0; i < n+1; i++) {
		(g->color)[i] = WHITE;
		(g->parent)[i] = NIL;
		(g->distance)[i] = INF;
		(g->neighbors)[i] = newList();
	}
	return g;
}

//Graph Destructor
void freeGraph(Graph*pG){
	if(pG && *pG) {
		if((*pG)->color) {
			free((*pG)->color);
			(*pG)->color = NULL;
		}
		if((*pG)->parent) {
			free((*pG)->parent);
			(*pG)->parent = NULL;
		}
		if((*pG)->distance) {
			free((*pG)->distance);
			(*pG)->distance = NULL;
		}
		if((*pG)->neighbors) {
			for(int i = 0; i < (*pG)->vertices + 1; i++) {
				freeList(&(((*pG)->neighbors)[i]));
			}
			free((*pG)->neighbors);
			(*pG)->neighbors = NULL;
		}
		free(*pG);
		*pG = NULL;
	}
}

//returns order of the Graph
int getOrder(Graph G) {
	if(G == NULL) {
		printf("Graph Error: Calling getOrder() on NULL Graph Reference\n");
		exit(EXIT_FAILURE);
	}
	return G->vertices;
}

//returns size of the Graph
int getSize(Graph G) {
	if(G == NULL) {
		printf("Graph Error: Calling getSize() on a NULL Graph Reference\n");
		exit(EXIT_FAILURE);
	}
	return G->edges;
}

//returns source of the Graph
int getSource(Graph G) {
	if(G == NULL) {
		printf("Graph Error: Calling getSource() on a NULL Graph Reference\n");
		exit(EXIT_FAILURE);
	}
	return G->source;
}

//returns parent of given vertex of the Graph
int getParent(Graph G, int u) {
	if(G == NULL) {
		printf("Graph Error: Calling getParent() on a NULL Graph Reference\n");
		exit(EXIT_FAILURE);
	}
	if(u > G->vertices || u < 1) {
		printf("Graph Error: calling getParent() with invalid vertex input\n");
		exit(EXIT_FAILURE);
	}
	return (G->parent)[u];
}

//returns distance of given vertex from source of Graph
int getDist(Graph G, int u) {
	if(G == NULL) {
		printf("Graph Error: Calling getDist() on a NULL Graph Reference\n");
		exit(EXIT_FAILURE);
	}
	if(u > G->vertices || u < 1) {
		printf("Graph Error: Calling getParent() with invalid vertex input\n");
		exit(EXIT_FAILURE);
	}
	return (G->distance)[u];
}

//returns path of given vertex from source of Graph
void getPath(List L, Graph G, int u) {
	if(G == NULL) {
		printf("Graph Error: Calling getPath() on a NULL Reference\n");
		exit(EXIT_FAILURE);
	}
	if(L == NULL) {
		printf("Graph Error: Calling getPath() on a NULL List Reference\n");
		exit(EXIT_FAILURE);
	}
	if(getSource(G) == NIL) {
		printf("Graph Error: Calling getPath() when BFS() hasnt run yet\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > G->vertices) {
		printf("Graph Error: Calling getPath() with invalid source vertex\n");
		exit(EXIT_FAILURE);
	}
	
	//using pseudocode from Graph handout
	if(u == G->source) {
		append(L, G->source);
	}
	else if((G->parent)[u] == NIL) {
		append(L, NIL);
	}
	else {
		getPath(L, G, (G->parent)[u]);
		append(L, u);
	}
}

//deletes all edges of the Graph, essentially emptying it
void makeNull(Graph G) {
	if(G == NULL) {
		printf("Graph Error: Calling makeNULL() on a NULL Graph Reference\n");
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < G->vertices+1; i++) {
		(G->color)[i] = WHITE;
		(G->parent)[i] = NIL;
		(G->distance)[i] = INF;
		clear((G->neighbors)[i]);
	}
	G->edges = NIL;
	G->source = NIL;
}

//adds an edge to the Graph
void addEdge(Graph G, int u, int v) {
	if(G == NULL) {
		printf("Graph Error: Calling addEdge() on a NULL Graph Reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || v < 1 || u > G->vertices || v > G->vertices) {
		printf("Graph Error: Calling addEdge() with invalid vertex (vertices) input\n");
		exit(EXIT_FAILURE);
	}
	G->edges++;
	inOrder((G->neighbors)[u], v);
	inOrder((G->neighbors)[v], u);
}

//adds an arc to the Graph
void addArc(Graph G, int u, int v) {
	if(G == NULL) {
		printf("Graph Error: Calling addArc() on a NULL Graph Reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || v < 1 || u > G->vertices || v > G->vertices) {
		printf("Graph Error: Calling addArc() with invalid vertex (vertices) input\n");
		exit(EXIT_FAILURE);
	}
	G->edges++;
	inOrder((G->neighbors)[u], v);
}

//performs BFS on the Graph
void BFS(Graph G, int s) {
	if(G == NULL) {
		printf("Graph Error: Calling BFS() on a NULL Graph Reference\n");
		exit(EXIT_FAILURE);
	}
	if(s < 1 || s > G->vertices) {
		printf("Graph Error: Calling BFS() with invalid vertex\n");
		exit(EXIT_FAILURE);
	}
	G->source = s;
	for(int i = 1; i <= G->vertices; i++) {
		(G->color)[i] = WHITE;
		(G->distance)[i] = INF;
		(G->parent)[i] = NIL;
	}
	(G->color)[s] = GREY;
	(G->distance)[s] = 0;
	List queue = newList();
	append(queue, s);
	while(length(queue) != 0) {
		int x = front(queue);
		deleteFront(queue);
		if(length((G->neighbors)[x])) {
			moveFront((G->neighbors)[x]);
			while(index((G->neighbors)[x]) != -1) {
				int y = get((G->neighbors)[x]);
				if((G->color)[y] == WHITE) {
					(G->color)[y] = GREY;
					(G->distance)[y] = (G->distance)[x] + 1;
					(G->parent)[y] = x;
					append(queue, y);
				}
				moveNext((G->neighbors)[x]);
			}
		}
		(G->color)[x] = BLACK;
	}
	freeList(&queue);
}

//prints Graph to file
void printGraph(FILE* out, Graph G) {
	if(G == NULL) {
		printf("Graph Error: Calling printGraph() on a NULL Graph Reference\n");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i <= G->vertices; i++) {
		fprintf(out, "%d: ", i);
		printList(out, (G->neighbors)[i]);
	}
}

