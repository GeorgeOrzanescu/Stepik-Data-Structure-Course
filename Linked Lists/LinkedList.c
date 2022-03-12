#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct {
    int id;
    char* name;
    float storage;
} data;

// SIMPLE LINKED LIST NODE
typedef struct {
    data data;
    struct node* next; // pointer to next node
} node;

node* createNode(data data){
    node* newNode = (node*) malloc(sizeof(node));
    // newNode->data = data; // problems with char* adress in data (shallow copy)
    newNode->data.id = data.id;
    newNode->data.name = (char*) malloc(sizeof(char)*(strlen(data.name)+1));
    strcpy(newNode->data.name, data.name);
    newNode->data.storage = data.storage;
    newNode->next = NULL;

    return newNode;
}
// insertion at the beginning
node* insertNodeFront(node* head, data data){
    node* newNode = createNode(data);
    newNode->next = head;
    return newNode;
}
// insertion at the end
node* insertNodeBack(node* head, data data){
    node* newNode = createNode(data);
    if(head == NULL){  // if list is empty
        return newNode;
    }
    node* current = head;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = newNode;
    return head;
}

void deleteList(node* head){
    node* current = head;
    while(current != NULL){
        node* temp = current; // save current node
        current = current->next; // move to next node

        free(temp->data.name);
        free(temp);
    }
}


void printList(node* head){
    node* current = head;
    while(current != NULL){
        printf("%d %s %.2f\n", current->data.id, current->data.name, current->data.storage);
        current = current->next;
    }
}
// find a node by id
void searchNode(node* head, int id){
    node* current = head;
    while(current != NULL){
        if(current->data.id == id){
            return printf("%d %s %.2f\n", current->data.id, current->data.name, current->data.storage);
        }
        current = current->next;
    }
    printf("Not found\n");
}

int main(){

    node* head = NULL;
    data data1 = {1, "John", 10.5};
    data data2 = {2, "Jane", 20.5};
    data data3 = {3, "Jack", 30.5};
    data data4 = {4, "Jill", 40.5};
    data data5 = {5, "Joe", 50.5};

    head = insertNodeFront(head, data1);
    head = insertNodeFront(head, data2);
    head = insertNodeFront(head, data3);

    head = insertNodeBack(head, data4);
    head = insertNodeBack(head, data5);

    printList(head);

    searchNode(head, 2);
    deleteList(head);

    return 0;
}