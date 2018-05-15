#include "lecture_ecriture.h"

typedef struct a {
	struct a *f_gauche;
	struct a *f_droite;
	int poids;
	int caractere;
}arbre, *p_arbre;

typedef struct{
	int  correspondance[ASCII];
	int longueur[ASCII];
}table, *p_table;

