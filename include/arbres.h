#ifndef LECTURE_H
#include "lecture_ecriture.h"
#define LECTURE_H
#endif

#ifndef ARBRE_H
#define ARBRE_H

typedef struct a {
	struct a *f_gauche;
	struct a *f_droite;
	int profondeur;
	float poids;
	int caractere;
}arbre, *p_arbre;

typedef struct{
	int  correspondance[ASCII];
	int longueur[ASCII];
}table, *p_table;

typedef struct f{
  int queue, tete;
  p_arbre T[ASCII];
} file, *p_file;

#endif
