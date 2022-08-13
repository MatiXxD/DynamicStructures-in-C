#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "list.h"


void x2(Item* pItem);
void printItem(Item* pItem);
char getOption(void);
char menu(void);
void lookElem(const List* list);
void getElement(const List* list);
void addItem(List* list);
void deleteItem(List* list);
void deleteItemV2(List* list);


int main(void) {

	List list;
	char ch;


	InitList(&list);
	while ((ch = menu()) != 'o') {
		switch (ch) {

		case 'e':
			printf("List %s empty.\n", IsEmpty(&list) ?
				"is" : "isn't");
			break;

		case 'f':
			printf("List %s full.\n", IsFull(&list) ?
				"is" : "isn't");
			break;

		case 'c':
			printf("List has %u elements.\n", ListSize(&list));
			break;

		case 's':
			lookElem(&list);
			break;

		case 'g':
			getElement(&list);
			break;
			
		case 'x':
			TraverseList(&list, x2);
			break;

		case 'p':
			TraverseList(&list, printItem);
			putchar('\n');
			break;

		case 'a':
			addItem(&list);
			break;

		case 'd':
			deleteItem(&list);
			break;

        case 'l':
            deleteItemV2(&list);

		}
		putchar('\n');
	}
	EmptyList(&list);
	

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
		"a) Add item\nd) Delete item\nl) Delete by value\no) Exit\n\n");

	char answer = getOption();
	while (strchr("efcsgxpadlo", answer) == NULL) {
		printf("Wrong input. Try again: ");
		answer = getOption();
	}

	return answer;

}

void lookElem(const List* list) {

	Item elem;

	printf("Enter element: ");
	scanf("%d", &elem);
	while (getchar() != '\n') continue;

	if (SeekInList(&elem, list))
		printf("Element %d was found.\n", elem);
	else
		printf("Element %d wasn't found.\n", elem);

}

void getElement(const List* list) {

	Item item;
	unsigned ind;

	printf("Enter index of element: ");
	scanf("%u", &ind);
	while (getchar() != '\n') continue;

	if (GetFromList(ind, &item, list))
		printf("Number correspond to index %u is %d.\n", ind, item);
	else
		printf("Error.\n");

}

void addItem(List* list) {

	Item elem;

	printf("Enter element: ");
	scanf("%d", &elem);
	while (getchar() != '\n') continue;

	if (AddToList(&elem, list))
		printf("Element %d was added.\n", elem);

}

void deleteItem(List* list) {

    Item item;
    unsigned ind;

	printf("Enter index of element: ");
	scanf("%u", &ind);
	while (getchar() != '\n') continue;

    if(DeleteFromList(ind, &item, list)){
        printf("Item %d was deleted.\n", item);
    }

}

void deleteItemV2(List* list){

    Item item;

    printf("Enter number you want to remove from the list.\n");
    scanf("%d", &item);
    while (getchar() != '\n') continue;

    if(DeleteValFromList(&item, list)){
        printf("Item %d was deleted.\n", item);
    }

}