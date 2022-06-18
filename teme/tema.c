#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

/*
Se implementează o aplicație pentru centralizarea rezervărilor clienților unui restaurant. Rezervările ajung în sistem prin două modalități: apel telefonic, respectiv aplicație mobilă. 

Rezervările sunt onorate în ordinea priorității, dată de durata rezervării (număr de ore în care o masă este rezervată), indiferent de canalul pe care acestea sunt transmise.

(0.5p) Scrieţi funcţia pentru inserarea unei noi rezervări in structura de tip coadă de priorități în care prioritatea este dată de durata rezervării unei mese. 

Testarea funcţiei este realizată prin afişarea la consolă a structurii în urma inserării. 

(0.5p) Scrieţi funcţia pentru determinarea rezervărilor a căror durată depășește 3 ore. Rezervările rezultate sunt stocate înt-un vector alocat dinamic. Funcţia nu include operaţii I/O cu tastatura/monitorul.

(0.5p) Scrieţi funcţia care permite generarea unui raport într-un fișier text privind toate rezervările efectuate de un anumit client, pe baza datelor din structura coadă de priorități. 

(0.5p) Scrieţi funcţia care extrage o rezervare din coada de priorități. Rezultatul execuţiei funcţiei este validat prin afişarea la consolă a structurii în urma extragerii.

Text răspuns

*/

typedef struct {
    int idRezervare;
    int nrOreRezervare;
    char *canalRezervare;

} Rezervare;

typedef struct nodeCoada {
    Rezervare rezervare;
    struct nodeCoada* next;
    struct nodeCoada* prev;
} nodeCoada;

void inserareRezervare(nodeCoada** head, nodeCoada** tail, Rezervare r) {
    nodeCoada* newNode = (nodeCoada*)malloc(sizeof(nodeCoada));
    newNode->rezervare.idRezervare = r.idRezervare;
    newNode->rezervare.nrOreRezervare = r.nrOreRezervare;
    newNode->rezervare.canalRezervare = (char*)malloc((strlen(r.canalRezervare) + 1) * sizeof(char));
    strcpy(newNode->rezervare.canalRezervare, r.canalRezervare);

    newNode->next = NULL;
    newNode->prev = NULL;


    if (*head == NULL && *tail == NULL) {
        *head = newNode;
        *tail = newNode;
    }

    else {
        if (newNode->rezervare.nrOreRezervare > (*head)->rezervare.nrOreRezervare) {
            newNode->next = *head;
            *head = newNode;
        }
        else {
            nodeCoada* current = *head;
            while (current->next != NULL && current->next->rezervare.nrOreRezervare >= newNode->rezervare.nrOreRezervare) {
                current = current->next;
            }
            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;
        }
    }
}

void printCoada(nodeCoada* head) {
    nodeCoada* curr = head;
    while (curr) {
        printf("Rezervare id: %d " "durata de: %d ore " "rezervare facuta prin: %s\n", curr->rezervare.idRezervare, curr->rezervare.nrOreRezervare, curr->rezervare.canalRezervare);
        curr = curr->next;
    }
}

int numRezPesteTreiOre(nodeCoada* head) {
    int nrRez = 0;
    nodeCoada* curr = head;
    while (curr) {
        if (curr->rezervare.nrOreRezervare > 3) {
            nrRez++;
        }
        curr = curr->next;
    }
    return nrRez;
}

Rezervare* rezervariPesteTreiOre(nodeCoada* head){
    int nrRezervari = numRezPesteTreiOre(head);
    Rezervare* rezervari = (Rezervare*)malloc(nrRezervari * sizeof(Rezervare));
    nodeCoada* curr = head;
    int i = 0;
    while (curr) {
        if (curr->rezervare.nrOreRezervare > 3) {
            rezervari[i] = curr->rezervare;
            i++;
        }
        curr = curr->next;
    }
    return rezervari;
}

void generareRaportTxtRezervari(nodeCoada* head){
    FILE* f = fopen("raport.txt", "w");
    nodeCoada* curr = head;
    while (curr) {
        fprintf(f, "Rezervare id: %d " "durata de: %d ore " "rezervare facuta prin: %s\n", curr->rezervare.idRezervare, curr->rezervare.nrOreRezervare, curr->rezervare.canalRezervare);
        curr = curr->next;
    }
    fclose(f);
}

Rezervare extrageRezervare(nodeCoada** head){
    nodeCoada* curr = *head;
    Rezervare rezervare;
    rezervare.idRezervare = curr->rezervare.idRezervare;
    rezervare.nrOreRezervare = curr->rezervare.nrOreRezervare;
    rezervare.canalRezervare = (char*)malloc((strlen(curr->rezervare.canalRezervare) + 1) * sizeof(char));
    strcpy(rezervare.canalRezervare, curr->rezervare.canalRezervare);

    *head = curr->next;
    free(curr->rezervare.canalRezervare);
    free(curr);
    return rezervare;
}

int main() {

    nodeCoada* head = NULL;
    nodeCoada* tail = NULL;

    Rezervare r1 = { 1, 2, "telefon" };
    Rezervare r2 = { 2, 3, "telefon" };
    Rezervare r3 = { 3, 4, "mobil" };

    inserareRezervare(&head, &tail,r1);
    inserareRezervare(&head,&tail, r2);
    inserareRezervare(&head,&tail, r3);


    printCoada(head);
    int nrRezervariPesteTreiOre = numRezPesteTreiOre(head);
    Rezervare* rezervari = rezervariPesteTreiOre(head);
    printf("Rezervari peste trei ore:\n");
    for (int i = 0; i < nrRezervariPesteTreiOre; i++) {
        printf("Rezervare id: %d " "durata de: %d ore" "rezervare facuta prin: %s\n", rezervari[i].idRezervare, rezervari[i].nrOreRezervare, rezervari[i].canalRezervare);
    }

    //generareRaportTxtRezervari(head);
    Rezervare rez = extrageRezervare(&head);
    printf("Rezervare extrasa:");
    printf("Rezervare id: %d " "durata de: %d ore" "rezervare facuta prin: %s\n", rez.idRezervare, rez.nrOreRezervare, rez.canalRezervare);
    printCoada(head);
	return 0;
}