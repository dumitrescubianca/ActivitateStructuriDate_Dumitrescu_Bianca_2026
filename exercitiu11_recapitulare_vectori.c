#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct aspirator
{
	int id;
	float pret;
	float kw;
	char* denumire;
	char* codProdus;
};

struct aspirator initializare(int id, float pret, float kw, const char* denumire, const char* codProdus)
{
	struct aspirator a;
	a.id = id;
	a.pret = pret;
	a.kw = kw;

	a.denumire = (char*)malloc(strlen(denumire) + 1);
	if (a.denumire != NULL)
	{
		strcpy_s(a.denumire, strlen(denumire) + 1, denumire);
	}

	a.codProdus = (char*)malloc(strlen(codProdus) + 1);
	if (a.codProdus != NULL)
	{
		strcpy_s(a.codProdus, strlen(codProdus) + 1, codProdus);
	}

	return a;
}

void afisare(struct aspirator a)
{
	printf("ID: %d\n", a.id);
	printf("Pret: %.2f\n", a.pret);
	printf("KW: %.2f\n", a.kw);
	printf("Denumire: %s\n", a.denumire);
	printf("Cod produs: %s\n", a.codProdus);
}

void afisareVector(struct aspirator* vector, int nrElemente)
{
	int i;
	for (i = 0; i < nrElemente; i++)
	{
		printf("\nElementul %d:\n", i);
		afisare(vector[i]);
	}
}

struct aspirator* copiazaPrimeleNElemente(struct aspirator* vector, int nrElemente, int nrElementeCopiate)
{
	int i;
	struct aspirator* vectorNou;

	if (nrElementeCopiate > nrElemente)
	{
		nrElementeCopiate = nrElemente;
	}

	vectorNou = (struct aspirator*)malloc(sizeof(struct aspirator) * nrElementeCopiate);
	if (vectorNou == NULL)
	{
		return NULL;
	}

	for (i = 0; i < nrElementeCopiate; i++)
	{
		vectorNou[i] = initializare(
			vector[i].id,
			vector[i].pret,
			vector[i].kw,
			vector[i].denumire,
			vector[i].codProdus
		);
	}

	return vectorNou;
}

struct aspirator getPrimulElementConditionat(struct aspirator* vector, int nrElemente, const char* conditie)
{
	int i;

	for (i = 0; i < nrElemente; i++)
	{
		if (strcmp(vector[i].denumire, conditie) == 0)
		{
			return initializare(
				vector[i].id,
				vector[i].pret,
				vector[i].kw,
				vector[i].denumire,
				vector[i].codProdus
			);
		}
	}

	return initializare(-1, 0, 0, "", "");
}

void dezalocare(struct aspirator** vector, int* nrElemente)
{
	int i;

	if (*vector != NULL)
	{
		for (i = 0; i < *nrElemente; i++)
		{
			free((*vector)[i].denumire);
			free((*vector)[i].codProdus);
		}

		free(*vector);
	}

	*vector = NULL;
	*nrElemente = 0;
}

int main()
{
	int nrElemente = 3;
	int nrCopiate = 2;

	struct aspirator* vector = (struct aspirator*)malloc(sizeof(struct aspirator) * nrElemente);
	struct aspirator* vectorNou = NULL;
	struct aspirator aGasit;

	if (vector == NULL)
	{
		printf("Eroare la alocarea memoriei.\n");
		return 1;
	}

	vector[0] = initializare(1, 499.99f, 1.8f, "Philips", "ASP001");
	vector[1] = initializare(2, 699.50f, 2.1f, "Samsung", "ASP002");
	vector[2] = initializare(3, 899.00f, 2.5f, "Dyson", "ASP003");

	printf("Vector initial:\n");
	afisareVector(vector, nrElemente);

	vectorNou = copiazaPrimeleNElemente(vector, nrElemente, nrCopiate);

	printf("\nPrimele %d elemente copiate:\n", nrCopiate);
	if (vectorNou != NULL)
	{
		afisareVector(vectorNou, nrCopiate);
	}
	
	aGasit = getPrimulElementConditionat(vector, nrElemente, "Samsung");

	printf("\nPrimul element gasit dupa denumire:\n");
	afisare(aGasit);

	dezalocare(&vector, &nrElemente);
	dezalocare(&vectorNou, &nrCopiate);

	free(aGasit.denumire);
	free(aGasit.codProdus);

	return 0;
}