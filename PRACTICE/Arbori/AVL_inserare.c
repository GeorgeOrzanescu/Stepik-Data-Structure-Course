#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>


typedef struct {
	unsigned int cod;
	char* model;
	float putere;
}Tren;

typedef struct {
	Tren tren;
	struct NodAVL* st;
	struct NodAVL* dr;
}NodAVL;


NodAVL* creareNod(Tren t) {
	NodAVL* nodNou = (NodAVL*)malloc(sizeof(NodAVL));
	nodNou->tren.cod = t.cod;
	nodNou->tren.model = (char*)malloc(sizeof(char) * (strlen(t.model) + 1));
	strcpy(nodNou->tren.model, t.model);
	nodNou->tren.putere = t.putere;

	nodNou->dr = NULL;
	nodNou->st = NULL;

	return nodNou;
}

int inaltimeArbore(NodAVL* root) {
	if (root) {
		int inaltimeS = inaltimeArbore(root->st);
		int inaltimeD = inaltimeArbore(root->dr);
		return 1 + max(inaltimeS, inaltimeD);
	}
	else {
		return 0;
	}
}


int gradEchilibru(NodAVL* root) {
	if (root) {
		int inaltimeS = inaltimeArbore(root->st);
		int inaltimeD = inaltimeArbore(root->dr);
		return inaltimeS - inaltimeD;
	}
	else {
		return 0;
	}
}

NodAVL* rotatieDreapta(NodAVL* root) {
	if (root) {
		NodAVL* noulRoot = root->st;
		noulRoot->dr = root;
		root->st = noulRoot->dr;
		return noulRoot;
	}
}
NodAVL* rotatieStanga(NodAVL* root) {
	if (root) {
		NodAVL* noulRoot = root->dr;
		noulRoot->st = root;
		root->dr = noulRoot->st;
		return noulRoot;
	}
}

NodAVL* inserare(NodAVL* root, Tren t) {
	NodAVL* nodNou = creareNod(t);
	if (root) {
		if (root->tren.putere > t.putere) {
			root->st = inserare(root->st, t);
		}
		else {
			root->dr = inserare(root->dr, t);
		}
		// echilibrare
		int gradEchil = gradEchilibru(root);
		if (gradEchil == 2) // debalansat la stanga
		{
			if (gradEchilibru(root->st) == 1) {
				root = rotatieDreapta(root);
			}
			else {
				root->st = rotatieStanga(root->st);
				root = rotatieDreapta(root);
				//rotatie stanga
				//rotatie dreapta
			}
		}
		if (gradEchil == -2) // debalansat la dreapta
		{
			if (gradEchilibru(root->dr) == -1) {
				//rotatie stanga
				root = rotatieStanga(root);
			}
			else {
				root->dr = rotatieDreapta(root->dr);
				root = rotatieStanga(root);
				//rotatie dreapta
				//rotatie stanga
			}
		}
		return root;
	}
	else {
		return nodNou;
	}
}


void afisareINORDER(NodAVL* root) {
	if (root) {
		afisareINORDER(root->st);
		printf("%d -- %s -- %5.2f\n", root->tren.cod, root->tren.model, root->tren.putere);
		afisareINORDER(root->dr);

	}
}

void main() {
	NodAVL* root = NULL;

	Tren t1 = { 1,"Bulterger",1600 };
	Tren t2 = { 2,"Martewg",1200 };
	Tren t3 = { 3,"Varana",3000 };
	Tren t4 = { 4,"Oltenia",1400 };
	Tren t5= { 5,"Oltenia2",2500 };


	root = inserare(root, t1);
	root = inserare(root, t2);
	root = inserare(root, t3);
	root = inserare(root, t4);
	root = inserare(root, t5);


	afisareINORDER(root);
	printf("End of main!");
}