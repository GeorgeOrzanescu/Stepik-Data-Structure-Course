#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>
#include <string.h>


typedef struct {
    char* name;
    float value;
} info;

typedef struct {
    info data;
    struct nodeLs* next;
} nodeLs;

// insert a new node at the beginning of the list
nodeLs* insertNode(info info, nodeLs* nextNode) {
    nodeLs* newNode;
    newNode = (nodeLs*)malloc(sizeof(nodeLs));
    newNode->data.name = (char*)malloc((strlen(info.name) + 1) * sizeof(char*));
    strcpy(newNode->data.name, info.name);
    newNode->data.value = info.value;

    newNode->next = nextNode;
    return newNode;
}


nodeLs* deleteNode(char* name, nodeLs* nextNode) {
    nodeLs* current;
    nodeLs* prev;

    // if the list is empty
    if (nextNode == NULL) {
        printf("List is empty\n");
        return;
    }

    // if the node to be deleted is the first node
    if (strcmp(nextNode->data.name, name) == 0) {
        current = nextNode->next;
        free(nextNode->data.name);
        free(nextNode);
        return current;
    }

    // search for the node to be deleted
    prev = nextNode;
    current = nextNode->next;
    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            prev->next = current->next;
            free(current->data.name);
            free(current);
            return nextNode;
        }
        prev = current;
        current = current->next;

    }

    // if node is not found
    printf("Node not found\n");
}


void printList(nodeLs* listaSimpla) {
    nodeLs* currentNode = listaSimpla;
    while (currentNode) {
        printf("%s %f\n", currentNode->data.name, currentNode->data.value);
        currentNode = currentNode->next;
    }
}

void main() {

    nodeLs* listaSimpla = NULL;


    info inf1 = { "Bitcoin", 35000.43f };
    info inf2 = { "Ethereum", 100.44f };
    info inf3 = { "Dogecoin", 0.71f };
    info inf4 = { "Litecoin", 10.45f };

    listaSimpla = insertNode(inf1, listaSimpla);
    listaSimpla = insertNode(inf2, listaSimpla);
    listaSimpla = insertNode(inf3, listaSimpla);
    listaSimpla = insertNode(inf4, listaSimpla);


    listaSimpla = deleteNode("Bitcoin", listaSimpla);

    printList(listaSimpla);
}