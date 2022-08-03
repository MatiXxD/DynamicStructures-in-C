#ifndef _STACK_H_
#define _STACH_H_
#include <stdbool.h>


// Define data type which gonna be 
// used as item in stack
typedef int Item;


// Define stack's node and stack
typedef struct stackNode{
	Item value;
	struct stackNode* previous;
} Node;

typedef struct stack {
	Node* first;
	unsigned count;
} Stack;


// Initialize stack
void InitStack(Stack* stack);

// Check if stack is empty
bool IsEmpty(const Stack* stack);

// Check if stack is full
bool IsFull(const Stack* stack);

// Print number of stack's elements
unsigned StackCount(const Stack* stack);

// Return true if item was found
bool FindItem(Item item, const Stack* stack);

// Print nth item of the stack
bool GetElem(unsigned n, Item* item, const Stack* stack);

// Apply func() to all elements of the stack
void ApplyFunc(const Stack* stack, void (*func)(Item* item));

// Insert item in the stack
bool Push(Item item, Stack* stack);

// Delete item from the stack
bool Pop(Item* item, Stack* stack);

// Delete stack
void DeleteStack(Stack* stack);


#endif