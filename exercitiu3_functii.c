#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct caine
{
	int id;
	char* nume;
	int varsta;
	char* rasa;
	float greutate;
};

struct caine initializare(int id, char* nume, int varsta, char* rasa, float greutate)
{
	struct caine s;
	s.id = id;
	s.nume = (char*)malloc(strlen(nume) + 1);
		strcpy_s(s.nume, strlen(nume) + 1, nume);
		s.varsta = varsta;
		s.rasa = (char*)malloc(strlen(rasa) + 1);
			strcpy_s(s.rasa, strlen(rasa) + 1, nume);
		s.greutate = greutate;
		return s;
}

void afisare(struct caine s)
{
	printf("ID:%d\n", s.id);
	printf("nume:%s\n", s.nume);
	printf("varsta:%d\n", s.varsta);
	printf("rasa:%s\n", s.rasa);
	printf("greutate:%.2f\n", s.greutate);

}

void modifica_Atribut(struct caine* s)
{
	s->greutate = s->greutate - 2.5;

}

void dezalocare(struct caine* s)
{
	free(s->nume);
	free(s->rasa);
}

int main()
{
	struct caine s;
	s = initializare(1, "Daisy", 2, "Golden", 32.7);
	afisare(s);
	printf("\nDupa cura:\n");
	afisare(s);
	modifica_Atribut(&s);
	dezalocare(&s);
	return 0;

}