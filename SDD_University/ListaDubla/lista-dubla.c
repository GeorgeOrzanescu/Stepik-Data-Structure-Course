#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>
#include<string.h>


typedef struct {
    char* namePilot;
    int numPass;
} plane;


typedef struct {
    plane plane;
    struct nodeLd* next;
    struct nodeLd* prev;
} nodeLd;

nodeLd* createNode(plane plane,nodeLd* next,nodeLd* prev) {
    nodeLd* newNode = (nodeLd*)malloc(sizeof(nodeLd));
    newNode->plane.namePilot = (char*)malloc((strlen(plane.namePilot) + 1) * sizeof(char));
    strcpy(newNode->plane.namePilot, plane.namePilot);
    newNode->plane.numPass = plane.numPass;
    newNode->next = next;
    newNode->prev = prev;
    return newNode;

}

nodeLd* insertNode(plane plane, nodeLd* head, nodeLd** tail) {
    nodeLd* nodeToInsert = createNode(plane, head, NULL);
    if (head == NULL) {
        head = nodeToInsert;
        *tail = nodeToInsert;
    }
    else {
        head->prev = nodeToInsert;
        return nodeToInsert;
    }
    return head;
}

void printList(nodeLd* head) {
    nodeLd* current = head;
    while (current != NULL) {
        printf("%s %d\n", current->plane.namePilot, current->plane.numPass);
        current = current->next;
    }
}

void printListReverse(nodeLd* tail){
    nodeLd* current = tail;
    while (current) {
        printf("%s %d\n", current->plane.namePilot, current->plane.numPass);
        current = current->prev;
    }
}

void main() {
    nodeLd* head = NULL;
    nodeLd* tail = NULL;

    plane plane1 = { "Pilot1", 10 };
    plane plane2 = { "Pilot2", 20 };
    plane plane3 = { "Pilot3", 30 };

    head = insertNode(plane1, head, &tail);
    head = insertNode(plane2, head, &tail);
    head = insertNode(plane3, head, &tail);

    printList(head);
    printListReverse(tail);
}