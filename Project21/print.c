
#include "header.h"

void printIntervals(Vertex* g, int size) {
	int i;
	for (i = 0; i < size; i++) {
		printf("[%d,%d]", g[i].x, g[i].y);
		if (i != size - 1) printf(",");
	}
	printf("\n");
}