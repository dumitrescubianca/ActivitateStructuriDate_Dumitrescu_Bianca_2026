#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pacient
{
	int id;
	int varsta_pacient;
	char* nume;
	float cost_tratament;
};
struct pacient initializare ( int id, int varsta_pacient, char* nume, float cost_tratament )
{
	struct pacient s;
	s.id = id;
	s.nume = (char*)malloc(strlen(nume) + 1);
	strcpy_s(s.nume, strlen(nume) + 1, nume);
	s.varsta_pacient = varsta_pacient;
	s.cost_tratament = cost_tratament;

	return s;
}
void afisare(struct pacient s)
{
	printf("ID:%d\n", s.id);
	printf("varsta_pacient: %d\n", s.varsta_pacient);
	printf("nume: %s\n", s.nume);
	printf("cost_tratament: %f\n", s.cost_tratament);	
}

void modifica_Atribut(struct pacient* s)
{
	s->cost_tratament=s->cost_tratament + 500;

}
void dezalocare(struct pacient* s)
{
	free(s->nume);
}

int main()
{
	struct pacient p;
	p = initializare(1, 75, "Ionel", 3600);
	afisare(p);
	modifica_Atribut(&p);
	printf("\nDupa scumpire:\n");
	afisare(p);
	dezalocare(&p);

	return 0;
}