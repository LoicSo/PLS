#include "structure.h"

/*------------------STRUCTURE ARBRE------------------*/

int poids(arbre a) {
    return a.poids;
}

int caractere(arbre a) {
    return a.caractere;
}


/*------------------STRUCTURE TABLE------------------*/

int acces_correspondance(table t, int i) {
    return t.correspondance[i];
}

void modifier_correspondance(table *t, int i, int val) {
    t->correspondance[i] = val;
}

int acces_longueur(table t, int i) {
    return t.longueur[i];
}

void modifier_longueur(table *t, int i, int val) {
    t->longueur[i] = val;
}


/*------------------STRUCTURE LECTURE------------------*/

int taille(lecture l) {
    return l.taille;
}

int char_dif(lecture l) {
    return l.char_dif;
}

int acces_occurrence(lecture l, int i) {
    return l.occurrence[i];
}

void modifier_occurrence(lecture *l, int i, int val) {
    l->occurrence[i] = val;
}

}