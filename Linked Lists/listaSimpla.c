#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<malloc.h>

typedef struct {
	int nrMatricol;
	char* nume;
	float medie;
}student;

// SIMPLE LINKED LIST
typedef struct {
	student inf;  // informatia utila
	struct nodeLs* next; //pointer legatura lista
} nodeLs;


nodeLs* inserare(nodeLs* cap,student s) {
	// alocam spatiu pt nodul pe care il construim
	nodeLs* nou = (nodeLs*)malloc(sizeof(nodeLs));
	// initializam nodul cu informatia utila  (copiem fiecare atribut pentru a a anu avea shallow copy)
	nou->inf.nrMatricol = s.nrMatricol;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1)* sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;

	nou->next = NULL; // initializam NULL pt inceput
	if (cap == NULL) { // daca nu exista nodul cap , nodul de introdus devine cap
		cap = nou;
	}
	else {
		nodeLs* temp = cap;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
	}

	return cap;
}

// traversarea listei de noduri
void traversare(nodeLs* cap) {
	nodeLs* temp = cap;
	while (temp != NULL) {
		printf("Student nr: %d, media %5.2f , numele: %s", temp->inf.nrMatricol, temp->inf.medie, temp->inf.nume);
		printf("\n");
		temp = temp->next;
	}
}
// dezalocare lista
void dezalocare(nodeLs* cap) {
	nodeLs* temp = cap;
	while (temp != NULL) {
		nodeLs* next = temp->next;  // avem nevoie de next dupa ce stergem temp
		free(temp->inf.nume);
		free(temp);
		temp = next;  // aici punem next in temp
	}
}

void main() {

	int n;
	//printf("Nr studenti: ");
	//scanf("%d", &n); // citim imputul 

	nodeLs* cap = NULL;
	student s;
	char buffer[20]; // sa putem citi numele 20 e la alegere

	// CITIRE DE LA TASTATURA
	//for (int i = 0; i < n; i++)
	//{
	//	printf("Nr matricol : ");
	//	scanf("%d", &s.nrMatricol);
	//	printf("Nume : ");

	//	scanf("%s", buffer);  // char buffer[20]  e ca o adresa de aia nu folosim &
	//	s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));

	//	strcpy(s.nume, buffer);
	//	printf("Medie : ");
	//	scanf("%f", &s.medie);

	//	cap = inserare(cap, s);   // fiindca ne returneaza capul mereu sa updatam capul mereu
	//	free(s.nume);  // eliberam memoria alocata pt urmatorul input
	//}
	//
	//traversare(cap);
	//dezalocare(cap);

	// CITIRE DIN FISIER TXT
	FILE* f = fopen("fisier.txt","r");
	fscanf(f, "%d", &n); // citim numarul de studenti prima oara

	for (int i = 0; i < n; i++)
	{
		fscanf(f,"%d", &s.nrMatricol);

		fscanf(f,"%s", buffer);  // char buffer[20]  e ca o adresa de aia nu folosim &
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);

		fscanf(f,"%f", &s.medie);

		cap = inserare(cap, s);   // fiindca ne returneaza capul mereu sa updatam capul mereu
		free(s.nume);  // eliberam memoria alocata pt urmatorul input

		
	}
	fclose(f);  // inchizi fisierul 
	traversare(cap);
	dezalocare(cap);
}