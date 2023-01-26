//Tim Kraemer
//Cruz ID: tikraeme
//pa2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"
#include "Graph.h"

int main(int argc, char* argv[]) {
	//Check number of arguements
	if(argc != 3) {
		fprintf(stderr, "Error: Expected 2 arguements (input and output file)\n");
		return -1;
	}
	
	//Open the input and output files
	FILE * in_fp = fopen(argv[1], "r");
	FILE * out_fp = fopen(argv[2], "w");

	if(in_fp == NULL || out_fp == NULL) {
		fprintf(stderr, "Error: Could not open arguement files\n");
		return -1;
	}
	
	//Get number of vertices and create the graph
	int num_vert = 0;
	fscanf(in_fp, "%d", &num_vert);

	Graph graph1 = newGraph(num_vert);

	int vert1;
	int vert2;

	//read in the edges and add them to the graph
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

	//read in the source dest pairs and run BFS on each pair, printing the path (if it exists) to the output file
	while(1) {
		fscanf(in_fp, "%d %d", &source, &dest);
		if(source == 0 && dest == 0) {
			break;
		}
		BFS(graph1, source);
		if(getDist(graph1, dest) == INF) {
			fprintf(out_fp, "The distance from %d to %d is infinity\nNo %d-%d path exists\n", source, dest, source, dest);
		}
		else {
			fprintf(out_fp, "The distance from %d to %d is %d\nA shortest %d-%d path is: ", source, dest, getDist(graph1, dest), source, dest);
			List list1 = newList();
			getPath(list1, graph1, dest);
			printList(out_fp, list1);
			freeList(&list1);
			fprintf(out_fp, "\n");
		}
	}
	//free the graph and close the input files
	freeGraph(&graph1);
	fclose(in_fp);
	fclose(out_fp);
}

