#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include <string.h>


typedef struct {
	int code;
	char* name;
	float value;
} data;

typedef struct { // simple list
	data data;
	struct nodeLS* next;
} nodeLS;

typedef struct {
	nodeLS** vector; // store the adress of the first node of every list
	int size;
} hashTable;


int hashFunction(int key, hashTable hashTable) {
	return key % hashTable.size;
}

int insert(hashTable hashTable, data d) {
	int position = hashFunction(d.code,hashTable);
	nodeLS* newNodeLS = (nodeLS*)malloc(sizeof(nodeLS));
	newNodeLS->data.code = d.code;
	newNodeLS->data.name = (char*)malloc((strlen(d.name) + 1) * sizeof(char));
	strcpy(newNodeLS->data.name, d.name);
	newNodeLS->data.value = d.value;
	newNodeLS->next = NULL;


	if (hashTable.vector[position] == NULL) {
		hashTable.vector[position] = newNodeLS;
	}
	else { // we collided
		nodeLS* temp = hashTable.vector[position];
		while (temp->next) {
			temp = temp->next;  // find a free position
		}
		temp->next = newNodeLS;
	}
	return position;
}

void traversalLS(nodeLS* head) {
	nodeLS* temp = head;
	while (temp) {
		printf("%d - %s - %5.2f", temp->data.code, temp->data.name, temp->data.value);
		temp = temp->next;
	}
}

void traversalHT(hashTable hashTable) {
	if (hashTable.vector != NULL) {
		for (int i = 0; i < hashTable.size; i++)
		{
			if (hashTable.vector[i] != NULL) {
				printf("Pozition %d \n", i);
				traversalLS(hashTable.vector[i]);
				printf("\n");
			}
		}
	}
}


int main() {

	hashTable HT;
	HT.size = 101;
	HT.vector = (nodeLS*)malloc(sizeof(nodeLS) * HT.size);
	for (int i = 0; i < HT.size ; i++)
	{
		HT.vector[i] = NULL;
	}
	data d1 = { 11,"Geo",45.6f };
	data d2 = { 22,"Var",42.6f };
	data d3= { 33,"Lis",55.6f };
	data d4 = { 5,"Mar",235.6f };

	insert(HT, d1);
	insert(HT, d2);
	insert(HT, d3);
	insert(HT, d4);

	traversalHT(HT);

	return 0;
}