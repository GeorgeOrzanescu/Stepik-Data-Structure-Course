#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct{
    int id;
    char* name;
    float storage;
} data;

void readVector(data* vector, int size){

    char buffer[30];
    for(int i = 0; i < size; i++){
        printf("Enter id: ");
        scanf("%d", &vector[i].id);

        printf("Enter name: ");
        scanf("%s", buffer);
        vector[i].name = (char*)malloc(sizeof(char)*(strlen(buffer)+1));
        strcpy(vector[i].name, buffer);

        printf("Enter storage: ");
        scanf("%f", &vector[i].storage);
    }
}

void printVector(data* vector, int size){
    for(int i = 0; i < size; i++){
        printf("%d %s %.2f\n", vector[i].id, vector[i].name, vector[i].storage);
    }
}

void freeVector(data* vector, int size){
    for(int i = 0; i < size; i++){
        free(vector[i].name);
    }
    free(vector);
}

int main() {

    int size;
    printf("Enter size: ");
    scanf("%d", &size);

    data* vector = (data*) malloc(size * sizeof(data));
    readVector(vector, size);
    printVector(vector, size);
    freeVector(vector, size);


    return 0;
}