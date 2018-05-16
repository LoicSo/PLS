#ifndef LECTURE_H
#include "lecture_ecriture.h"
#define LECTURE_H
#endif

#ifndef STRUCTURE_H
#include "structure.h"
#define STRUCTURE_H
#endif

#ifndef CALCUL_H
#define CALCUL_H


float frequence[ASCII];

//initialise le tableau de fréquence à 0
void initialiser();

//calcul des fréquences de la structure lecture
//met à jour le tableau de fréquence
void calcul_frequence(lecture l);
#endif
