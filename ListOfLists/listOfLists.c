#include<stdio.h>
#include<malloc.h>


/*
List of lists is a data structure that is used to store a collection of lists.
In this example we will be using a list of lists to store a collection of payments.
Each sublist of the main list will be a collection of payments based on the chanel.
*/



typedef struct{
    int id;
    char *beneficiary;
    float amount;
    char *chanel;
} payment;

typedef struct {
    payment info;
    struct nodeSecList *next;
} nodeSecList;

typedef struct{
    struct nodeSecList * info;
    struct nodePrimList *next;
} nodePrimList;


void insertSecList(nodeSecList** headSecList,payment payment){
    nodeSecList *new = (nodeSecList *)malloc(sizeof(nodeSecList));
    new->info.id = payment.id;
    new->info.beneficiary=(char*)malloc((strlen(payment.beneficiary)+1) * sizeof(char));
    strcpy(new->info.beneficiary, payment.beneficiary);
    new->info.amount = payment.amount;
    new->info.chanel=(char*)malloc((strlen(payment.chanel)+1) * sizeof(char));
    strcpy(new->info.chanel, payment.chanel);
    new->next = NULL;

    if(*headSecList == NULL){
        *headSecList = new;
    }
    else{
        nodeSecList *temp = *headSecList;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = new;
    }
}

void insertPrimList(nodePrimList** headPrimList,nodeSecList* headSecList){
    nodePrimList *new = (nodePrimList *)malloc(sizeof(nodePrimList));
    new->info = headSecList;
    new->next = NULL;
    if(*headPrimList == NULL){
        *headPrimList = new;
    }
    else{
        nodePrimList *temp = *headPrimList;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = new;
    }
}

void traversSecList(nodeSecList* headSecList){
    nodeSecList *temp = headSecList;
    while(temp != NULL){
        printf("\nId = %d , Beneficiary: %s, Amount: %5.2f, Chanel: %s",temp->info.id,temp->info.beneficiary,temp->info.amount,temp->info.chanel);
        temp = temp->next;
    }
}

void traversPrimList(nodePrimList* headPrimList){
    nodePrimList *temp = headPrimList;
    int i = 1;
    while(temp != NULL){
        printf("\n Sublist: %d", i);
        traversSecList(temp->info);
        temp = temp->next;
        i++;
    }
}

void deleteSecList(nodeSecList* headSecList){
    nodeSecList *temp = headSecList;
    while(temp != NULL){
        nodeSecList *temp2 = temp->next;
        free(temp->info.beneficiary);
        free(temp->info.chanel);
        free(temp);
        temp = temp2;
    }
}

void deletePrimList(nodePrimList* headPrimList){
    nodePrimList *temp = headPrimList;
    while(temp != NULL){
        nodePrimList *temp2 = temp->next;
        deleteSecList(temp->info);
        free(temp);
        temp = temp2;
        }
}



void main(){

    int n;
    payment payment;
    nodePrimList* headPrimList = NULL;
    nodeSecList* headSecList1 = NULL;  // one for each list Physical
    nodeSecList* headSecList2 = NULL; // one for each list Internet

    char buffer[20];
    FILE *f = fopen("payments.txt","r");
    fscanf(f,"%d",&n); // read the number of payments

    for(int i = 0; i < n; i++){
        fscanf(f,"%d",&payment.id);
        fscanf(f,"%s",buffer);
        payment.beneficiary = (char*)malloc((strlen(buffer)+1) * sizeof(char));
        strcpy(payment.beneficiary, buffer);
        fscanf(f,"%f",&payment.amount);
        fscanf(f,"%s",buffer);
        payment.chanel = (char*)malloc((strlen(buffer)+1) * sizeof(char));
        strcpy(payment.chanel, buffer);

        if(strcmp(payment.chanel,"Physical") == 0){
            insertSecList(&headSecList1,payment);
        }
        if(strcmp(payment.chanel,"Internet") == 0){
            insertSecList(&headSecList2,payment);
        }

        free(payment.beneficiary); // free the memory allocated for the beneficiary
        free(payment.chanel); // free the memory allocated for the chanel
        
    }
    // insert the sublists in the main list
    insertPrimList(&headPrimList,headSecList1);
    insertPrimList(&headPrimList,headSecList2);

    // print the main list
    traversPrimList(headPrimList);
    deletePrimList(headPrimList);
}