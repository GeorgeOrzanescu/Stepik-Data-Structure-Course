#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

typedef struct {
	int nrFactura;
	char* dataEmitere;
	char* numeClient;
	float valoare;
	int nrProduse;
}Factura;

typedef struct {
	Factura factura;
	struct NodAVL* stanga;
	struct NodAVL* dreapta;
}NodAVL;

NodAVL* creareNodAVL(Factura f) {
	NodAVL* nodNou = (NodAVL*)malloc(sizeof(NodAVL));
	nodNou->factura.nrFactura = f.nrFactura;
	nodNou->factura.valoare = f.valoare;
	nodNou->factura.nrProduse = f.nrProduse;
	nodNou->factura.dataEmitere = (char*)malloc(sizeof(char) * (strlen(f.dataEmitere) + 1));
	strcpy(nodNou->factura.dataEmitere, f.dataEmitere);
	nodNou->factura.numeClient = (char*)malloc(sizeof(char) * (strlen(f.numeClient) + 1));
	strcpy(nodNou->factura.numeClient, f.numeClient);

	nodNou->stanga = NULL;
	nodNou->dreapta = NULL;

	return nodNou;
}

int inaltimeArb(NodAVL* root) {
	if (root) {
		int inaltimeS = inaltimeArb(root->stanga);
		int inaltimeD = inaltimeArb(root->dreapta);
		return 1 + max(inaltimeS, inaltimeD);
	}
	else {
		return 0;
	}
}

int gradEchilibru(NodAVL* root) {
	if (root) {
		int inaltimeS = inaltimeArb(root->stanga);
		int inaltimeD = inaltimeArb(root->dreapta);
		return inaltimeS - inaltimeD;
	}
	else {
		return 0;
	}
}

NodAVL* rotatieDreapta(NodAVL* root) {
	if (root) {
		NodAVL* rootNou = root->stanga;
		root->stanga = rootNou->dreapta;
		rootNou->dreapta = root;

		return rootNou;
	}

}
NodAVL* rotatieStanga(NodAVL* root) {
	if (root) {
		NodAVL* rootNou = root->dreapta;
		root->dreapta = rootNou->stanga;
		rootNou->stanga = root;

		return rootNou;
	}
	
}


NodAVL* inserare(NodAVL* root, Factura f) {

	if (root != NULL) {
		if (root->factura.valoare > f.valoare) {
			root->stanga = inserare(root->stanga, f);
		}
		else {
			root->dreapta = inserare(root->dreapta, f);
		}
		// echilibrare
		int gradEchilibrare = gradEchilibru(root);
		if (gradEchilibrare == 2) { // balansat spre stanga
			// rotatie dreapta
			if (gradEchilibru(root->stanga) == 1) {
				root = rotatieDreapta(root);
			}
			else {
				//rotatie stanga
				//rotatie dreapta
				root->stanga = rotatieStanga(root->stanga);
				root = rotatieDreapta(root);
			}
		}
		if (gradEchilibrare == -2) { //balansat spre dreapta
				// rotatie stanga
				if (gradEchilibru(root->dreapta) == -1) {
					root = rotatieStanga(root);
				}
				//rotatie dreapta
				//rotatie stanga
				else {
					root->dreapta = rotatieDreapta(root->dreapta);
					root = rotatieStanga(root);
				}
		}
			return root;
		}
		else {
			NodAVL* nodDeIntrodus = creareNodAVL(f);
			return nodDeIntrodus;
		}
	}

void afisareAVL(NodAVL* root) //INORDER  Stanga --> ROOT --> Dreapta
{
	if (root) {
		afisareAVL(root->stanga);
		printf("%d -- %s -- %f\n", root->factura.nrFactura, root->factura.numeClient,
			root->factura.valoare);
		afisareAVL(root->dreapta);
	}
}

void aplicareComision(NodAVL* root) //INORDER  Stanga --> ROOT --> Dreapta
{
	if (root) {
		aplicareComision(root->stanga);
		root->factura.valoare += (root->factura.valoare * 0.025);
		aplicareComision(root->dreapta);
	}
}



void main() {

	NodAVL* root = NULL;
	Factura f1 = { 1,"26/11/2022","George O.",345.5,6 };
	Factura f2 = { 2,"15/11/2022","Marina O.",32.7,1 };
	Factura f3 = { 3,"31/11/2022","Denisa V.",64,2 };
	Factura f4 = { 4,"22/11/2022","Claudia R.",145.5,6 };


	root = inserare(root, f1);
	root = inserare(root, f2);
	root = inserare(root, f3);
	root = inserare(root, f4);
	afisareAVL(root);
	aplicareComision(root);
	printf("%d",inaltimeArb(root));
	printf("\nEnd of main!");
	afisareAVL(root);
}