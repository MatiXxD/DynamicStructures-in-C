#ifndef _LIST_H_
#define _LIST_H_

// Std libs
#include <stdbool.h>

// Define data type
typedef int Item;

// Define list node
typedef struct listNode{
    Item item;
    struct listNode* next;
} Node;

// Define list
typedef struct list{
    Node* start;
    unsigned size;
} List;


// Initialize list
void InitList(List* list);

// Check is list empty
bool IsEmpty(const List* list);

// Check is list full
bool IsFull(const List* list);

// Return list's size
unsigned ListSize(const List* list);

// Find item in the list
bool SeekInList(const Item *item, const List* list);

// Get nth element of the list
bool GetFromList(unsigned n, Item* item, const List* list);

// Apply func() to all elements of the list
void TraverseList(List* list, void (*func)(Item* item));

// Add item
bool AddToList(const Item* item, List* list);

// Delete nth item
bool DeleteFromList(unsigned n, Item* item, List* list);

// Delete element from list by value
bool DeleteValFromList(const Item* item, List* list);

// Empty list
void EmptyList(List* list);



#endif