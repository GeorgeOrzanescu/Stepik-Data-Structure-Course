#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include <string.h>


typedef struct {
	int code;
	char* brand;
	float price;
} car;


typedef struct {
	car car;
	struct nodeCoada* next;
}nodeCoada;

void put(nodeCoada** head,nodeCoada** tail, car c) {
	nodeCoada* newNode = (nodeCoada*)malloc(sizeof(nodeCoada));
	newNode->car.code = c.code;
	newNode->car.brand = (char*)malloc((strlen(c.brand) + 1) * sizeof(char));
	strcpy(newNode->car.brand, c.brand);
	newNode->car.price = c.price;
	newNode->next = NULL;


	if (*head == NULL && *tail == NULL) {
		*head = newNode;
		*tail = newNode;
	}
	else {
		newNode->next = *head;
		*head = newNode;
	}
}

void get(nodeCoada** head,nodeCoada**tail) {
    if (*tail == NULL) {
        return;
    }
    nodeCoada *curr = *head;
    // stop before tail
    while (curr->next != *tail) {
        curr = curr->next;
    }
    nodeCoada* temp = *tail;
    *tail = curr;
    curr->next = NULL; // break the link with former tail
    free(temp->car.brand);
    free(temp);

}

void printCoada(nodeCoada* head) {
	nodeCoada* curr = head;
	while (curr) {
		printf("%d" "%s" "%5.2f\n", curr->car.code, curr->car.brand, curr->car.price);
		curr = curr->next;
	}


}


// !! we need both head and tail so we can put at head 
// and pop at tail 
int main() {
	nodeCoada* head = NULL, *tail = NULL;

	car c1 = { 1,"Dacia",7500.56f };
	car c2 = { 2,"Lada",3500.52f };
	car c3 = { 3,"Ferrari",13500.52f };

	put(&head, &tail, c1);
	put(&head, &tail, c2);
	put(&head, &tail, c3);

    get(&head, &tail);

    printCoada(head);
}