#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>
#include <string.h>

typedef struct {
    char* nume;
    float value;
    char* symbol;
} cryptoCoin;




int main() {
    cryptoCoin myCrypto[3];
    FILE *f = fopen("cont.txt", "r");

    char buffer[20];
    for (int i = 0; i < 3; i++)
    {
        cryptoCoin cc;

        fscanf(f, "%s", buffer);
        cc.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(cc.nume, buffer);
        
        fscanf(f, "%f", &cc.value);

        fscanf(f, "%s", buffer);
        cc.symbol = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(cc.symbol, buffer);

        myCrypto[i] = cc;
    }


    for (int i = 0; i < 3; i++)
    {
        printf("%s\n", myCrypto[i].nume);
        printf("%5.2f\n", myCrypto[i].value);
        printf("%s\n", myCrypto[i].symbol);
    }

    return 0;
}