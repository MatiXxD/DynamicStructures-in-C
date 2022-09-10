#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "queue.h"


void x2(Item* pItem);
void printItem(Item* pItem);
char getOption(void);
char menu(void);
void lookElem(const Queue* queue);
void getElement(const Queue* queue);
void addItem(Queue* queue);
void deleteItem(Queue* queue);


int main(void) {

	Queue queue;
	char ch;


	InitQueue(&queue);
	while ((ch = menu()) != 'o') {
		switch (ch) {

		case 'e':
			printf("List %s empty.\n", IsEmpty(&queue) ?
				"is" : "isn't");
			break;

		case 'f':
			printf("List %s full.\n", IsFull(&queue) ?
				"is" : "isn't");
			break;

		case 'c':
			printf("List has %u elements.\n", QueueSize(&queue));
			break;

		case 's':
			lookElem(&queue);
			break;

		case 'g':
			getElement(&queue);
			break;

		case 'x':
			TraverseQueue(&queue, x2);
			break;

		case 'p':
			TraverseQueue(&queue, printItem);
			putchar('\n');
			break;

		case 'a':
			addItem(&queue);
			break;

		case 'd':
			deleteItem(&queue);
			break;

		}
		putchar('\n');
	}
	EmptyQueue(&queue);


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

void lookElem(const Queue* queue) {

	Item elem;

	printf("Enter element: ");
	scanf("%d", &elem);
	while (getchar() != '\n') continue;

	if (InQueue(&elem, queue))
		printf("Element %d was found.\n", elem);
	else
		printf("Element %d wasn't found.\n", elem);

}

void getElement(const Queue* queue) {

	Item item;
	unsigned ind;

	printf("Enter index of element: ");
	scanf("%u", &ind);
	while (getchar() != '\n') continue;

	if (GetFromQueue(ind, &item, queue))
		printf("Number correspond to index %u is %d.\n", ind, item);
	else
		printf("Error.\n");

}

void addItem(Queue* queue) {

	Item elem;

	printf("Enter element: ");
	scanf("%d", &elem);
	while (getchar() != '\n') continue;

	if (AddToQueue(&elem, queue))
		printf("Element %d was added.\n", elem);

}

void deleteItem(Queue* queue) {

    Item item;
    if(DeleteFromQueue(&item, queue)){
        printf("Item %d was deleted.\n", item);
    }

}
