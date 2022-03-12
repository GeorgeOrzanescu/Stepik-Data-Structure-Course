#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<malloc.h>

typedef struct {
	int nrMatricol;
	char* nume;
	float medie;
}student;

// DOUBLE LINKED LIST
typedef struct {
	student inf;  // informatia utila
	struct nodeLs* next; //pointer legatura lista urmatorul node
	struct nodeLs* prev; //pointer legatura lista anterior node
} nodeLs;

// !!! ** coada dorim sa returnam coada din parametru si o sa il adaugam ca referinta la apel
// &coada   --> adresa cozi
nodeLs* inserare(nodeLs* cap,nodeLs** coada, student s) {
	// alocam spatiu pt nodul pe care il construim
	nodeLs* nou = (nodeLs*)malloc(sizeof(nodeLs));
	// initializam nodul cu informatia utila  (copiem fiecare atribut pentru a a anu avea shallow copy)
	nou->inf.nrMatricol = s.nrMatricol;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;

	nou->next = NULL; // initializam NULL pt inceput
	nou->prev = NULL; 

	if (cap == NULL) { // daca nu exista nodul cap , nodul de introdus devine atat cap cat si coada
		cap = nou;
		coada = nou;
	}
	else {
		nodeLs* temp = cap;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou; //ultimul se leaga cu noul node
		nou->prev = temp; // noul node va avea anterior fostul ultim element

		*coada = nou;  // actualizam coada cu adresa noului node
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
// traversare inversa
void traversareInvers(nodeLs* coada) {
	nodeLs* temp = coada;
	while (temp != NULL) {
		printf("Student nr: %d, media %5.2f , numele: %s", temp->inf.nrMatricol, temp->inf.medie, temp->inf.nume);
		printf("\n");
		temp = temp->prev;
	}
}

// dezalocare lista de la cap la coada poti face si inver ca mai sus
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

	nodeLs* cap = NULL;
	nodeLs* coada = NULL;
	student s;
	char buffer[20]; // sa putem citi numele 20 e la alegere

	// CITIRE DIN FISIER TXT
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n); // citim numarul de studenti prima oara

	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &s.nrMatricol);

		fscanf(f, "%s", buffer);  // char buffer[20]  e ca o adresa de aia nu folosim &
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);

		fscanf(f, "%f", &s.medie);

		// adaugam ca referinta parametrul coada sa poate fi modificat in interiorul functiei inserare
		cap = inserare(cap,&coada, s);   // fiindca ne returneaza capul mereu sa updatam capul mereu
		free(s.nume);  // eliberam memoria alocata pt urmatorul input
	}
	fclose(f);  // inchizi fisierul
	traversare(cap);
	traversareInvers(coada);
	dezalocare(cap);
}