#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdio.h>
#include<string.h>

typedef struct {
	int cod;
	int pret;
	char* categorie;
}Echipament;

typedef struct {
	Echipament echipament;
	struct NodArb* left;
	struct NodArb* right;
}NodArb;


NodArb* creareNod(Echipament e) {
	NodArb* nodNou = (NodArb*)malloc(sizeof(NodArb));
	nodNou->echipament.cod = e.cod;
	nodNou->echipament.categorie = (char*)malloc(sizeof(char) * (strlen(e.categorie) + 1));
	strcpy(nodNou->echipament.categorie, e.categorie);
	nodNou->echipament.pret = e.pret;

	nodNou->left = NULL;
	nodNou->right = NULL;

	return nodNou;
}

NodArb* inserare(NodArb* radacina, Echipament e) {
	NodArb* nodDeInserat = creareNod(e);
	if (radacina != NULL) {
		if (e.cod < radacina->echipament.cod) {
			radacina->left = inserare(radacina->left, e);
		}
		else {
			radacina->right = inserare(radacina->right, e);
		}
		return radacina;
	}

	else {
		return nodDeInserat;
	}
}

void afisare(NodArb* radacina) {
	if (radacina != NULL) {
		afisare(radacina->left);
		printf("\n%d -- %s -- %d\n", radacina->echipament.cod, radacina->echipament.categorie,
			radacina->echipament.pret);
		afisare(radacina->right);
	}
}

void cautarePretCelMaiMare(NodArb* radacina, char* categoria,int* max,int* cod) {
	if (radacina != NULL) {
		if (strcmp(radacina->echipament.categorie, categoria) == 0)
		{
			if (radacina->echipament.pret > *max) {
				*max = radacina->echipament.pret;
				*cod = radacina->echipament.cod;
			}
		}
	}

	cautarePretCelMaiMare(radacina->right, categoria, max, cod);
	cautarePretCelMaiMare(radacina->left, categoria, max, cod);
}

typedef struct {
	Echipament echipament;
	struct NodLD* next;
	struct NodLD* prev;
}NodLD;

NodLD* creareNodLD(Echipament e) {
	NodLD* nodNou = (NodLD*)malloc(sizeof(NodLD));
	nodNou->echipament.cod = e.cod;
	nodNou->echipament.categorie = (char*)malloc(sizeof(char) * (strlen(e.categorie) + 1));
	strcpy(nodNou->echipament.categorie, e.categorie);
	nodNou->echipament.pret = e.pret;

	nodNou->prev = NULL;
	nodNou->next = NULL;

	return nodNou;
}
// echipamente mai ieftine decat un anumit pret
NodLD* copiereArboreInLD(NodArb* root, NodLD* rootLD, int pret) {
	if (root != NULL) {
		if (root->echipament.pret <= pret) {
			NodLD* nodNou = creareNod(root->echipament);
			if (rootLD == NULL) {
				rootLD = nodNou;
			}
			else {
				NodLD* nodDeplasare = rootLD;
				while (nodDeplasare->next) {
					nodDeplasare = nodDeplasare->next;
				}
				nodDeplasare->next = nodNou;
				nodNou->prev = nodDeplasare;
			}
		}
		copiereArboreInLD(root->left, rootLD, pret);
		copiereArboreInLD(root->right, rootLD, pret);
	}
	return rootLD;
}


void afisareLD(NodLD* rootLD) {
	NodLD* nodDeplasare = rootLD;
	while (nodDeplasare) {
		printf("\n%d-- %s -- %d", nodDeplasare->echipament.cod, nodDeplasare->echipament.categorie,
			nodDeplasare->echipament.pret);
		nodDeplasare = nodDeplasare->next;
	}
}

void main() {

	NodArb* radacina = NULL;
	
	FILE* f = fopen("text.txt", "r");
	int n;
	char buffer[20];
	if (f) {
		fscanf(f, "%d", &n);
		for (int i = 0; i < n; i++)
		{
			Echipament e;
			fscanf(f, "%d", &e.cod);
			fscanf(f, "%d", &e.pret);
			fscanf(f, "%s", buffer);
			e.categorie = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
			strcpy(e.categorie, buffer);

			radacina = inserare(radacina, e);
		}
	}
	fclose(f);
	int max = 0;
	int cod = 0;
	cautarePretCelMaiMare(radacina, "Pahar", &max, &cod);
	printf("%d  -- %d", max, cod);
	//afisare(radacina);

	NodLD* rootLD = NULL;
	rootLD = copiereArboreInLD(radacina, rootLD, 50);
	afisareLD(rootLD);
}