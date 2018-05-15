#include "arbres.h"

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

