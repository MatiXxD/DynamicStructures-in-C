#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "tree.h"


void x2(Item* pItem);
void printItem(Item* pItem);
char getOption(void);
char menu(void);
void lookElem(const Tree* tree);
void addItem(Tree* tree);
void deleteItem(Tree* stack);


int main(void) {

	Tree tree;
	char ch;


	InitTree(&tree);
	while ((ch = menu()) != 'o') {
		switch (ch) {

		case 'e':
			printf("Tree %s empty.\n", IsEmptyTree(&tree) ?
				"is" : "isn't");
			break;

		case 'f':
			printf("Tree %s full.\n", IsFullTree(&tree) ?
				"is" : "isn't");
			break;

		case 'c':
			printf("Tree has %u elements.\n", TreeSize(&tree));
			break;

		case 's':
			lookElem(&tree);
			break;

		case 't':
			printf("Tree depth is %u.\n", TreeDepth(&tree));
			break;

		case 'x':
			TraverseInTree(&tree, x2, 2);
			break;

		case 'p':
			TraverseInTree(&tree, printItem, 2);
			putchar('\n');
			break;

		case 'a':
			addItem(&tree);
			break;

		case 'd':
			deleteItem(&tree);
			break;

		}
		putchar('\n');
	}
	EmptyTree(&tree);


	return 0;

}


void x2(Item* pItem) {

	*pItem *= 2;

}

void printItem(Item* pItem) {

	printf("%d ", *pItem);

}

char getOption(void) {

	char ch = getchar();
	while (getchar() != '\n')
		continue;

	return tolower(ch);

}

char menu(void) {

	printf("Enter what you want to do:\n");
	printf("e) Is empty?\nf) Is full?\nc) Items count\ns) Find item\n"
		"t) Tree depth\nx) Apply x2 func\np) Apply print func\n"
		"a) Add item\nd) Delete item\no) Exit\n\n");

	char answer = getOption();
	while (strchr("efcstxpado", answer) == NULL) {
		printf("Wrong input. Try again: ");
		answer = getOption();
	}

	return answer;

}

void lookElem(const Tree* tree) {

	Item elem;

	printf("Enter element: ");
	scanf("%d", &elem);
	while (getchar() != '\n') continue;

	if (FindInTree(tree, &elem))
		printf("Element %d was found.\n", elem);
	else
		printf("Element %d wasn't found.\n", elem);

}

void addItem(Tree* tree) {

	Item elem;

	printf("Enter element: ");
	scanf("%d", &elem);
	while (getchar() != '\n') continue;

	if (AddToTree(&elem, tree))
		printf("Element %d was added.\n", elem);

}

void deleteItem(Tree* tree) {

	Item elem;
	
	printf("Enter element: ");
	scanf("%d", &elem);
	while (getchar() != '\n') continue;

	if (DeleteFromTree(&elem, tree))
		printf("Element %d was deleted.\n", elem);

}