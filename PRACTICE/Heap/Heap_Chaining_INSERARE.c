#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>


typedef struct {
	int id;
	char* nume;
	float valoare;
}Informatie;

typedef struct {
	Informatie informatie;
	struct NodLS* next;
}NodLS;

typedef struct {
	NodLS** informatii;
	int dimensiune;
}TabelaD;

typedef struct {
	Informatie* informatii;
	int dimensiune;
}Heap;

NodLS* creareNod(Informatie i) {
	NodLS* nodNou = (NodLS*)malloc(sizeof(NodLS));
	nodNou->informatie.id = i.id;
	nodNou->informatie.nume = (char*)malloc((strlen(i.nume) + 1) * sizeof(char));
	strcpy(nodNou->informatie.nume, i.nume);
	nodNou->informatie.valoare = i.valoare;
	nodNou->next = NULL;

	return nodNou;
}
// TABELA DISPERSIE CHAINING
int functieHash(float valoare) {
	return (int)valoare / 50;
}

void inserareTabela(TabelaD* tabelaD, Informatie i) {
	NodLS* nodDeInserat = creareNod(i);
	int pozitie = functieHash(i.valoare);

	if (pozitie < tabelaD->dimensiune) {
		if (tabelaD->informatii[pozitie] == NULL) {
			tabelaD->informatii[pozitie] = nodDeInserat;
		}
		else {
			NodLS* nodDeplasare = tabelaD->informatii[pozitie];
			while (nodDeplasare->next) {
				nodDeplasare = nodDeplasare->next;
			}
			nodDeplasare->next = nodDeInserat;
		}
	}

}

void afisareTabela(TabelaD tabelaD) {
	for (int i = 0; i < tabelaD.dimensiune; i++)
	{
		if (tabelaD.informatii[i] != NULL) {
			NodLS* nodDeplasare = tabelaD.informatii[i];
			while (nodDeplasare) {
				printf("%i -- %s -- %5.2f\n", nodDeplasare->informatie.id, nodDeplasare->informatie.nume,
					nodDeplasare->informatie.valoare);
				nodDeplasare = nodDeplasare->next;
			}
			
		}
	}
}


// HEAP 

void filtrare(Heap h,int index) {
	int indexRootNou = index;
	int indexS = 2 * index + 1;
	int indexD = 2 * index + 2;

	if (indexS < h.dimensiune && h.informatii[indexS].valoare > h.informatii[indexRootNou].valoare) {
		indexRootNou = indexS;
	}
	if (indexD < h.dimensiune && h.informatii[indexD].valoare > h.informatii[indexRootNou].valoare) {
		indexRootNou = indexD;
	}
	if (indexRootNou != index) {
		Informatie temp = h.informatii[index];
		h.informatii[index] = h.informatii[indexRootNou];
		h.informatii[indexRootNou] = temp;

		filtrare(h, indexRootNou);
	}
}

Heap inserareHeap(Heap h, Informatie i) {
	Informatie* informatiiNoi = (Informatie*)malloc(sizeof(Informatie) * (h.dimensiune + 1));
	for (int i = 0; i < h.dimensiune; i++)
	{
		informatiiNoi[i] = h.informatii[i];
	}
	informatiiNoi[h.dimensiune] = i;
	h.dimensiune++;
	free(h.informatii);
	h.informatii = informatiiNoi;

	for (int i = (h.dimensiune - 1) / 2; i >= 0; i--)
	{
		filtrare(h, i);
	}

	return h;
}

void afisareHeap(Heap h) {
	for (int i = 0; i < h.dimensiune; i++)
	{
		printf("%i -- %s -- %5.2f\n", h.informatii[i].id, h.informatii[i].nume,
			h.informatii[i].valoare);
	}
}


Heap extragere(Heap h, Informatie* infoExtras) {
	Informatie* informatiiNoi = (Informatie*)malloc(sizeof(Informatie) * (h.dimensiune - 1));
	// schimbare ultimul cu primul din heap
	Informatie temp = h.informatii[0];
	h.informatii[0] = h.informatii[h.dimensiune - 1];
	h.informatii[h.dimensiune - 1] = temp;

	// copiem informatia 
	*infoExtras = temp;

	for (int i = 0; i < h.dimensiune-1; i++)
	{
		informatiiNoi[i] = h.informatii[i];
	}
	free(h.informatii);
	h.informatii = informatiiNoi;
	h.dimensiune--;

	for (int i = (h.dimensiune - 1) / 2; i >= 0; i--)
	{
		filtrare(h, i);
	}
	return h;
}


/*
void main() {
	TabelaD tabelaD;
	tabelaD.dimensiune = 50;
	tabelaD.informatii = (Informatie**)malloc(sizeof(Informatie*) * tabelaD.dimensiune);
	for (int i = 0; i < tabelaD.dimensiune; i++)
	{
		tabelaD.informatii[i] = NULL;
	}

	Informatie info1 = { 1,"Prima Informatie",67.5 };
	Informatie info2 = { 2,"Doua Informatie",89.5 };
	Informatie info3 = { 3,"Treia Informatie",104.5 };
	Informatie info4= { 4,"Patra Informatie",156.5 };
	inserareTabela(&tabelaD, info1);
	inserareTabela(&tabelaD, info2);
	inserareTabela(&tabelaD, info3);
	inserareTabela(&tabelaD, info4);
	afisareTabela(tabelaD);
	printf("End of main!");
}
*/

void main() {
	Heap h;
	h.dimensiune = 0;
	h.informatii = (Informatie*)malloc(sizeof(Informatie) * h.dimensiune);

	Informatie info1 = { 1,"Prima Informatie",89.5 };
	Informatie info2 = { 2,"Doua Informatie",67.5 };
	Informatie info3 = { 3,"Treia Informatie",104.5 };
	Informatie info4 = { 4,"Patra Informatie",156.5 };

	h = inserareHeap(h, info1);
	h = inserareHeap(h, info2);
	h = inserareHeap(h, info3);
	h = inserareHeap(h, info4);

	afisareHeap(h);

	Informatie infoExtrasa;
	h = extragere(h, &infoExtrasa);
	printf("%i -- %s -- %5.2f\n", infoExtrasa.id, infoExtrasa.nume,
		infoExtrasa.valoare);
	printf("End of main!");
}