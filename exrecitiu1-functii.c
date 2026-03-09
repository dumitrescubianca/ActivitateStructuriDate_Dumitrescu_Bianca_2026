#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct meniu
{
	int id;
	int gramaj;
	float pret;
	char* denumire;
};
struct meniu initializare(int id,int gramaj, float pret, char* denumire)
{
	struct meniu s;
	s.id = id;
	s.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy_s(s.denumire, strlen(denumire) + 1, denumire);

	s.pret = pret;
	s.gramaj = gramaj;

	return s;
}
void afisare(struct meniu s) // afisare 
{
	printf("ID %d\n", s.id);
	printf("denumire %s\n", s.denumire);
	printf("gramaj %d\n", s.gramaj);
	printf("pret %.2f\n", s.pret);
}
void modifica_Atribut(struct meniu* s)
{
	s->pret = s->pret + 7;
}
void dezalocare(struct meniu* s)
{
	free(s->denumire);
}

/* int main()
{
	struct meniu m;
	m = initializare(1, 250, 20.5, "ciorba");
	afisare(m);
	modifica_Atribut(&m);
	printf("\nDupa modificare:\n");
	afisare(m);
	dezalocare(&m);
	return 0;
}*/