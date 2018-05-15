#include "arbres.h"
#include "structure.h"
#include <stdlib.h>


void faire_donnee(p_table t, p_lecture l){
	int i=0;
	int j=0;
	ecriture = malloc(sizeof(char) * l->taille);
	char current =*(l->donnee+i);
	int entier;
	int longueur;
	int  corresp;
	int compteur_current =8;
	unsigned int car_fin=0;
	unsigned char car;

	int espacement;
	int masque;
	int caractere_tmp;
	int k;
	while( current != '\0'){
		entier = (int)current;

		longueur =  acces_longueur(t,entier);
		corresp = acces_correspondance(t,entier);
		if(compteur_current -longueur >0){
			car_fin += (corresp << (compteur_current -longueur));
			compteur_current = compteur_current -longueur;

		}
		else if(compteur_current -longueur == 0){
			car_fin +=corresp;
			car = (char)car_fin;
			*(ecriture+j) = car;
			j++;
			car_fin=0;
			compteur_current=8; 
		}
		else{
			k=0;

			do{
				espacement = longueur- compteur_current -k*8;	
				masque =(1<< espacement) -1;
				caractere_tmp = corresp & masque;
				car_fin += (corresp >> espacement);
				car = (char)car_fin;
				*(ecriture+j) = car;
				j++;
				car_fin=0;
				compteur_current=8;
				corresp =caractere_tmp;
				car_fin += (caractere_tmp << compteur_current-espacement);
				compteur_current =compteur_current -espacement;
				k++;

			}while(espacement > 8);
		}
		i++;
		current =*(l->donnee+i);
		
	}
	car = (char)car_fin;
	*(ecriture+j) = car;

}

int main_test_faire_donee(){
	table t;
	t.correspondance[65] = 5;
	t.correspondance[66] = 345;
	t.longueur[65]=3;
	t.longueur[66]=9;

	lecture l;
	l.donnee = "BABA";
	l.taille=4;

	faire_donnee(&t,&l);
	printf("chaine compressé :%s\n",ecriture );

}