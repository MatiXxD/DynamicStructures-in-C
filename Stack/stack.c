#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


static bool isEqual(Item item1, Item item2);
static void copyToItem(Item* source, Item item);
static void copyToNode(Item item, Node* node);
static void copyFromNode(Item* item, const Node* node);


void InitStack(Stack* stack) {

	stack->first = NULL;
	stack->count = 0;

}

bool IsEmpty(const Stack* stack) {

	return stack->count == 0;

}

bool IsFull(const Stack* stack) {

	Node* temp = (Node*)malloc(sizeof(Node));
	if (temp == NULL)
		return true;
	else
		return false;

}

unsigned StackCount(const Stack* stack) {

	return stack->count;

}

bool FindItem(Item item, const Stack* stack) {

	if (IsEmpty(stack)) {
		fprintf(stderr, "Stack is empty.\n");
		return false;
	}
		
	Node* start = stack->first;
	while (stack != NULL) {
		if (isEqual(item, start->value)) 
			return true;
		start = start->previous;
	}

	return false;

}

bool GetElem(unsigned n, Item* item, const Stack* stack) {

	if (IsEmpty(stack)) {
		fprintf(stderr, "Stack is empty.\n");
		return false;
	}
	else if (n > stack->count) {
		fprintf(stderr, "Entered number is bigger than "
			"size of stack.");
		return false;
	}

	Node* start = stack->first;
	for (unsigned i = 0; i < n-1; i++) {
		start = start->previous;
	}

	copyToItem(item, start->value);
	return true;

}

void ApplyFunc(const Stack* stack, void (*func)(Item* item)) {

	if (IsEmpty(stack))
		fprintf(stderr, "Stack is empty.\n");
	
	Node* start = stack->first;
	while (start != NULL) {
		(*func)(&start->value);
		start = start->previous;
	}

}

bool Push(Item item, Stack* stack) {

	if (IsFull(stack)) {
		fprintf(stderr, "Stack is full.\n");
		return false;
	}

	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) {
		fprintf(stderr, "Memory error.\n");
		return false;
	}

	copyToNode(item, newNode);
	if (stack->first == NULL)
		newNode->previous = NULL;
	else
		newNode->previous = stack->first;
	stack->first = newNode;
	stack->count++;

	return true;

}

bool Pop(Item* item, Stack* stack) {

	if (IsEmpty(stack)) {
		fprintf(stderr, "Stack is empty.\n");
		return false;
	}

	Node* temp = stack->first;
	stack->first = stack->first->previous;
	copyFromNode(item, temp);

	free(temp);
	stack->count--;

	return true;

}

void DeleteStack(Stack* stack) {

	Node* temp;

	while (stack->first != NULL) {
		temp = stack->first;
		stack->first = stack->first->previous;
		free(temp);
	}
	stack->count = 0;

}



static bool isEqual(Item item1, Item item2) {

	return item1 == item2;

}

static void copyToItem(Item* source, Item item) {

	*source = item;

}

static void copyToNode(Item item, Node* node) {

	node->value = item;

}

static void copyFromNode(Item* item, const Node* node) {

	*item = node->value;

}