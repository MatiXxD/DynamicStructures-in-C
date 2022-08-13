#include <stdio.h>
#include <stdlib.h>
#include "list.h"


// Prototypes of local functions 
static bool isEqual(const Item* item1, const Item* item2);
static Node* getNode(unsigned n, Node* start);
static void makeNode(const Item* item, Node* node);


// List function 
void InitList(List* list){

    list->start = NULL;
    list->size = 0;

}

bool IsEmpty(const List* list){

    return list->size == 0;

}

bool IsFull(const List* list){

    Node* temp = (Node*)malloc(sizeof(Node));
    if(temp == NULL)
        return true;

    free(temp);
    return false;

}

unsigned ListSize(const List* list){

    return list->size;

}

bool SeekInList(const Item *item, const List* list){

    Node* start = list->start;
    while(start != NULL){
        if(isEqual(item, &start->item))
            return true;
        start = start->next;
    }

    return false;

}

bool GetFromList(unsigned n, Item* item, const List* list){

    if(list->size < n){
        fprintf(stderr, "Out of range. List size is %u.\n", list->size);
        return false;
    }

    Node* temp = getNode(n, list->start);
    *item = temp->item;

    return true;

}

void TraverseList(List* list, void (*func)(Item* item)){

    Node* temp = list->start;
    while(temp != NULL){
        func(&temp->item);
        temp = temp->next;
    }

}

bool AddToList(const Item* item, List* list){

    Node* newNode = NULL;
    Node* node = NULL;

    if(IsFull(list)){
        fprintf(stderr, "List is full.\n");
        return false;
    }

    newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL){
        fprintf(stderr, "Memory error.\n");
        return false;
    }
    makeNode(item, newNode);

    node = list->start;
    if(node == NULL)
        list->start = newNode;
    else{
        while(node->next != NULL)
            node = node->next;
        node->next = newNode;
    }
    list->size++;

    return true;

}

bool DeleteFromList(unsigned n, Item* item, List* list){

    Node* temp = NULL;
    Node* dltNode = NULL;

    if(list->size <= n){
        fprintf(stderr, "Out of range. List size is %u.\n", list->size);
        return false;
    }

    if(n == 0){
        temp = list->start;
        *item = temp->item;
        list->start = list->start->next;
        free(temp);
    }
    else{
        temp = getNode(n-1, list->start);
        *item = temp->next->item;
        dltNode = temp->next;
        temp->next = temp->next->next;
        free(dltNode);
    }
    
    list->size--;
    if(list->size == 0) list->start = NULL;

    return true;

}

bool DeleteValFromList(const Item* item, List* list){

    Node* current = NULL;
    Node* previous = NULL;

    if(!SeekInList(item, list)){
        fprintf(stderr, "Item wasn't found in the list.\n");
        return false;
    }

    current = list->start;
    while(current != NULL){
        if(isEqual(&current->item, item)) break;
        previous = current;
        current = current->next;
    }

    if(previous == NULL){
        list->start = current->next;
        free(current);
    }
    else{
        previous->next = current->next;
        free(current);
    }

    list->size--;
    if(list->size == 0) list->start = NULL;

    return true;

}

void EmptyList(List* list){

    Node* node = list->start;
    Node* temp = NULL;

    while(node != NULL){
        temp = node;
        node = node->next;
        free(temp);    
    }

}


// Local functions
static bool isEqual(const Item* item1, const Item* item2){

    return *item1 == *item2;

}

static Node* getNode(unsigned n, Node* start){

    for(int i = 0 ; i < n ; i++)
        start = start->next;

    return start;

}

static void makeNode(const Item* item, Node* node){

    node->item = *item;
    node->next = NULL;

}