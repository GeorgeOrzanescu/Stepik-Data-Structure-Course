#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct{
    int cod;
    char *denumire;
    float pret;
    float cantitate;
} produs;

typedef struct {
    produs *data;  // pointer to the data
    struct nodeCL* next, *prev; // pointers to the next and previous nodes
} nodeCL;


nodeCL* createNodeCL(produs data){
    nodeCL* newNode = (nodeCL*) malloc(sizeof(nodeCL)); // allocate memory for the new node
    newNode->data = (produs*) malloc(sizeof(produs)); // allocate memory for the new nodes product
    newNode->data->cod = data.cod;

    newNode->data->denumire = (char*) malloc(sizeof(char)*(strlen(data.denumire)+1));
    strcpy(newNode->data->denumire, data.denumire);

    newNode->data->pret = data.pret;
    newNode->data->cantitate = data.cantitate;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}


nodeCL* insertNode(nodeCL* head,nodeCL** tail ,produs data){

    nodeCL* newNode = createNodeCL(data);
    if(head == NULL){  // if list is empty
        head = newNode; // newNode is the head
        newNode->next = head; // newNode->next points to the head
        newNode->prev = head; // newNode->prev points to the head
        *tail = newNode; // tail points to the newNode
    }
    else{ // insert the new node at the end
        nodeCL *temp = head;
        while(temp->next != head){
            temp = temp->next;  // move to the last node
        }
        temp->next = newNode; // connect the last node to the newNode
        newNode->prev = temp; // newNode->prev points to the last node

        *tail = newNode; // tail points to the newNode
        (*tail)->next = head; // tail->next points to the head
        head->prev = *tail; // head->prev points to the tail
    }
    
    return head;
}

void freeCircularList(nodeCL* head){
    nodeCL* current = head;
    while(current->next != head){
        nodeCL* temp = current->next;
        free(current->data->denumire);
        free(current->data);
        free(current);
        current = temp;
    }
    free(current->data->denumire);
    free(current->data);
    free(current);
}


void printCircularList(nodeCL* head){
    nodeCL* current = head;
    do{
        printf("%d %s %5.2f %5.2f\n", current->data->cod, current->data->denumire, current->data->pret, current->data->cantitate);
        current = current->next;
    }while(current != head);  // do while loop to print circular list we can be sure that we print the head first
}


void printCircularListReverse(nodeCL* tail){
    nodeCL* current = tail;
    do{
        printf("%d %s %5.2f %5.2f\n", current->data->cod, current->data->denumire, current->data->pret, current->data->cantitate);
        current = current->prev;
    }while(current != tail);  // do while loop to print circular list we can be sure that we print the head first
}

void conversionToVector(nodeCL* head, produs** vector, int* nr){
    nodeCL *temp = head;
    while(temp->next != head){
        vector[*nr] = temp->data;
        (*nr)++;

        nodeCL* temp2 = temp->next;  // use a temp node to move to the next node
        // free(temp->data->denumire); 
        // it will not work because we are using the same memory for the vector
        // free(temp->data);
        free(temp);  // only free the node
        temp = temp2;
    }
    vector[*nr] = temp->data;
    (*nr)++;
    free(temp);
}




int main() {

    produs p1 = { 1, "taxa",1.5,10};
    produs p2 = {2, "mare", 2.5, 20};
    produs p3 = {3, "mic", 3.5, 30};

    nodeCL* head = NULL;
    nodeCL* tail = NULL;

    head = insertNode(head,&tail,p1);
    head = insertNode(head,&tail,p2);
    head = insertNode(head,&tail,p3);


    printCircularList(head);
    printCircularListReverse(tail);

    produs** vector = (produs**) malloc(sizeof(produs*)*3); // we now that we have 3 nodes
    int nr = 0; // this get incremented in the conversionToVector function

    conversionToVector(head, vector, &nr);
    for (int i = 0; i < nr; i++)
    {
       printf("%d %s %5.2f %5.2f\n", vector[i]->cod, vector[i]->denumire, vector[i]->pret, vector[i]->cantitate);
    
    }
    // free(vector);
    for (int i = 0; i < nr; i++)
    {
        free(vector[i]->denumire);
        free(vector[i]);
    }
    free(vector);
    

    freeCircularList(head);



    return 0;
}