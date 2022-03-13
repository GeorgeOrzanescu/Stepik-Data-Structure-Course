#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

/*
With a Stack, the first element to come out is the last one to have gone in.
 Because of this, the Stack is considered a "Last In, First Out" (LIFO) data type.

Formally, a Stack is defined by the following functions:
• push(element): Add element to the top of the Stack
• top(): Look at the element at the top of the Stack
• pop(): Remove the element at the top of the Stack

*/

typedef struct{
    char *request;
    struct stackNode* next;
} stackNode;

void push(stackNode** top, char* request){

    // create a new node
    stackNode* newNode = (stackNode*) malloc(sizeof(stackNode));
    newNode->request = (char*) malloc(sizeof(char)*(strlen(request)+1));
    strcpy(newNode->request, request);
    
    // if the stack is empty
    if(*top == NULL){
        *top = newNode;
        newNode->next = NULL;
    }
    else{ // if the stack is not empty
        newNode->next = *top;
        *top = newNode;
    }
}

void peakTop(stackNode* top){
    if(top == NULL){
        printf("The stack is empty!\n");
    }
    else{
        printf("The top of the stack is: %s\n", top->request);
    }
}

void pop(stackNode** top){
    if(*top == NULL){
        printf("The stack is empty!\n");
    }
    else{
        stackNode *temp = (*top)->next;
        free((*top)->request);
        free(*top);

        *top = temp;
    }
}

void displayStack(stackNode* top){
    stackNode* temp = top;
    while(temp != NULL){
        printf("%s\n", temp->request);
        temp = temp->next;
    }
}


int main() {

    stackNode* top = NULL;
    push(&top, "request1");
    push(&top, "request2");
    push(&top, "request3");


    displayStack(top);
    peakTop(top);

    pop(&top);
    displayStack(top);
    pop(&top);
    displayStack(top);
    pop(&top);

    push(&top, "request1");
    push(&top, "request2");
    push(&top, "request3");

    displayStack(top);


    return 0;
}