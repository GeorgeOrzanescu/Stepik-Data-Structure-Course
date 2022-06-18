#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct {
	int pretMin;
	char* nume;
}Platforma;

typedef struct {
	Platforma* platforme;
	int dimensiune;
}Heap;


void filtrareHeap(Heap h ,int index) {
	int indexRootNou = index;
	int indexS = 2 * index + 1;
	int indexD = 2 * index + 2;

	if (indexS < h.dimensiune && h.platforme[indexS].pretMin <  h.platforme[indexRootNou].pretMin) {
		indexRootNou = indexS;
	}
	if (indexD < h.dimensiune && h.platforme[indexD].pretMin < h.platforme[indexRootNou].pretMin ) {
		indexRootNou = indexD;
	}
	if (indexRootNou != index) {
		Platforma temp = h.platforme[index]; // vechiul root
		h.platforme[index] = h.platforme[indexRootNou];
		h.platforme[indexRootNou] = temp;

		filtrareHeap(h, indexRootNou); // reluam filtrarea
	}
}


Heap inserareHeap(Heap h, Platforma p) {
	Platforma* platformeNoi = (Platforma*)malloc(sizeof(Platforma) * (h.dimensiune + 1));
	for (int i = 0; i < h.dimensiune; i++)
	{
		platformeNoi[i] = h.platforme[i];
	}
	platformeNoi[h.dimensiune] = p;
	h.dimensiune++;
	free(h.platforme);
	h.platforme = platformeNoi;

	for (int i = (h.dimensiune-1) / 2 ; i >= 0; i--)
	{
		filtrareHeap(h, i);
	}

	return h;
}

void afisareHeap(Heap h) {
	if (h.dimensiune > 0) {
		for (int i = 0; i < h.dimensiune; i++)
		{
			printf("%d -- %s\n", h.platforme[i].pretMin, h.platforme[i].nume);
		}
	}
}

Heap modificarePlatformaMinPret(Heap h,int nouPret) {
	Platforma modificata = h.platforme[0]; // cea mai mica root
	modificata.pretMin = nouPret;

	h.platforme[0] = modificata;
	for (int i = (h.dimensiune - 1) / 2; i >= 0; i--)
	{
		filtrareHeap(h, i);
	}

	return h;
}


void dezalocareHeap(Heap* h) {
	for (int i = 0; i < (*h).dimensiune; i++)
	{
		free((*h).platforme[i].nume);
	}
	free((*h).platforme);
	(*h).dimensiune = 0;
}

typedef struct {
	Platforma platforma;
	struct ArboreB* st;
	struct ArboreB* dr;
}ArboreB;


ArboreB* creareNodArboreB(Platforma p) {
	ArboreB* nodNou = (ArboreB*)malloc(sizeof(ArboreB));
	nodNou->platforma.pretMin = p.pretMin;
	nodNou->platforma.nume = (char*)malloc((strlen(p.nume) + 1) * sizeof(char));
	strcpy(nodNou->platforma.nume,p.nume);
	nodNou->dr = NULL;
	nodNou->st= NULL;
	return nodNou;
}
ArboreB* inserareNodArbore(ArboreB* root, Platforma p) {
	ArboreB* nodDeIntrodus = creareNodArboreB(p);
	if (root) {
		if (root->platforma.pretMin > nodDeIntrodus->platforma.pretMin) {
			root->st = inserareNodArbore(root->st,p);
		}
		else {
			root->dr = inserareNodArbore(root->dr,p);
		}
		return root;
	}
	else {
		return nodDeIntrodus;
	}
}



ArboreB* inserareNrPlatforme(Heap h, ArboreB* root, int numPlatforme) {
	if (numPlatforme < h.dimensiune) {
		for (int i = 0; i < numPlatforme; i++)
		{
			root = inserareNodArbore(root, h.platforme[i]);
		}
	}
	return root;
}

void afisareArboreB(ArboreB* root) {
	if (root) {
		afisareArboreB(root->st);
		printf("%d -- %s\n", root->platforma.pretMin, root->platforma.nume);
		afisareArboreB(root->dr);

	}
}


void dezalocareArbore(ArboreB* root) {
	if (root) {
		ArboreB* stanga = root->st;
		ArboreB* dreapta = root->dr;
		free(root->platforma.nume);
		free(root->st);
		free(root);
		dezalocareArbore(stanga);
		dezalocareArbore(dreapta);
	}
}
void main() {
	Heap h;
	h.dimensiune = 0;
	h.platforme = (Platforma*)malloc(sizeof(Platforma)*h.dimensiune);

	FILE* f = fopen("platforme.txt", "r");
	int n = 0;
	char buffer[20];
	if (f) {
		fscanf(f, "%d", &n);
		for (int i = 0; i < n; i++)
		{
			Platforma p;
			fscanf(f, "%d", &p.pretMin);
			fscanf(f, "%s", buffer);
			p.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
			strcpy(p.nume, buffer);

			h = inserareHeap(h, p);
		}
	}
	fclose(f);

	h = modificarePlatformaMinPret(h, 10);
	dezalocareHeap(&h);
	afisareHeap(h);

	ArboreB* root = NULL;
	root = inserareNrPlatforme(h, root, 4);
	//dezalocareArbore(root);
	afisareArboreB(root);
	printf("End of main!");
}