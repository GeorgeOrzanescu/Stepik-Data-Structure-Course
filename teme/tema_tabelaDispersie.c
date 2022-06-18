#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include <string.h>

typedef enum CanalIncasare
{
    electronic,
    ghiseu
} CanalIncasare;

typedef struct {
    float valoare;
    char *dataEmitere;
    char *dataScadenta;
    enum CanalIncasare canalIncasare;
} Factura;

typedef struct {
    Factura** vector;
    int size;
}tabelaDispersie;

int hashFunction(int key, tabelaDispersie tD) { // key va fi valoarea facturii 
    return key%10 + key/10;
}

// insert Factura in tabelaDispersie base on valoare

void insert(tabelaDispersie tD, Factura *f) {
    int pozition;
    if (tD.vector != NULL) {
        pozition = hashFunction(f->valoare, tD); // get hash value based on valoare
        printf("%d\n", pozition);
        if (tD.vector[pozition] == NULL) { // check if generated value is free
            tD.vector[pozition] = f; // assign the data to the generated position
        }
        else {
            int index = 1;
            while (pozition + index < tD.size) { // find a position smaller then max 
                if (tD.vector[pozition + index] == NULL) { // check if empty
                    tD.vector[pozition + index] = f; // assign the data 
                    pozition += index; // update position
                    break;
                }
                index++;
            }
        }
    }
}

Factura citireIncasare(float valoare,const char* dataEmitere,const char* dataScadenta,enum CanalIncasare c){
    Factura f;
    f.valoare = valoare;
    f.dataEmitere = (char *)malloc((strlen(dataEmitere) + 1) * sizeof(char));
    strcpy(f.dataEmitere, dataEmitere);
    f.dataScadenta = (char *)malloc((strlen(dataScadenta) + 1) * sizeof(char));
    strcpy(f.dataScadenta, dataScadenta);
    if(c == electronic){
        f.canalIncasare = electronic;
    }
    else {
        f.canalIncasare = ghiseu;
    }

    return f;
}

void displayTabelaD(tabelaDispersie tD) {
    for (int i = 0; i < tD.size; i++) {
        if (tD.vector[i] != NULL) {
            printf(" %d %5.2f ", i,tD.vector[i]->valoare);
        }
    }
}


void main() {
    tabelaDispersie tD;
    tD.size = 100;
    tD.vector = (Factura**)malloc(tD.size * sizeof(Factura*));
    for (int i = 0; i < tD.size; i++) {
        tD.vector[i] = NULL;
    }

    // Factura f1 = { 100, "01.01.2020", "31.12.2020", electronic };
    // Factura f2 = { 200, "01.01.2020", "31.12.2020", electronic };
    // Factura f3 = { 300, "01.01.2020", "31.12.2020", electronic };
    // Factura f4 = { 400, "01.01.2020", "31.12.2020", electronic };
    // Factura f5 = { 500, "01.01.2020", "31.12.2020", electronic };
    // Factura f6 = { 345, "01.01.2020", "31.12.2020", ghiseu };


    // insert(tD, &f1);
    // insert(tD, &f2);
    // insert(tD, &f3);
    // insert(tD, &f4);
    // insert(tD, &f5);
    // insert(tD, &f6);
    FILE *f = fopen("facturi.txt", "r");
    if (f == NULL) {
        printf("File not found");
        return;
    }
    char buffer[100];
    int n = 0;
    fscanf(f, "%f", &n);
    for (int i = 0; i < n; i++)
    {
        float valoare;
        char *dataEmitere;
        char *dataScadenta;
        enum CanalIncasare canalIncasare;
        fscanf(f, "%f", &valoare);
        fscanf(f, "%s", buffer);
        dataEmitere = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(dataEmitere, buffer);
        free(buffer);
        fscanf(f, "%s", buffer);
        dataScadenta = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(dataScadenta, buffer);
        free(buffer);
        fscanf(f, "%s", buffer);
        if (strcmp(buffer,"electronic") == 0)
           { canalIncasare = electronic;}
        else {
            canalIncasare = ghiseu;
        }

        Factura f = citireIncasare(valoare, dataEmitere, dataScadenta, canalIncasare);
        insert(tD, &f);
    }

    

    displayTabelaD(tD);
}