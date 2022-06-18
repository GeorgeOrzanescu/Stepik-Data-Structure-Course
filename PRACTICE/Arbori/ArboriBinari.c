#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <string.h>
#include<stdlib.h>


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
	avionCreat.preturiBilete = (float*)malloc(sizeof(float) * avionCreat.nrLocuriOcupate);

	for (int i = 0; i < avionCreat.nrLocuriOcupate; i++)
	{
		avionCreat.preturiBilete[i] = preturiBilete[i];
	}
	return avionCreat;
}

void afisareAvion(Avion avion) {
	printf("%s %d %d\n", avion.model, avion.nrLocuri, avion.nrLocuriOcupate);
	for (int i = 0; i < avion.nrLocuriOcupate; i++)
	{
		printf("%5.2f\n", avion.preturiBilete[i]);
	}
}

Avion citireAvionFisier(FILE* f) {
	Avion avionCitit;
	char buffer[20];

	fscanf(f, "%s", buffer);
	avionCitit.model = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy(avionCitit.model, buffer);
	fscanf(f, "%d", &avionCitit.nrLocuri);
	fscanf(f, "%d", &avionCitit.nrLocuriOcupate);
	avionCitit.preturiBilete = (float*)malloc(sizeof(float) * avionCitit.nrLocuriOcupate);
	for (int i = 0; i < avionCitit.nrLocuriOcupate; i++)
	{
		fscanf(f, "%f", &avionCitit.preturiBilete[i]);
	}

	return avionCitit;
}


typedef struct {
	Avion info;
	struct NodAB* dr;
	struct NodAB* st;
}NodAB;

NodAB* inserare(NodAB* root, Avion a) {
	if (root) {
		if (root->info.nrLocuri > a.nrLocuri) {
			root->st = inserare(root->st, a);
		}
		else {
			root->dr = inserare(root->dr, a);
		}
		return root;
	}
	else {
		NodAB* newRoot = (NodAB*)malloc(sizeof(NodAB));
		newRoot->info = a;
		newRoot->dr = NULL;
		newRoot->st = NULL;
		return newRoot;
	}
}

void afisarePreOrder(NodAB* root) { // Root --> Stanga --> Dreapta
	if (root) {
		printf("%d\n", root->info.nrLocuri);
		afisarePreOrder(root->st);
		afisarePreOrder(root->dr);

	}
}

void afisareInOrder(NodAB* root) { // Stanga --> Root --> Dreapta
	if (root) {
		afisareInOrder(root->st);
		printf("%d\n", root->info.nrLocuri);
		afisareInOrder(root->dr);

	}
}

void afisarePostOrder(NodAB* root) { // Stanga --> Dreapta --> ROOT
	if (root) {
		afisarePostOrder(root->st);
		afisarePostOrder(root->dr);
		printf("%d\n", root->info.nrLocuri);

	}
}

Avion cautare(NodAB* root, int nrLocuri) {
	if (root) {
		if (root->info.nrLocuri == nrLocuri) {
			Avion a = initAvion(root->info.model, root->info.nrLocuri,
				root->info.nrLocuriOcupate, root->info.preturiBilete);
			return a;
		}
		else if (root->info.nrLocuri > nrLocuri) {
			return cautare(root->st, nrLocuri);
		}
		else {
			return cautare(root->dr, nrLocuri);
		}
	}
	return initAvion("", -1, -1, NULL); // empty plain NOT FOUND CASE
}


void stergereArbore(NodAB* root) {
	if (root) {
		NodAB* stanga = root->st;
		NodAB* dreapta = root->dr;
		free(root->info.model);
		free(root->info.preturiBilete);
		free(root);
		stergereArbore(stanga);
		stergereArbore(dreapta);
		
	}

}
// ARBORE AVL
int inaltimeArbore(NodAB* root) {
	if (root) {
		int inaltimeS = inaltimeArbore(root->st);
		int inaltimeD = inaltimeArbore(root->dr);
		return 1 + max(inaltimeS, inaltimeD);
	}
	else {
		return 0;
	}
	
}
NodAB* rotateRight(NodAB* root) {
	if (root) {
		NodAB* futureRoot = root->st;
		root->st = futureRoot->dr;
		futureRoot->dr = root;
		return futureRoot;
	}
	return root;
}

NodAB* rotateLeft(NodAB* root) {
	if (root) {
		NodAB* futureRoot = root->dr;
		root->dr = futureRoot->st;
		futureRoot->st = root;
		return futureRoot;
	}
	return root;
}

int calculareGradEchilibru(NodAB* root) {
	if (root) {
		int inaltimeS = inaltimeArbore(root->st);
		int inaltimeD = inaltimeArbore(root->dr);
		int gradEchilb = inaltimeS - inaltimeD;

		return gradEchilb;
	}
	return 0;
}

NodAB* inserareAVL(NodAB* root, Avion a) {
	if (root) {
		if (root->info.nrLocuri > a.nrLocuri) {
			root->st = inserare(root->st, a);
		}
		else {
			root->dr = inserare(root->dr, a);
		}
		// check balance level
		int gradEchilb = calculareGradEchilibru(root);
		if (gradEchilb == 2) { // left size inbalance
			// rotate right
			if (calculareGradEchilibru(root->st) == 1) {
				root = rotateRight(root);
			}
			//double rotation right
			else {

			}
		}
		if (gradEchilb == -2) {//right size inbalance
			//rotate left
			if (calculareGradEchilibru(root->dr) == -1) {
				root = rotateLeft(root);
			}
			// double rotation left
			else {

			}
		}

		return root;
	}
	else {
		NodAB* newRoot = (NodAB*)malloc(sizeof(NodAB));
		newRoot->info = a;
		newRoot->dr = NULL;
		newRoot->st = NULL;
		return newRoot;
	}
}
void main() {
	float* preturiBilete = (float*)malloc(sizeof(float) * 4);
	preturiBilete[0] = 10;
	preturiBilete[1] = 20;
	preturiBilete[2] = 30;
	preturiBilete[3] = 30;
	Avion a1 = initAvion("Airbus A330", 300, 4, preturiBilete);

	//FILE* f = fopen("avioane.txt", "r");
	//int nrAvioane = 0;
	//if (f) {
	//	fscanf(f, "%d", &nrAvioane);
	//	for (int i = 0; i < nrAvioane; i++)
	//	{
	//		Avion a = citireAvionFisier(f);
	//		afisareAvion(a);
	//	}
	//}
	//fclose(f);
	NodAB* root = NULL; // radacina arborelui binar de cautare

	FILE* f = fopen("avioane.txt", "r");
	int nrAvioane = 0;
	if (f) {
		fscanf(f, "%d", &nrAvioane);
		for (int i = 0; i < nrAvioane; i++)
		{
			Avion a = citireAvionFisier(f);
			root = inserare(root,a);
		}
	}
	fclose(f);
	afisarePreOrder(root);
	//afisareInOrder(root);
	//stergereArbore(root);

	//root = NULL; // free doesnt make root pointer NULL

	//afisarePostOrder(root);
	printf("%d\n",inaltimeArbore(root));
	printf("%s", "Program finished successfully");
}