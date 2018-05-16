#include "calcul.h"


//initialise le tableau de fréquence à 0
void initialiser(double frequence[ASCII]) {
    for (int i=0; i<ASCII; i++) {
        frequence[i] = 0;
    }
}

//calcul des fréquences de la structure lecture
//met à jour le tableau de fréquence
void calcul_frequence(double frequence[ASCII], lecture l) {
   initialiser(frequence);
   int k = 0;
   for (int i=0; i<ASCII; i++) {
       frequence[i] = (double)acces_occurrence(l,i) / taille(l);
       if(acces_occurrence(l,i)){
        printf("frequence : %lf      %d\n", frequence[i], i);
        k++;
      }
   }

}
