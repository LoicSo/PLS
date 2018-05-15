#include <stdlib.h>

#include "arbres.h"
#include "calcul.h"
#include "structure.h"

p_arbre* init_tab(frequence f, int nb_car){
	int i = 0;
	p_arbre noeud;

	p_arbre *tab_noeud = malloc(nb_car * sizeof(p_arbre));

	for (int j = 0; j < nb_car; ++j)
	{
		noeud = malloc(sizeof(arbre));

		while(i < ASCII && f[i] == 0.0)
			i++;

		if (i < ASCII)
		{
			noeud->f_gauche = NULL;
			noeud->f_droite = NULL;
			noeud->profondeur = 0;
			noeud->poids = f[i];
			noeud->caractere = i;

			tab_noeud[j] = noeud;
			i++;
		}
	}
	return tab_noeud;
}

p_arbre mini(p_arbre tab_noeud[], int nb_car){
	float min = 1.0;
	p_arbre res;
	for (int i = 0; i < nb_car; ++i)
	{
		if(tab_noeud[i] != NULL)
		{
			if (tab_noeud[i]->poids < min)
			{
				min = tab_noeud[i]->poids;
				res = tab_noeud[i];
			}
		}
	}
	return res;
}

void supprimer(p_arbre **tab_noeud, p_arbre noeud, int nb_car){
	for (int i = 0; i < nb_car; ++i)
	{
		if ((*tab_noeud)[i] == noeud){
			(*tab_noeud)[i] = NULL;
			return;
		}
	}
}

int est_feuille(p_arbre noeud){
	return(noeud->f_droite == NULL && noeud->f_gauche == NULL);
}

void incrementer_prof(p_arbre noeud){
	if(noeud != NULL){
		noeud->profondeur++;
		incrementer_prof(noeud->f_gauche);
		incrementer_prof(noeud->f_droite);
	}
}

p_arbre creer_parent(p_arbre gauche, p_arbre droite){
	p_arbre parent = malloc(sizeof(arbre));

	if(est_feuille(gauche)){
		parent->f_droite = gauche;
		parent->f_gauche = droite;
	}
	else{
		parent->f_droite = droite;
		parent->f_gauche = gauche;
	}
	parent->profondeur = 0;
	parent->poids = gauche->poids + droite->poids;
	parent->caractere = 0;
	incrementer_prof(gauche);
	incrementer_prof(droite);
	return parent;
}

void ajouter(p_arbre **tab_noeud, int nb_car, p_arbre noeud){
	int i = 0;
	while(i < nb_car && (*tab_noeud)[i] != NULL)
		i++;
	if(i < nb_car)
		(*tab_noeud)[i] = noeud;
}

p_arbre creation_arbre(frequence f, p_lecture l){
	int nb_car = char_dif(*l);	
	p_arbre *tab_noeud;
	tab_noeud = init_tab(f, nb_car);
	int nb_noeud = nb_car;

	p_arbre gauche, droite, parent;

	while (nb_noeud > 1){
		gauche = mini(tab_noeud, nb_car);
		supprimer(&tab_noeud, gauche, nb_car);
		droite = mini(tab_noeud, nb_car);
		supprimer(&tab_noeud, droite, nb_car);
		parent = creer_parent(gauche, droite);
		ajouter(&tab_noeud, nb_car, parent);
		nb_noeud--;
	}
	return *tab_noeud;
}

void afficher_arbre (p_arbre a, int niveau)
{
  /*
    affichage de l'arbre a
    on l'affiche en le penchant sur sa gauche
    la partie droite (haute) se retrouve en l'air
  */

	int i ;

	if (a != NULL)
	{
		afficher_arbre (a->f_droite,niveau+1) ;

		for (i = 0; i < niveau; i++)
			printf ("\t") ;
		printf (" %f %d (%d)\n\n", a->poids, a->caractere, a->profondeur) ;

		afficher_arbre (a->f_gauche, niveau+1) ;
	}
	return ;
}

void trouver_feuille(table *t, p_arbre a, int valeur){
	if(a->f_gauche == NULL && a->f_gauche == NULL){
		modifier_correspondance(t, a->caractere, valeur);
		modifier_longueur(t, a->caractere, a->profondeur);
	}else{
		trouver_feuille(t, a->f_gauche, (valeur<<1)+1);
		trouver_feuille(t, a->f_droite, (valeur<<1));

	}

}

table faire_table(p_arbre a){
	table t;
	for (int i=0; i<ASCII; i++){
		modifier_longueur(&t, i,0);
		modifier_correspondance(&t,i,0);
	}
	trouver_feuille(&t,a,0);
	return t;
}

void affciher_table(table t){
	for(int i=0; i<ASCII; i++){
		if (acces_longueur(t, i)){
			printf("code ascii : %d, valeur :%d, longueur : %d\n", i, acces_correspondance(t,i), acces_longueur(t,i) );
		}
	}

}

int main(int argc, char const *argv[])
{
	frequence f;
	p_lecture l = malloc(sizeof(lecture));

	f[0] = 0.1;
	f[1] = 0.2;
	f[2] = 0.3;
	f[3] = 0.4;
	for (int i = 4; i < ASCII; ++i)
	{
		f[i] = 0.0;
	}
	l->char_dif = 4;

	p_arbre arbre;
	arbre = creation_arbre(f, l);
	afficher_arbre(arbre, 0);
	table t = faire_table(arbre);
	affciher_table(t);

	return 0;
}


