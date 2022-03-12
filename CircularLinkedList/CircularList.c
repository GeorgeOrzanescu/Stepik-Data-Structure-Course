#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<malloc.h>

// CIRCULAR UNIDIRECTIONAL LINKED LIST IMPLEMENTATION
typedef struct {
    int data;
    struct nodeCL* next;
} NodeCL;


NodeCL* createNodeCL(int data){
    NodeCL* newNode = (NodeCL*) malloc(sizeof(NodeCL));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
// insertion at the end
NodeCL* insertNode(NodeCL* head, int data){
    NodeCL* newNode = createNodeCL(data);
    if(head == NULL){  // if list is empty
        return newNode;
    }
    if (head->next == NULL){ // second element case (head->next == NULL)
        head->next = newNode;
        newNode->next = head;
        return head;
    }

    NodeCL* current = head;
    while(current->next != head){
        current = current->next;
    }
    current->next = newNode;
    newNode->next = head;
    return head;
}

void printCircularList(NodeCL* head){
    NodeCL* current = head;
    do{
        printf("%d ", current->data);
        current = current->next;
    }while(current != head);  // do while loop to print circular list we can be sure that we print the head first
    printf("\n");
}


NodeCL* deleteNode(NodeCL* head, int data){
    NodeCL* current = head;
    
    if(current->data == data){ // if head is the node we want to delete
        NodeCL* temp = current;
        while(temp->next != head){
            temp = temp->next;  // move to the last node
        }
        temp->next = head->next; // connect the last node to the second node after the head
        free(head);// delete the head
        return temp->next; // return the new head
    }

    while(current->next != head){ // if the node we want to delete is not the head
        current = current->next;
        NodeCL *temp = current->next;
        if(temp->data == data){
            current->next = temp->next;
            free(temp);
            return head;
        }
    }

    printf("Not found\n");
    return head;
   
}
int main(){

    NodeCL *head = NULL;
    head = insertNode(head, 1);
    head = insertNode(head, 2);
    head = insertNode(head, 3);
    head = insertNode(head, 4);
    head = insertNode(head, 5);


    head = deleteNode(head,5);
    printCircularList(head);
    return 0;
}