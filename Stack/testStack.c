#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "stack.h"


void x2(Item* pItem);
void printItem(Item* pItem);
char getOption(void);
char menu(void);
void lookElem(const Stack* stack);
void getElement(const Stack* stack);
void addItem(Stack* stack);
void deleteItem(Stack* stack);


int main(void) {

	Stack stack;
	char ch;


	InitStack(&stack);
	while ((ch = menu()) != 'o') {
		switch (ch) {

		case 'e':
			printf("Stack %s empty.\n", IsEmpty(&stack) ?
				"is" : "isn't");
			break;

		case 'f':
			printf("Stack %s full.\n", IsFull(&stack) ?
				"is" : "isn't");
			break;

		case 'c':
			printf("Stack has %u elements.\n", StackCount(&stack));
			break;

		case 's':
			lookElem(&stack);
			break;

		case 'g':
			getElement(&stack);
			break;
			
		case 'x':
			ApplyFunc(&stack, x2);
			break;

		case 'p':
			ApplyFunc(&stack, printItem);
			putchar('\n');
			break;

		case 'a':
			addItem(&stack);
			break;

		case 'd':
			deleteItem(&stack);
			break;

		}
		putchar('\n');
	}
	DeleteStack(&stack);
	

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
		"g) Get element\nx) Apply x2 func\np) Apply print func\n"
		"a) Add item\nd) Delete item\no) Exit\n\n");

	char answer = getOption();
	while (strchr("efcsgxpado", answer) == NULL) {
		printf("Wrong input. Try again: ");
		answer = getOption();
	}

	return answer;

}

void lookElem(const Stack* stack) {

	Item elem;

	printf("Enter element: ");
	scanf("%d", &elem);
	while (getchar() != '\n') continue;

	if (FindItem(elem, stack))
		printf("Element %d was found.\n", elem);
	else
		printf("Element %d wasn't found.\n", elem);

}

void getElement(const Stack* stack) {

	Item item;
	unsigned ind;

	printf("Enter index of element: ");
	scanf("%u", &ind);
	while (getchar() != '\n') continue;

	if (GetElem(ind, &item, stack))
		printf("Number correspond to index %u is %d.\n", ind, item);
	else
		printf("Error.\n");

}

void addItem(Stack* stack) {

	Item elem;

	printf("Enter element: ");
	scanf("%d", &elem);
	while (getchar() != '\n') continue;

	if (Push(elem, stack))
		printf("Element %d was added.\n", elem);

}

void deleteItem(Stack* stack) {

	Item elem;

	if (Pop(&elem, stack))
		printf("Element %d was deleted.\n", elem);

}
