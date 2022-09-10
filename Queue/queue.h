#ifndef _QUEUE_H_
#define _QUEUE_H_

// Include std libs
#include <stdbool.h>

// Define data type
typedef int Item;

// Define node
typedef struct queueNode{
    Item item;
    struct queueNode* next;
} Node;

// Define queue
typedef struct queue{
    Node* start;
    Node* end;
    unsigned size;
} Queue;


// Functions' prototypes
void InitQueue(Queue* queue);

// Check is queue empty
bool IsEmpty(const Queue* queue);

// Check is queue full
bool IsFull(const Queue* queue);

// Return queue size
unsigned QueueSize(const Queue* queue);

// Find item in queue
bool InQueue(const Item* item, const Queue* queue);

// Get nth element of the queue
bool GetFromQueue(unsigned int n, Item* item, const Queue* queue);

// Apply func() to all elements of the queue
void TraverseQueue(Queue* queue, void (*func)(Item* item));

// Add item
bool AddToQueue(const Item* item, Queue* queue);

// Remove item from queue
bool DeleteFromQueue(Item* item, Queue* queue);

// Empty queue
void EmptyQueue(Queue* queue);


#endif
