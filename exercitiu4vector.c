#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct haine
{
	int id;
	char* codBare;
	char* numeProdus;
	float pret;
};

struct haine initializare(int id, const char* codBare, const char* numeProdus, float pret)
{
	struct haine h;
	h.id = id;
	h.codBare = NULL;
	h.numeProdus = NULL;
	h.pret = pret;

	h.codBare = (char*)malloc(strlen(codBare) + 1);
	if (h.codBare != NULL)
	{
		strcpy_s(h.codBare, strlen(codBare) + 1, codBare);
	}

	h.numeProdus = (char*)malloc(strlen(numeProdus) + 1);
	if (h.numeProdus != NULL)
	{
		strcpy_s(h.numeProdus, strlen(numeProdus) + 1, numeProdus);
	}

	return h;
}

void afisare(struct haine h)
{
	printf("ID: %d\n", h.id);
	printf("Cod bare: %s\n", h.codBare);
	printf("Nume produs: %s\n", h.numeProdus);
	printf("Pret: %.2f\n", h.pret);
}

void afisareVector(struct haine* vector, int nrElemente)
{
	int i;
	for (i = 0; i < nrElemente; i++)
	{
		printf("\nElementul %d:\n", i);
		afisare(vector[i]);
	}
}

struct haine* copiazaPrimeleNElemente(struct haine* vector, int nrElemente, int nrElementeCopiate)
{
	int i;
	struct haine* vectorNou;

	if (nrElementeCopiate > nrElemente)
	{
		nrElementeCopiate = nrElemente;
	}

	vectorNou = (struct haine*)malloc(sizeof(struct haine) * nrElementeCopiate);
	if (vectorNou == NULL)
	{
		return NULL;
	}

	for (i = 0; i < nrElementeCopiate; i++)
	{
		vectorNou[i] = initializare(
			vector[i].id,
			vector[i].codBare,
			vector[i].numeProdus,
			vector[i].pret
		);
	}

	return vectorNou;
}

void copiazaAnumiteElemente(struct haine* vector, int nrElemente, float prag, struct haine** vectorNou, int* dimensiune)
{
	int i;
	int k = 0;

	*dimensiune = 0;

	for (i = 0; i < nrElemente; i++)
	{
		if (vector[i].pret > prag)
		{
			(*dimensiune)++;
		}
	}

	if (*dimensiune == 0)
	{
		*vectorNou = NULL;
		return;
	}

	*vectorNou = (struct haine*)malloc(sizeof(struct haine) * (*dimensiune));
	if (*vectorNou == NULL)
	{
		*dimensiune = 0;
		return;
	}

	for (i = 0; i < nrElemente; i++)
	{
		if (vector[i].pret > prag)
		{
			(*vectorNou)[k] = initializare(
				vector[i].id,
				vector[i].codBare,
				vector[i].numeProdus,
				vector[i].pret
			);
			k++;
		}
	}
}

struct haine getPrimulElementConditionat(struct haine* vector, int nrElemente, const char* conditie)
{
	int i;

	for (i = 0; i < nrElemente; i++)
	{
		if (strcmp(vector[i].numeProdus, conditie) == 0)
		{
			return initializare(
				vector[i].id,
				vector[i].codBare,
				vector[i].numeProdus,
				vector[i].pret
			);
		}
	}

	return initializare(-1, "", "", 0);
}

void dezalocare(struct haine** vector, int* nrElemente)
{
	int i;

	if (*vector != NULL)
	{
		for (i = 0; i < *nrElemente; i++)
		{
			free((*vector)[i].codBare);
			free((*vector)[i].numeProdus);
		}

		free(*vector);
	}

	*vector = NULL;
	*nrElemente = 0;
}

int main()
{
	int nrElemente = 3;
	int nrPrimele2;
	int dimensiuneNoua = 0;

	struct haine* vector = (struct haine*)malloc(sizeof(struct haine) * nrElemente);
	struct haine* primele2;
	struct haine* vectorFiltrat = NULL;
	struct haine hGasita;

	if (vector == NULL)
	{
		printf("Eroare la alocarea memoriei.\n");
		return 1;
	}

	vector[0] = initializare(1, "111", "Tricou", 80.0f);
	vector[1] = initializare(2, "222", "Geaca", 250.0f);
	vector[2] = initializare(3, "333", "Blugi", 180.0f);

	printf("Vectorul initial:\n");
	afisareVector(vector, nrElemente);

	primele2 = copiazaPrimeleNElemente(vector, nrElemente, 2);
	nrPrimele2 = (nrElemente < 2) ? nrElemente : 2;

	printf("\n\nPrimele 2 elemente copiate:\n");
	if (primele2 != NULL)
	{
		afisareVector(primele2, nrPrimele2);
	}

	copiazaAnumiteElemente(vector, nrElemente, 100.0f, &vectorFiltrat, &dimensiuneNoua);

	printf("\n\nElementele cu pret > 100:\n");
	if (vectorFiltrat != NULL)
	{
		afisareVector(vectorFiltrat, dimensiuneNoua);
	}
	else
	{
		printf("Nu exista elemente care respecta conditia.\n");
	}

	hGasita = getPrimulElementConditionat(vector, nrElemente, "Geaca");

	printf("\n\nPrimul element gasit dupa numeProdus:\n");
	afisare(hGasita);

	dezalocare(&vector, &nrElemente);
	dezalocare(&primele2, &nrPrimele2);
	dezalocare(&vectorFiltrat, &dimensiuneNoua);

	free(hGasita.codBare);
	free(hGasita.numeProdus);

	return 0;
}