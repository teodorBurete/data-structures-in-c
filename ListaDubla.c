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
	struct nodLs* prev;

}nodLs;

produs citireProdus() {
	produs p;
	char buffer[20];

	printf("Cod: ");
	scanf("%d", &p.cod);

	printf("Denumire: ");
	scanf("%s", buffer);
	p.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(p.denumire, buffer);

	printf("Pret: ");
	scanf("%f", &p.pret);

	return p;
}

void inserareNod(nodLs** cap, nodLs** ultim, produs p) {
	nodLs* nou = (nodLs*)malloc(sizeof(nodLs));
	nou->next = NULL;
	nou->prev = NULL;

	nou->inf.cod = p.cod;
	nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, p.denumire);

	nou->inf.pret = p.pret;

	if (*cap == NULL) {
		*cap = nou;
		*ultim = nou;
	}
	else {
		nodLs* temp = *cap;

		while (temp->next)
			temp = temp->next;

		temp->next = nou;
		nou->prev = temp;
		*ultim = nou;
	}
}

void traversare(nodLs* cap) {
	nodLs* temp = cap;
	while (temp) {
		printf("Codul=%d, Denumire=%s, Pret=%5.2f", temp->inf.cod, temp->inf.denumire, temp->inf.pret);
		printf("\n");
		temp = temp->next;
	}

}

void stergereNod(nodLs** cap, nodLs** ultim, nodLs* sters) {

	if (*cap == sters) {

		*cap = sters->next;
		if (*cap != NULL)
			(*cap)->prev = NULL;

		free(sters->inf.denumire);
		free(sters);

		return;
	}

	if (*ultim == sters) {

		*ultim = sters->prev;
		(*ultim)->next = NULL;

		free(sters->inf.denumire);
		free(sters);

		return;
	}

	nodLs* urmator = sters->next;
	nodLs* anterior = sters->prev;

	urmator->prev = anterior;
	anterior->next = urmator;

	free(sters->inf.denumire);
	free(sters);

	return;

}

void stergereNodCod(nodLs** cap, nodLs** ultim, int cod) {

	nodLs* sters = NULL;

	nodLs* temp = *cap;
	while (temp) {
		if (temp->inf.cod == cod) {
			sters = temp;
			stergereNod(cap, ultim, sters);
			break;
		}
		else {
			temp = temp->next;
		}
	}
}





void traversareInversa(nodLs* ultim) {
	nodLs* temp = ultim;
	while (temp) {
		printf("Codul=%d, Denumire=%s, Pret=%5.2f", temp->inf.cod, temp->inf.denumire, temp->inf.pret);
		printf("\n");

		temp = temp->prev;
	}
}

void dezalocare(nodLs* cap) {

	nodLs* temp = cap;

	while (temp) {
		free(temp->inf.denumire);
		nodLs* temp1 = temp;
		temp = temp->next;
		free(temp1);
		
	}
}


int main() {

	int n = 2;
	nodLs* cap = NULL, * ultim = NULL;

	produs p;
	for (int i = 0; i < n; i++) {
		p = citireProdus();
		inserareNod(&cap, &ultim, p);
		free(p.denumire);
	}

	traversare(cap);
	printf("\n");
	traversareInversa(ultim);
	printf("\n");
	stergereNodCod(&cap, &ultim, 2);
	traversare(cap);

	dezalocare(cap);

}
