#pragma once
#include <stdio.h>

typedef struct Node {
	struct Node *prev;
	struct Node *next;
	int num;
} Node;

typedef struct List {
	struct Node *head;
	struct Node *tail;
	int size;
} List;

typedef struct interval {
	int x;
	int y;
	int degree;
	int color;
	List *adjList;
} Vertex;

// Creates a new List structure with one node.
struct List *createList();

// Add item to list.
void addItem(List *list, int item);

// Frees nodes and list memory.
void destroyList(List *list);

void GreedyColoring();

void printIntervals(Vertex* g, int size);
void sort(Vertex* g, int size);
void swap(Vertex* a, Vertex* b);
int isAdjacent(Vertex *, Vertex *);
void coloring(Vertex *graph, int k);
int getChromaticNumber(Vertex *graph, int);
void printChromaticSets(Vertex *graph, int, int);
