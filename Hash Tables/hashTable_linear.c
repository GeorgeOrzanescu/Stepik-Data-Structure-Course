#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<malloc.h>

typedef struct{
    int code;
    char *name;
    float grade;
} student;

typedef struct {
    int size;
    student **table;
} hashTable;

int hashFunction(int key,hashTable hashTable){
    return key % hashTable.size;  // return eanything which does not generate many collisions
    // !! for f(x1) = y it should not exist a f(x2) = y
}

int insert(hashTable hashTable,student* s){
    int pozition;
    if(hashTable.table != NULL){
        pozition = hashFunction(s->code,hashTable);
        if(hashTable.table[pozition] == NULL){
            hashTable.table[pozition] = s;
        }
        else{
            int i = 1;
            while (pozition + i < hashTable.size){ // move to next adjacent position
                if(hashTable.table[pozition + i] == NULL){ // if empty store info
                    hashTable.table[pozition + i] = s;
                    pozition += i;
                    break;
                }
                i++;

            }
        }
    }
    return pozition;
}

void traversal(hashTable hashTable){
    if(hashTable.table != NULL){
        for(int i = 0; i < hashTable.size; i++){
            if(hashTable.table[i] != NULL){
                printf("%d %s %f\n",hashTable.table[i]->code,hashTable.table[i]->name,hashTable.table[i]->grade);
            }
        }
    }
}

void dezalocation(hashTable hashTable){
    if(hashTable.table != NULL){
        for(int i = 0; i < hashTable.size; i++){
            if(hashTable.table[i] != NULL){
                free(hashTable.table[i]->name);
                free(hashTable.table[i]);
            }
        }
        free(hashTable.table);
    }
}


int main()
{
    hashTable hashTable;
    hashTable.size = 10;
    hashTable.table = (student **)malloc(sizeof(student *) * hashTable.size);
    for(int i = 0; i < hashTable.size; i++){
        hashTable.table[i] = NULL; // initialize all positions to NULL
    }

    student *s;
    char buffer[20]; // buffer for name
    s = (student *)malloc(sizeof(student));
    
    printf("Enter code: ");
    scanf("%d",&s->code);
    printf("Enter name: ");
    scanf("%s",buffer);
    s->name = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(s->name,buffer);
    printf("Enter grade: ");
    scanf("%f",&s->grade);
    insert(hashTable,s);
    traversal(hashTable);
    dezalocation(hashTable);

    return 0;
}