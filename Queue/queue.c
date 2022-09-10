#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


// Prototypes of local functions
static bool isEqual(const Item* item1, const Item* item2);
static Node* getNode(unsigned n, Node* start);
static void makeNode(const Item* item, Node* node);


///////////////////////////////////////////////////////////////////


// Queue's functions
void InitQueue(Queue* queue){

    queue->start = NULL;
    queue->end = NULL;
    queue->size = 0;

}

bool IsEmpty(const Queue* queue){

    return (queue->size == 0);

}

bool IsFull(const Queue* queue){

    Node* temp = (Node*)malloc(sizeof(Node));
    if(temp == NULL)
        return true;

    free(temp);
    return false;

}

unsigned QueueSize(const Queue* queue){

    return queue->size;

}

bool InQueue(const Item* item, const Queue* queue){

    Node* node = queue->start;
    while(node != NULL){
        if(isEqual(item, &node->item))
            return true;
        node = node->next;
    }

    return false;

}

bool GetFromQueue(unsigned int n, Item* item, const Queue* queue){

    if(queue->size < n){
        fprintf(stderr, "Out of range. Queue size is %u.\n", queue->size);
        return false;
    }

    Node* temp = getNode(n, queue->start);
    if(temp != NULL){
        *item = temp->item;
        return true;
    }
    else{
        return false;
    }

}

void TraverseQueue(Queue* queue, void (*func)(Item* item)){

    Node* temp = queue->start;
    while(temp != NULL){
        func(&temp->item);
        temp = temp->next;
    }

}

bool AddToQueue(const Item* item, Queue* queue){

    Node* newNode = NULL;

    if(IsFull(queue)){
        fprintf(stderr, "Queue is full.\n");
        return false;
    }

    newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL){
        fprintf(stderr, "Memory error.\n");
        return false;
    }

    makeNode(item, newNode);
    if(queue->end == NULL){
        queue->start = newNode;
    }
    else{
        queue->end->next = newNode;
    }
    queue->end = newNode;
    queue->size++;

    return true;

}

bool DeleteFromQueue(Item* item, Queue* queue){

    if(IsEmpty(queue)){
        fprintf(stderr, "Can't delete item from empty queue.\n");
        return false;
    }

    Node* temp = queue->start;
    *item = temp->item;

    queue->start = queue->start->next;
    queue->size--;
    if(queue->size == 0)
        queue->end = NULL;

    return true;

}

void EmptyQueue(Queue* queue){

    Item trash;
    while(queue->size != 0)
        DeleteFromQueue(&trash, queue);

}


///////////////////////////////////////////////////////////////////


bool isEqual(const Item* item1, const Item* item2){

    return *item1 == *item2;

}

static Node* getNode(unsigned n, Node* node){

    for(int i = 0 ; i < n ; i++)
        node = node->next;

    return node;

}

static void makeNode(const Item* item, Node* node){

    node->item = *item;
    node->next = NULL;

}

