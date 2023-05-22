#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>


typedef struct {

	int cod;
	char* denumire;
	float pret;
} produs;

typedef struct {

	produs inf;
	struct nodLs* next;

}nodLs;


typedef struct {
	struct nodLs** vector;
	int size;
} hashT;

int functieHash(int cheie, hashT tabela) {

	return cheie % tabela.size;
}

int inserare(hashT tabela, produs p) {
	int pozitie;

	if (tabela.vector != NULL) {
		pozitie = functieHash(p.pret, tabela);
		nodLs* nou = (nodLs*)malloc(sizeof(nodLs));
		nou->inf.cod = p.cod;
		nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
		strcpy(nou->inf.denumire, p.denumire);
		nou->inf.pret = p.pret;
		nou->next = NULL;

		if (tabela.vector[pozitie] == NULL) {
			tabela.vector[pozitie] = nou;
		}
		else {
			nodLs* temp = tabela.vector[pozitie];

			while (temp->next)
				temp = temp->next;
			temp->next = nou;
		}

		return pozitie;
	}
	return -1;
}

void traversareLs(nodLs* cap) {
	nodLs* temp = cap;
	while (temp) {
		printf("Codul=%d, Denumire=%s, Pret=%5.2f", temp->inf.cod, temp->inf.denumire, temp->inf.pret);
		printf("\n");
		temp = temp->next;
	}
}

void traversare(hashT tabela) {

	if (tabela.vector != NULL) {
		for (int i = 0; i < tabela.size; i++) {
			if (tabela.vector[i] != NULL) {
				printf("\nPozitie=%d\n", i);
				traversareLs(tabela.vector[i]);
			}
		}
	}
}

void dezalocareNodLs(nodLs* cap) {
	if (cap != NULL) {
		nodLs* temp = cap;
		while (temp) {
			nodLs* temp1 = temp->next;
			free(temp->inf.denumire);
			free(temp);
			temp = temp1;
		}
	}
}

void dezalocare(hashT tabela) {
	if (tabela.vector != NULL) {
		for (int i = 0; i < tabela.size; i++) {

			dezalocareNodLs(tabela.vector[i]);
		}
		free(tabela.vector);
	}
}

int main() {
	hashT tabela;
	tabela.size = 101;
	tabela.vector = (nodLs**)malloc(sizeof(nodLs*) * tabela.size);

	for (int i = 0; i < tabela.size; i++) {
		tabela.vector[i] = NULL;
	}

	int n;
	char buffer[30];
	produs p;
	FILE* f = fopen("text1.txt", "r");
	fscanf(f, "%d", &n);

	for (int i = 0; i < n; i++) {
		fscanf(f, "%d", &p.cod);
		fscanf(f, "%s", buffer);
		fscanf(f, "%f", &p.pret);

		p.denumire = (char*)malloc(((strlen(buffer) + 1) * sizeof(char)));
		strcpy(p.denumire, buffer);

		inserare(tabela, p);
		free(p.denumire);
	}

	traversare(tabela);
	dezalocare(tabela);
}