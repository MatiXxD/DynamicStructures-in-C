#include <stdio.h>
#include "tree.h"


static bool toLeft(const Item* item1, const Item* item2);
static bool toRight(const Item* item1, const Item* item2);
static bool isEqual(const Item* item1, const Item* item2);
static bool recursiveSearch(const Node* node, const Item* item);
static void prefixTraverse(const Node* node, void (*func)(Item* item));
static void infixTraverse(const Node* node, void (*func)(Item* item));
static void postfixTraverse(const Node* node, void (*func)(Item* item));
static unsigned getDepth(const Node* node, unsigned depth);
static void copyToNode(Node* node, const Item* item);
static Node* makeNode(const Item* item);
static void addNode(Node** node, Node* newNode);
static bool getParent(const Item* item, const Node* node, Node** parent);
static void deleteNode(Node** node);
static void deleteNodes(Node* root);


void InitTree(Tree* tree) {

	tree->root = NULL;
	tree->size = 0;

}

bool IsEmptyTree(const Tree* tree) {

	return tree->size == 0;

}

bool IsFullTree(const Tree* tree) {

	Node* temp = (Node*)malloc(sizeof(Node));
	if (temp == NULL)
		return true;

	free(temp);
	return false;

}

unsigned TreeSize(const Tree* tree) {

	return tree->size;

}

bool FindInTree(const Tree* tree, const Item* item) {

	return recursiveSearch(tree->root, item);

}

bool TraverseInTree(const Tree* tree, void (*func)(Item* item), int mode) {

	if (mode < 1 || mode > 3) {
		fprintf(stderr, "Wrong mode.\n");
		return false;
	}

	if (mode == 1)			prefixTraverse(tree->root, func);
	else if (mode == 2)		infixTraverse(tree->root, func);
	else					postfixTraverse(tree->root, func);

	return true;

}

unsigned TreeDepth(const Tree* tree) {

	return getDepth(tree->root, 0);

}

bool AddToTree(Item* item, Tree* tree) {

	if (IsFullTree(tree)) {
		fprintf(stderr, "The tree is full.\n");
		return false;
	}
	else if (recursiveSearch(tree->root, item)) {
		fprintf(stderr, "This item already in the tree.\n");
		return false;
	}

	Node* newNode = makeNode(item);
	if (newNode == NULL) {
		fprintf(stderr, "Memory error.\n");
		return false;
	}

	tree->size++;
	if (tree->root == NULL)
		tree->root = newNode;
	else
		addNode(&tree->root, newNode);

	return true;

}

bool DeleteFromTree(Item* item, Tree* tree) {

	if (IsEmptyTree(tree)) {
		fprintf(stderr, "Tree is empty.\n");
		return false;
	}
	
	Node* parent = NULL;
	if (!getParent(item, tree->root, &parent)) {
		fprintf(stderr, "Item wasn't found in the tree");
		return false;
	}

	if (parent == NULL) 
		deleteNode(&tree->root);
	else if (parent->left != NULL && isEqual(&parent->left->item, item)) 
		deleteNode(&parent->left);
	else
		deleteNode(&parent->right);

	tree->size--;

	return true;

}

void EmptyTree(Tree* tree) {

	if (tree != NULL) {
		deleteNodes(tree->root);
		tree->root = NULL;
		tree->size = 0;
	}

}




static bool toLeft(const Item* item1, const Item* item2) {

	return *item1 < *item2;

}

static bool toRight(const Item* item1, const Item* item2) {

	return *item1 > *item2;

}

static bool isEqual(const Item* item1, const Item* item2) {

	return *item1 == *item2;

}

static bool recursiveSearch(const Node* node, const Item* item) {

	if (node == NULL) return false;
	else if (isEqual(item, &node->item)) return true;

	if (toLeft(item, &node->item))
		return recursiveSearch(node->left, item);
	else if (toRight(item, &node->item))
		return recursiveSearch(node->right, item);

}

static void prefixTraverse(const Node* node, void (*func)(Item* item)) {

	if (node == NULL) return;

	(*func)(&node->item);
	prefixTraverse(node->left, func);
	prefixTraverse(node->right, func);

}

static void infixTraverse(const Node* node, void (*func)(Item* item)) {

	if (node == NULL) return;

	infixTraverse(node->left, func);
	(*func)(&node->item);
	infixTraverse(node->right, func);

}

static void postfixTraverse(const Node* node, void (*func)(Item* item)) {

	if (node == NULL) return;

	postfixTraverse(node->left, func);
	postfixTraverse(node->right, func);
	(*func)(&node->item);

}

static unsigned getDepth(const Node* node, unsigned depth) {

	if (node == NULL) return depth;

	unsigned leftDepth = getDepth(node->left, depth + 1);
	unsigned rightDepth = getDepth(node->right, depth + 1);

	return leftDepth >= rightDepth ? leftDepth : rightDepth;

}

static void copyToNode(Node* node, const Item* item) {

	node->item = *item;

}

static Node* makeNode(const Item* item) {

	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode != NULL) {
		copyToNode(newNode, item);
		newNode->left = NULL;
		newNode->right = NULL;
	}

	return newNode;

}

static void addNode(Node** node, Node* newNode) {

	if (*node == NULL) {
		*node = newNode;
		return;
	}

	if (toLeft(&newNode->item , &(*node)->item))
		addNode(&(*node)->left, newNode);
	else if (toRight(&newNode->item, &(*node)->item))
		addNode(&(*node)->right, newNode);

}

static bool getParent(const Item* item, const Node* node, Node** parent) {

	if (node == NULL) return false;
	else if (isEqual(item, &node->item)) return true;

	if (toLeft(item, &node->item)) {
		*parent = node;
		return getParent(item, node->left, parent);
	}
	else if (toRight(item, &node->item)) {
		*parent = node;
		return getParent(item, node->right, parent);
	}
	else {
		fprintf(stderr, "Location error.\n");
		return false;
	}
	
}

static void deleteNode(Node** node) {

	Node* temp;

	// Only left side
	if ((*node)->right == NULL) {
		temp = *node;
		*node = (*node)->left;
		free(temp);
	}
	
	// Only right side
	else if ((*node)->left == NULL) {
		temp = *node;
		*node = (*node)->right;
		free(temp);
	}

	// Both sides
	else {
		for (temp = (*node)->left; temp->right != NULL; )
			temp = temp->right;
		temp->right = (*node)->right;
		temp = *node;
		*node = (*node)->left;
		free(temp);
	}

}

static void deleteNodes(Node* root) {

	if (root != NULL) {
		Node* temp = root->right;
		deleteNodes(root->left);
		free(root);
		deleteNodes(temp);
	}

}
