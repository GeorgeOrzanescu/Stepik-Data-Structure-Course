#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct {
	char* numeAngajat;
	char* departament;
	char* dataEvaluare;
	unsigned int notaEvaluare;
}EvaluareAngajat;


typedef struct {
	EvaluareAngajat evaluare;
	struct NodArbore* st;
	struct NodArbore* dr;
}NodArbore;


//EvaluareAngajat creareEvaluare(const char* numeAngajat, const char* departament,
//	const char* dataEvaluare, unsigned int notaEvaluare) {
//	EvaluareAngajat ea;
//	ea.numeAngajat = (char*)malloc((strlen(numeAngajat) + 1) * sizeof(char));
//	strcpy(ea.numeAngajat, numeAngajat);
//	ea.departament = (char*)malloc((strlen(departament) + 1) * sizeof(char));
//	strcpy(ea.departament, departament);
//	ea.dataEvaluare = (char*)malloc((strlen(dataEvaluare) + 1) * sizeof(char));
//	strcpy(ea.dataEvaluare, dataEvaluare);
//	ea.notaEvaluare = notaEvaluare;
//
//	return ea;
//}

int inaltimeArbore(NodArbore* root) {
	if(root){
		int inaltimeS = inaltimeArbore(root->st);
		int inaltimeD = inaltimeArbore(root->dr);
		return 1 + max(inaltimeS, inaltimeD);
	}
	else {
		return 0;
	}
}

int calculGradEchilibru(NodArbore* root) {
	if (root) {
		int inaltimeS = inaltimeArbore(root->st);
		int inaltimeD = inaltimeArbore(root->dr);
		int gradEchilb = inaltimeS - inaltimeD;

		return gradEchilb;
	}
	else {
		return 0;
	}
}
NodArbore* rotatieDreapta(NodArbore* root) {
	if (root) {
		NodArbore* rootNou = root->st;
		root->st = rootNou->dr;
		rootNou->dr = root;
		return rootNou;
	}
}

NodArbore* rotatieStanga(NodArbore* root) {
	if (root) {
		NodArbore* rootNou = root->dr;
		root->dr= rootNou->st;
		rootNou->st = root;
		return rootNou;
	}
}


NodArbore* inserare(NodArbore* root, EvaluareAngajat ea) {
	if (root) {
		if (root->evaluare.notaEvaluare > ea.notaEvaluare) {
			root->st = inserare(root->st, ea);
		}
		else {
			root->dr = inserare(root->dr, ea);
		}
		// echilibrare
		// check balance of tree
		int gradEchil = calculGradEchilibru(root);
		if (gradEchil == 2) { // left size inbalance
			if (calculGradEchilibru(root->st) == 1) {
				printf("Rotire dreapta\n");
				root = rotatieDreapta(root);
			}
			else {
				printf("Dubla Rotire dreapta\n");
				root->st = rotatieStanga(root->st);
				root = rotatieDreapta(root);
			}
		}
		if (gradEchil == -2) { // right size inbalance
			if (calculGradEchilibru(root->dr) == -1) {
				printf("Rotire stanga\n");
				root = rotatieStanga(root);
			}
			else {
				printf("Dubla Rotire dreapta\n");
				root->dr = rotatieDreapta(root->dr);
				root = rotatieStanga(root);
			}
		}
		return root;
	}
	else {
		NodArbore* nodNou = (NodArbore*)malloc(sizeof(NodArbore));
		nodNou->evaluare = ea;
		nodNou->dr = NULL;
		nodNou->st = NULL;
		return nodNou;
	}
}


void afisareArboreINORDINE(NodArbore* root) { // INORDER Stanga --> ROOT --> Dreapta
	if (root) {
		afisareArboreINORDINE(root->st);
		printf("%s -- %s -- %s -- %d\n", root->evaluare.dataEvaluare, root->evaluare.departament,
			root->evaluare.numeAngajat, root->evaluare.notaEvaluare);
		afisareArboreINORDINE(root->dr);
	}
}

void afisareArborePREORDINE(NodArbore* root) { // PREORDER ROOT --> Stanga--> Dreapta
	if (root) {
		
		printf("%s -- %s -- %s -- %d\n", root->evaluare.dataEvaluare, root->evaluare.departament,
			root->evaluare.numeAngajat, root->evaluare.notaEvaluare);
		afisareArborePREORDINE(root->st);
		afisareArborePREORDINE(root->dr);
	}
}

typedef struct {
	EvaluareAngajat ea;
	struct NodeLS* next;
}NodeLS;
void determinareFrunzeLS(NodArbore* root, NodeLS** head) {
	if (root) {
		if (root->dr == NULL && root->st == NULL) {
			NodeLS* nodNou = (NodeLS*)malloc(sizeof(NodeLS));
			nodNou->ea = root->evaluare;
			nodNou->next = NULL;
			if (*head == NULL) {
				*head = nodNou;
			}
			else {
				NodeLS* temp = *head;
				while (temp->next) {
					temp = temp->next;
				}
				temp->next = nodNou;
			}
		}
		determinareFrunzeLS(root->st, head);
		determinareFrunzeLS(root->dr, head);
		
	}
}

void printLS(NodeLS* head) {
	while (head) {
		printf("%s -- %s -- %d\n", head->ea.departament, head->ea.numeAngajat, head->ea.notaEvaluare);
		head = head->next;
	}
}

void main() {

	NodArbore* root = NULL;

	FILE* f = fopen("evaluari.txt", "r");
	int n = 0;
	if (f) {
		fscanf(f, "%d", &n);
		char buffer[20];
		for (int i = 0; i < n; i++)
		{
			EvaluareAngajat ea;
			fscanf(f, "%s", buffer);
			ea.numeAngajat = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
			strcpy(ea.numeAngajat, buffer);
			fscanf(f, "%s", buffer);
			ea.departament = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
			strcpy(ea.departament, buffer);
			fscanf(f, "%s", buffer);
			ea.dataEvaluare = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
			strcpy(ea.dataEvaluare, buffer);
			fscanf(f, "%d", &ea.notaEvaluare);

			root = inserare(root, ea);
		}
	}
	fclose(f);
	afisareArboreINORDINE(root);
	NodeLS* head = NULL;
	determinareFrunzeLS(root, &head);
	printLS(head);

	printf("End of program!");
}