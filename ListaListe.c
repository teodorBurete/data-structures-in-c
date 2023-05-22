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
	struct nodLS* next;

}nodLS;

typedef struct {

	//struct nodLS* cap;
	nodLS* capLS;
	struct nodLP* next;
}nodLP;

void inserareNodLS(nodLS** capLS, produs p) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->next = NULL;

	nou->inf.cod = p.cod;
	nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, p.denumire);

	nou->inf.pret = p.pret;

	if (*capLS == NULL) {
		*capLS = nou;
	}
	else {

		nodLS* temp = *capLS;
		while (temp->next)
			temp = temp->next;

		temp->next = nou;

	}
}

void inserareNodLP(nodLP** capLP, nodLS* capLS) {

	nodLP* nou = (nodLP*)malloc(sizeof(nodLP));
	nou->capLS = capLS;
	nou->next = NULL;

	if (*capLP == NULL) {
		*capLP = nou;
	}
	else {

		nodLP* temp = *capLP;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void traversareLS(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("Codul=%d, Denumire=%s, Pret=%5.2f", temp->inf.cod, temp->inf.denumire, temp->inf.pret);
		printf("\n");
		temp = temp->next;
	}
}

void traversareLP(nodLP* cap) {
	nodLP* temp = cap;
	while (temp) {
		printf("\nSublsita: ");
		traversareLS(temp->capLS);
		temp = temp->next;
	}
}

void dezalocareLS(nodLS* cap) {
	nodLS* temp = cap;

	while (temp) {
		nodLS* temp1 = temp->next;
		free(temp->inf.denumire);
		free(temp);
		temp = temp1;

	}
}

void dezalocareLP(nodLP* cap) {

	nodLP* temp = cap;

	while (temp) {
		nodLP* temp1 = temp->next;
		dezalocareLS(temp->capLS);
		free(temp);
		temp = temp1;
	}
}


int main() {

	int n;
	nodLP* capLP = NULL;
	produs p;
	FILE* f = fopen("text1.txt", "r");
	char buffer[20];

	nodLS* scumpe = NULL, * ieftine = NULL;

	fscanf(f, "%d", &n);

	for (int i = 0; i < n; i++) {
		fscanf(f, "%d", &p.cod);
		fscanf(f, "%s", buffer);
		fscanf(f, "%f", &p.pret);

		p.denumire = (char*)malloc(((strlen(buffer) + 1) * sizeof(char)));
		strcpy(p.denumire, buffer);


		if (p.pret > 100)
			inserareNodLS(&scumpe, p);
		else
			inserareNodLS(&ieftine, p);

		free(p.denumire);
	}

	inserareNodLP(&capLP, scumpe);
	inserareNodLP(&capLP, ieftine);

	traversareLP(capLP);
	dezalocareLP(capLP);

}
