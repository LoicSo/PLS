#include "lecture_ecriture.h"

float frequence[ASCII];

//initialise le tableau de fréquence à 0
void initialiser();

//calcul des fréquences de la structure lecture
//met à jour le tableau de fréquence
void calcul_frequence(lecture fichier);