#include "calcul.h"


//initialise le tableau de fréquence à 0
void initialiser() {
    for (int i=0; i<ASCII; i++) {
        frequence[i] = 0;
    }
}

//calcul des fréquences de la structure lecture
//met à jour le tableau de fréquence
void calcul_frequence(lecture l) {
   initialiser();
   for (int i=0; i<ASCII; i++) {
       frequence[i] = (float)acces_occurrence(l,i) / taille(l);
   }
}
