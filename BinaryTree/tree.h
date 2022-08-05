#ifndef _TREE_H_
#define _TREE_H_
#include <stdlib.h>
#include <stdbool.h>


// Define Item, Node and Tree
typedef int Item;

typedef struct treeNode {
	struct treeNode* left;
	Item item;
	struct treeNode* right;
} Node;

typedef struct tree {
	Node* root;
	unsigned size;
} Tree;


// Initialize tree
void InitTree(Tree* tree);

// Check if tree is empty
bool IsEmptyTree(const Tree* tree);

// Check if tree is full
bool IsFullTree(const Tree* tree);

// Return size of the tree
unsigned TreeSize(const Tree* tree);

// Find item in the tree
bool FindInTree(const Tree* tree, const Item* item);

// Apply func to all elements of the tree (1 - prefix, 2 - infix, 3 - postfix)
bool TraverseInTree(const Tree* tree, void (*func)(Item* item), int mode);

// Return depth of the tree
unsigned TreeDepth(const Tree* tree);

// Add item to the tree
bool AddToTree(Item* item, Tree* tree);

// Delete item from the tree
bool DeleteFromTree(Item* item, Tree* tree);

// Empty tree
void EmptyTree(Tree* tree);

#endif