#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <string.h>


typedef struct {
	char* model;
	int nrLocuri;
	int nrLocuriOcupate;
	float* preturiBilete;
} Avion;


Avion initAvion(const char* model, int nrLocuri, int nrLocuriOcupate, float* preturiBilete) {
	Avion avionCreat;
	avionCreat.model = (char*)malloc((strlen(model) + 1) * sizeof(char));
	strcpy(avionCreat.model, model);
	avionCreat.nrLocuri = nrLocuri;
	avionCreat.nrLocuriOcupate = nrLocuriOcupate;
	avionCreat.preturiBilete = (float*)malloc(sizeof(float));

	for (int i = 0; i < avionCreat.nrLocuriOcupate; i++)
	{
		avionCreat.preturiBilete[i] = preturiBilete[i];
	}
	return avionCreat;
}


void main() {
    float* preturiBilete = (float*)malloc(sizeof(float));
    preturiBilete[0] = 100;
    preturiBilete[1] = 200;
    preturiBilete[2] = 300;
	Avion a1 = initAvion("Airbus A330", 300, 3, preturiBilete);

    printf("%s","Program finished successfully");
}