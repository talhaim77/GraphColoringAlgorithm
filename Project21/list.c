#include "header.h"
#include <assert.h>
#include <stdlib.h>

List *createList() {
	// Get space for a list struct
	List *list = (List *)malloc(sizeof(List));
	Node *newNode;
	if (list != NULL) {
		// Create a new node for the list
		newNode = (Node *)malloc(sizeof(Node));
		newNode->num = -1;
		newNode->next = NULL;
		newNode->prev = NULL;
		list->head = newNode;
		list->tail = newNode;
		list->size = 1;
	}
	return list;
}

void destroyList(List *list) {
	assert(list != NULL);
	if (list->head == NULL) free(list);
	else if (list->head->next == NULL) {
		free(list->head);
		free(list);
	}
	else {
		Node *delete_node = list->head;
		Node *itr_node = list->head->next;
		while (itr_node != NULL) {
			free(delete_node);
			delete_node = itr_node;
			itr_node = itr_node->next;
		}
		free(delete_node);
		free(list);
	}
}

void addItem(List *list, int item) {
	assert(list != NULL && list->head != NULL);
	Node *newNode = (Node *)malloc(sizeof(Node));
	if (newNode != NULL) {
		newNode->num = item;
		newNode->next = NULL;
		newNode->prev = list->tail;
		list->tail->next = newNode;
		list->tail = newNode;
		list->size++;
	}
}