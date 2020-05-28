#include "header.h"
// Bubble Sort
void sort(Vertex* arr, int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < i; j++) {
			if (arr[j].x > arr[i].x) {
				swap(&arr[i], &arr[j]);
			}
			else if (arr[j].x == arr[i].x) {
				if (arr[j].y > arr[i].y) {
					swap(&arr[i], &arr[j]);
				}
			}
		}
	}
}

void swap(Vertex* a, Vertex* b) {
	Vertex temp = *a;
	*a = *b;
	*b = temp;
}
