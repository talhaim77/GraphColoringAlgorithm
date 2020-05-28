
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "header.h"

void GreedyColoring() {
	int k, i, j, cNumber;
	int edges = 0, maxDegree = 0, minDegree, compEdges, compMinDegree, compMaxDegree;
	Vertex *graph;

	printf("Please input k: \n");
	scanf_s("%d", &k); // Getting the interval's family size. (Assuming k > 0!)

	graph = (Vertex*)calloc(k, sizeof(Vertex));

	printf("You now will be asked to insert a family of %d intervals: \n", k);

	// Setting vertices
	for (i = 0; i < k; i++) {
		printf("%dth Interval: ", i + 1);
		scanf_s("%d %d", &graph[i].x, &graph[i].y);
		graph[i].color = -1;
		graph[i].adjList = createList();
	}

	printf("The Intervals family is: \n");
	printIntervals(graph, k);

	sort(graph, k); // Sorting the vertices to optimize greedy coloring

	// Counting edges & degrees
	for (i = 0; i < k - 1; i++) {
		for (j = i + 1; j < k; j++) {
			if (isAdjacent(&graph[i], &graph[j])) {
				edges++;
				graph[i].degree++;
				graph[j].degree++;
				// Adding vertices to adjacents lists of each other
				addItem(graph[i].adjList, j);
				addItem(graph[j].adjList, i);
			}
		}
	}

	// Finding max & min degrees
	minDegree = k;
	for (i = 0; i < k; i++) {
		if (graph[i].degree > maxDegree) maxDegree = graph[i].degree;
		if (graph[i].degree < minDegree) minDegree = graph[i].degree;
	}

	printf("G Edges = %d\n", edges);
	printf("Maximum Degree of G = %d \n", maxDegree);
	printf("Minimum Degree of G = %d \n", minDegree);

	// Coloring the vertices & getting chromatic number
	coloring(graph, k);
	cNumber = getChromaticNumber(graph, k);
	printf("Chromatic Number of G = %d\n", cNumber);

	// Complement Graph
	compEdges = (k * (k - 1)) / 2 - edges;
	compMaxDegree = k - 1 - minDegree;
	compMinDegree = k - 1 - maxDegree;
	printf("G's Complement Edges = %d \n", compEdges);
	printf("Maximum Degree of G's Complement = %d \n", compMaxDegree);
	printf("Minimum Degree of G's Complement = %d \n", compMinDegree);

	printChromaticSets(graph, k, cNumber);

	// Free allocated memory
	for (i = 0; i < k; i++) {
		destroyList(graph[i].adjList);
	}
	free(graph);

}

int isAdjacent(Vertex *a, Vertex *b) {
	if (!((a->y < b->x) || (a->x > b->y))) return 1;
	return 0;
}

int getChromaticNumber(Vertex *graph, int size) {
	int i, chromatic = 0;
	for (i = 0; i < size; i++) {
		if (chromatic < graph[i].color) chromatic = graph[i].color;
	}
	return chromatic;
}

void printChromaticSets(Vertex *graph, int size, int cNum) {
	int i, j, ch_flag;
	printf("Optional Coloring: ");
	for (i = 1; i <= cNum; i++) {
		printf("{");
		ch_flag = 0;
		for (j = 0; j < size; j++) {
			if (graph[j].color == i) {
				if (ch_flag) printf(",");
				printf("[%d,%d]", graph[j].x, graph[j].y);
				ch_flag = 1;
			}
		}
		printf("} = %d", i);
		if (i < cNum) printf(",");
		printf(" ");
	}
	printf("\n");
}


// Greedy Coloring 
void coloring(Vertex *graph, int k) {
	int i, colorIdx, *available_colors;
	Node *ptr;

	graph[0].color = 1; // Assign the first color to first vertex 
	for (i = 1; i < k; i++) {
		available_colors = (int*)calloc(k, sizeof(int));
		ptr = graph[i].adjList->head->next;
		while (ptr != NULL) {
			if (graph[ptr->num].color != -1) {
				available_colors[graph[ptr->num].color] = 1;
			}
			ptr = ptr->next;
		}
		for (colorIdx = 1; colorIdx < k; colorIdx++) {
			if (available_colors[colorIdx] == 0) break;
		}
		graph[i].color = colorIdx;
		free(available_colors);
	}
}
