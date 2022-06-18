#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include <string.h>


/* 
Implement an application that solves situations of taking over pacients waiting to enter the family doctor's office.

(0.5p) Write the function to create a priority queue structure that contains pacient data.

The "pacient" structure is defined as follows: pacient code (int), pacient name (char *), problem description (char *), age (float), priority (int).

Example: {1234, "Ionescu Gigel", "Cold Symptoms", 23, 3}. The priorities according to which the entrance to the office is made are defined as follows:

Category 1 - pregnant women and children under 1 year of age (priority = 5),

Category 2 - children over 1 year old (priority = 4),

Category 3 - the rest of the pacients having priorities 1, 2 or 3 depending on the number of hours they waited in line.

(0.5p) Write the function for inserting a new pacient into the queue, a function that receives as a parameter the category to which the new pacient belongs (as char * category),

so that it is given the appropriate priority. In the case of category 3, the priority with the value 1 is implicitly considered.

(0.5p) Write the function that determines the number of pregnant women and children under the age of 1 waiting in line to enter the office.

The function is called in main () and the returned result (number of pregnant women and children under 1 year old) is displayed on the console.

(0.5p) Write the function to make a statistic in a text file about the problems that pacients presented to the doctor

(Example: Cold symptoms - 3 pacients, Back pain - 2 pacients, Headache - 1 pacient).
*/

typedef struct {
    int codPacient;
    char* nume;
    char* descriere;
    float varsta;
    int prioritate;
} Pacient;

typedef struct NodCoada{
    Pacient pacient;
    struct NodCoada* next;
    struct NodCoada* prev;
} NodCoada;

/*
Write the function for inserting a new pacient into the queue, a function that receives as a parameter the category to which the new pacient belongs (as char * category),
so that it is given the appropriate priority. In the case of category 3, the priority with the value 1 is implicitly considered.
*/

NodCoada* inserare(NodCoada* cap,NodCoada** ultim, Pacient pacient,const char* categorie) {
    NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada));
   nou->pacient.codPacient = pacient.codPacient;
   nou->pacient.nume = (char*)malloc(sizeof(char)*(strlen(pacient.nume) + 1));
   strcpy(nou->pacient.nume, pacient.nume);
    nou->pacient.descriere = (char*)malloc(sizeof(char)*(strlen(pacient.descriere) + 1));
    strcpy(nou->pacient.descriere, pacient.descriere);
    nou->pacient.varsta = pacient.varsta;
    
    nou->next = NULL;
    nou->prev = NULL;


    if (strcmp(categorie,"Categoria 1")== 0) {
        nou->pacient.prioritate = 5;
    }
    else if (strcmp(categorie, "Categoria 2") == 0) {
        nou->pacient.prioritate = 4;
    }
    else {
        nou->pacient.prioritate = 1;
    }

    if(cap == NULL && *ultim==NULL){
        cap = nou;
        *ultim = nou;
        return cap;
    }
    // insert based on highest priority
    if (nou->pacient.prioritate > cap->pacient.prioritate) {
        nou->next = cap;
        cap->prev = nou;
        cap = nou;
        return cap;
    }
    if(nou->pacient.prioritate <= (*ultim)->pacient.prioritate){
        (*ultim)->next = nou;
        nou->prev = *ultim;
        *ultim = nou;
        return cap; 
    }
    else {
        NodCoada* current = cap;
        while (current->next != NULL && current->next->pacient.prioritate >= nou->pacient.prioritate) {
            current = current->next;
        }
        nou->next = current->next;
        current->next = nou;
        nou->prev = current;
    }

    return cap;
}

void printCoada(NodCoada* cap) {
    NodCoada* current = cap;
    while (current != NULL) {
        printf("%d %s %s %f %d\n", current->pacient.codPacient, current->pacient.nume, current->pacient.descriere, current->pacient.varsta, current->pacient.prioritate);
        current = current->next;
    }
}

int getNumCategorie1(NodCoada* cap) {
    int numar = 0;
    NodCoada* current = cap;
    while (current != NULL) {
        if (current->pacient.prioritate == 5) {
            numar++;
        }
        current = current->next;
    }
    return numar;
}
int marimeLista(NodCoada* cap) {
    int numar = 0;
    NodCoada* current = cap;
    while (current != NULL) {
        numar++;
        current = current->next;
    }
    return numar;
}

void printToFile(NodCoada* cap, const char* fileName) {
    FILE* f = fopen(fileName, "w");
    NodCoada* current = cap;
    while (current != NULL) {
        fprintf(f, "%s - %s - %d\n", current->pacient.nume,current->pacient.descriere, current->pacient.varsta);
        current = current->next;
    } 
    
    fclose(f);
}

void main() {
    NodCoada* cap = NULL;
    NodCoada* ultim = NULL;

    Pacient pacient1 = { 1, "Ionescu Gigel", "Cold Symptoms", 23, 0};
    Pacient pacient2 = { 2, "Popescu Ion", "Back Pain", 1, 0 };
    Pacient pacient3 = {3, "Popescu Maria", "Back Pain",51, 0 };
    Pacient pacient4= {4, "Denisa", "Couf Pain",51, 0 };

    cap = inserare(cap, &ultim, pacient1, "Categoria 2");
    cap = inserare(cap, &ultim, pacient2, "Categoria 1");
    cap = inserare(cap, &ultim, pacient3, "Categoria 2");
    cap = inserare(cap, &ultim, pacient4, "Categoria 3");

    printCoada(cap);

}