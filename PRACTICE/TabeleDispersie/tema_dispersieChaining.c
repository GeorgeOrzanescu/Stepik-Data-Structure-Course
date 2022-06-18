#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef enum {
	electronic, ghiseu
} canalIncasare;

typedef struct {
	float valoare;
	char* dataEmitere;
	char* dataScadenta;
	canalIncasare canalIncasare;
}Factura;

typedef struct {
	Factura factura;
	struct NodeLS* next;
}NodeLS;

int hashFunction(float valoareFactura) {
	return (int)valoareFactura / 50;
}

typedef struct {
	NodeLS** facturi; // stocam head-ul fiecare liste 
	int dimensiune;
}TabelaDispersie;


NodeLS* creareNod(Factura f) {
	NodeLS* nodeNou = (NodeLS*)malloc(sizeof(NodeLS));
	nodeNou->factura.canalIncasare = f.canalIncasare;
	nodeNou->factura.dataEmitere = (char*)malloc((strlen(f.dataEmitere) + 1) * sizeof(char));
	strcpy(nodeNou->factura.dataEmitere, f.dataEmitere);
	nodeNou->factura.dataScadenta = (char*)malloc((strlen(f.dataScadenta) + 1) * sizeof(char));
	strcpy(nodeNou->factura.dataScadenta, f.dataScadenta);
	nodeNou->factura.valoare = f.valoare;

	nodeNou->next = NULL;

	return nodeNou;
}


void inserare(TabelaDispersie tabelaD, Factura f) {
	NodeLS* nodeNou = creareNod(f);
	int pozitie = hashFunction(f.valoare);

	if (tabelaD.facturi[pozitie] == NULL) {
		tabelaD.facturi[pozitie] = nodeNou;
	}
	else {
		NodeLS* nodDeplasare = tabelaD.facturi[pozitie];
		while (nodDeplasare->next != NULL) {
			nodDeplasare = nodDeplasare->next;
		}
		nodDeplasare->next = nodeNou;
	}
}


void printareTabelaD(TabelaDispersie tabelaD) {
	for (int i = 0; i < tabelaD.dimensiune; i++)
	{
		if (tabelaD.facturi[i] != NULL) {
			printf("ListaSimpla de pe pozitia: %d\n", i);
			NodeLS* nodDeplasare = tabelaD.facturi[i];
			while (nodDeplasare) {
				
				printf("%f - %s - %s - %d\n",
					nodDeplasare->factura.valoare,
					nodDeplasare->factura.dataEmitere,
					nodDeplasare->factura.dataScadenta,
					nodDeplasare->factura.canalIncasare);
				nodDeplasare = nodDeplasare->next;
			}
		}
	}
}

int stergereFacturaDupaValoare(float valoare, TabelaDispersie tabelaD) {
	int pozitie = hashFunction(valoare, tabelaD);
	if (tabelaD.facturi[pozitie] == NULL) {
		return -1;
	}
	else {
		NodeLS* nodTemp= NULL;
		NodeLS* nodDeplasare = tabelaD.facturi[pozitie];
		if (nodDeplasare->factura.valoare == valoare) {
			nodTemp = nodDeplasare->next;
			free(nodDeplasare->factura.dataEmitere);
			free(nodDeplasare->factura.dataScadenta);
			free(nodDeplasare);
			tabelaD.facturi[pozitie] = nodTemp;
			return 0;
		}
		while (nodDeplasare->next) {
			if (nodDeplasare->factura.valoare != valoare) {
				nodTemp = nodDeplasare;
				nodDeplasare = nodDeplasare->next;
			}
			if (nodDeplasare->factura.valoare == valoare) {
				nodTemp->next = nodDeplasare->next;
				free(nodDeplasare->factura.dataEmitere);
				free(nodDeplasare->factura.dataScadenta);
				free(nodDeplasare);
				return 0;
			}
		}
		return -1;
	}
}

void afisareSumeIncasate(TabelaDispersie tabelaD) {
	float sumeElectronice = 0.0f;
	float sumeGhiseu = 0.0f;

	for (int i = 0; i < tabelaD.dimensiune; i++)
	{
		if (tabelaD.facturi[i] != NULL) {
			NodeLS* nodDeplasare = tabelaD.facturi[i];
			while (nodDeplasare) {
				if (nodDeplasare->factura.canalIncasare == 0) {
					sumeElectronice += nodDeplasare->factura.valoare;
				}
				else {
					sumeGhiseu += nodDeplasare->factura.valoare;
				}
				nodDeplasare = nodDeplasare->next;
			}
		}
	}

	printf("Total suma incasata electronic: %5.2f\n", sumeElectronice);
	printf("Total suma incasata ghiseu: %5.2f\n", sumeGhiseu);
}


void main() {

	TabelaDispersie tabelaD;
	tabelaD.dimensiune = 101;
	tabelaD.facturi = (NodeLS**)malloc(sizeof(NodeLS*) * tabelaD.dimensiune);
	for (int i = 0; i < tabelaD.dimensiune; i++)
	{
		tabelaD.facturi[i] = NULL;
	}


	FILE* f = fopen("facturi.txt", "r");
	int n = 0;
	fscanf(f, "%d", &n);
	char buffer[20];
	if (f) {
		for (int i = 0; i < n; i++)
		{
			Factura factura;
			fscanf(f, "%f", &factura.valoare);
			fscanf(f, "%s", buffer);
			factura.dataEmitere = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
			strcpy(factura.dataEmitere, buffer);

			fscanf(f, "%s", buffer);
			factura.dataScadenta = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
			strcpy(factura.dataScadenta, buffer);

			fscanf(f, "%s", buffer);
			if (strcmp(buffer, "electronic") == 0) {
				factura.canalIncasare = electronic;
			}
			else {
				factura.canalIncasare = ghiseu;
			}

			inserare(tabelaD, factura);
		}
	
	}

	//printf("Factura gasita: %d\n", stergereFacturaDupaValoare(89.8, tabelaD));
	printareTabelaD(tabelaD);
	afisareSumeIncasate(tabelaD);
	printf("End of main!");
}