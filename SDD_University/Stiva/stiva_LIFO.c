#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include <string.h>


typedef struct {
	char* name;
	int num;
} data;

typedef struct {
	data data;
	struct nodeStiva* next;
}nodeStiva;

nodeStiva* push(nodeStiva* top, data data) {
	nodeStiva* newTop = (nodeStiva*)malloc(sizeof(nodeStiva));
	newTop->data.name = (char*)malloc((strlen(data.name) + 1) * sizeof(char));
	strcpy(newTop->data.name, data.name);
	newTop->data.num = data.num;
	newTop->next = NULL;

	if (top == NULL) {
		return newTop;
	}

	newTop->next = top;
	return newTop;
}


data pop(nodeStiva** top) {
	if (top == NULL) {
		return;
	}

	nodeStiva* temp = *top;
	data data;
	data.name = (char*)malloc((strlen(temp->data.name) + 1) * sizeof(char));
	strcpy(data.name, temp->data.name);
	data.num = temp->data.num;
	*top = temp->next;
	free(temp->data.name);
	free(temp);
	return data;
}



void printStiva(nodeStiva* top) {
	nodeStiva* current = top;
	while (current != NULL) {
		printf("%s %d", current->data.name, current->data.num);
		current = current->next;
	}
}


int main() {
	nodeStiva* top = NULL;

	data d1 = { "firstNode",3 };
	data d2 = { "secondNoe",7 };
	data d3 = { "thirdNode",1 };

	top = push(top, d1);
	top = push(top, d2);
	top = push(top, d3);

	data dataPoped = pop(&top);

	printf("%s %d\n", dataPoped.name, dataPoped.num);
	printStiva(top);
}