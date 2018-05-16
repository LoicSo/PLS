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

/**
 * @brief Permet d'initialisé la fréquence a 0
 *
 */
void initialiser();


/**
 * @brief Permet de calculer les fréquence a partir de la structure lecture
 *
 *
 * @param fichier structure lecture complete
 */
void calcul_frequence(lecture l);
#endif
