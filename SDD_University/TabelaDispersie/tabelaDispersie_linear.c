#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include <string.h>

typedef struct {
    int code;
    char *name;
    float grade;
} student;

typedef struct {
    student **vector;
    int size;
} hashTableLinear;

int hashFunction(int key,hashTableLinear HashT){
    int prime = 7;
    return key + (HashT.size % prime) + prime;
}

int insert(hashTableLinear HashT,student* s){
    int pozition;
    if(HashT.vector != NULL){  
        pozition = hashFunction(s->code, HashT); // get hash value based on code
        if (HashT.vector[pozition]== NULL){ // check if generated value is free
            HashT.vector[pozition] = s; // assign the data to the generated position
        }
        else{
            int index = 1;
            while (pozition + index < HashT.size){ // find a position smaller then max 
                if(HashT.vector[pozition+index] == NULL){ // check if empty
                    HashT.vector[pozition + index] = s; // assign the data 
                    pozition += index; // update position
                    break;
                }
                index++;
            }
        }
    }
    return pozition;
}

void dezalocation(hashTableLinear HashT){
    if (HashT.vector != NULL){
        for (int i = 0; i < HashT.size; i++)
        {
            if(HashT.vector[i] != NULL){
                free(HashT.vector[i]->name);
                free(HashT.vector[i]);
            }
        }
        free(HashT.vector);
    }
}

int
main()
{

    hashTableLinear HashT;
    HashT.size = 100;
    HashT.vector = (student*)malloc(sizeof(student) * HashT.size);
    
    for (int i = 0; i < HashT.size; i++)
    {
        HashT.vector[i] = NULL;
    }


    student s1 = {1, "George", 6.7f};
    student s2 = {3, "Maria", 9.9f};
    student s3 = {3, "Vasile", 7.8f};

    int p1 = insert(HashT, &s1);
    int p2 = insert(HashT, &s2);
    int p3 = insert(HashT, &s3);

    printf("%d %d %d", p1, p2, p3);

    return 0;
}