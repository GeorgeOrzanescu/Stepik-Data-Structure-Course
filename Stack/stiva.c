#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>


typedef struct{
    int zi, luna, an;
} data;

typedef struct{
    data data;
    char *destinatar;
    float dimensiune;
} email;

typedef struct {
    email inf;
    struct nodstiva *next;
} nodstiva;


void push(nodstiva** varf,email e){
    // create a new node and copy all the data
    nodstiva *nou = (nodstiva *)malloc(sizeof(nodstiva));
    nou->inf.destinatar = (char *)malloc((strlen(e.destinatar) + 1) * sizeof(char));
    strcpy(nou->inf.destinatar, e.destinatar);

    nou->inf.data.zi = e.data.zi;
    nou->inf.data.luna = e.data.luna;
    nou->inf.data.an = e.data.an;

    nou->inf.dimensiune = e.dimensiune;
    nou->next = NULL;

    if(*varf == NULL){
        *varf = nou;
    }
    else{
        nou->next = *varf;
        *varf = nou;
    }
    
}   

void pop(nodstiva** varf){

    if(*varf == NULL){
        printf("Stiva este goala!");
    }

    nodstiva *temp = (*varf)->next;
    free((*varf)->inf.destinatar);
    free((*varf));

    *varf = temp;
}

void traversare(nodstiva* varf){
    nodstiva* current = varf;
    if(current == NULL){
        printf("Stiva este goala!");
        return;
    }
    do{
        printf("%d %d %d --- %s --- %5.2f\n",
               current->inf.data.zi, current->inf.data.luna, current->inf.data.an,
               current->inf.destinatar, current->inf.dimensiune);
        current = current->next;
    } while (current != NULL);
}

int main(){

    int n;
    nodstiva *varf = NULL;
    email e;
    char buffer[20];

    // read from file 
    FILE *f = fopen("fisier.txt", "r");
    fscanf(f, "%d", &n);

    for (int i = 0; i < n; i++)
    {
        fscanf(f, "%s", buffer);
        e.destinatar = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(e.destinatar, buffer);
        // be carefull at the format specifier
        fscanf(f, "%f", &e.dimensiune);
        fscanf(f, "%d", &e.data.zi);
        fscanf(f, "%d", &e.data.luna);
        fscanf(f, "%d", &e.data.an);

        push(&varf, e);
        free(e.destinatar); // pentru al refolosi iteratia urmatoare
    }
    
    fclose(f);



    traversare(varf);

    pop(&varf);
    pop(&varf);
    pop(&varf);
    printf("------DUPA POP------\n");
    traversare(varf);

    return 0;
}