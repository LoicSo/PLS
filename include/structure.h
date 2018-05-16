#ifndef LECTURE_H
#include "lecture_ecriture.h"
#define LECTURE_H
#endif
#ifndef ARBRE_H
#include "arbres.h"
#define ARBRE_H
#endif

#ifndef STRUCTURE_H
#define STRUCTURE_H


/*------------------STRUCTURE ARBRE------------------*/

int poids(arbre a);
int caractere(arbre a);

/*------------------STRUCTURE TABLE------------------*/

int acces_correspondance(table t, int i);
void modifier_correspondance(table *t, int i, int val);
int acces_longueur(table t, int i);
void modifier_longueur(table *t, int i, int val);


/*------------------STRUCTURE LECTURE------------------*/

int taille(lecture l);
int char_dif(lecture l);
int acces_occurrence(lecture l, int i);
void modifier_occurrence(lecture *l, int i, int val);

#endif
