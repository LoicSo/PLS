#include <stdlib.h>
#include "arbres.h"
#include "calcul.h"
#include "structure.h"


// Initialisation du tableau de noeud avec toutes les feuilles
p_arbre* init_tab(double f[ASCII], int nb_car, lecture l){
	int i = 0;
	p_arbre noeud;
	p_arbre *tab_noeud = malloc(nb_car * sizeof(p_arbre));

	for (int j = 0; j < nb_car; ++j)
	{
		noeud = malloc(sizeof(arbre));

		// On cherche les caractères présents dans les données
		while(i < ASCII && acces_occurrence(l,i) == 0){
					i++;
		}
		// On crée une feuille pour chaque caractère
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

// On cherche le noeud avec la fréquence la plus basse
p_arbre mini(p_arbre tab_noeud[], int nb_car){
	double min = 1.0;
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

// On supprime le noeud dans le tableau
void supprimer(p_arbre **tab_noeud, p_arbre noeud, int nb_car){
	for (int i = 0; i < nb_car; ++i)
	{
		if ((*tab_noeud)[i] == noeud){
			(*tab_noeud)[i] = NULL;
			return;
		}
	}
}

// Indique si le noeud est une feuille
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

// On crée le noeud parent des noeuds gauche et droite
p_arbre creer_parent(p_arbre gauche, p_arbre droite){
	p_arbre parent = malloc(sizeof(arbre));

	// On met les feuilles le plus à droite possible
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

// On ajoute le noeud dans le tableau
void ajouter(p_arbre **tab_noeud, int nb_car, p_arbre noeud){
	int i = 0;
	while(i < nb_car && (*tab_noeud)[i] != NULL)
		i++;
	if(i < nb_car)
		(*tab_noeud)[i] = noeud;
}


  /*
    Affichage de l'arbre a
    on l'affiche en le penchant sur sa gauche
    la partie droite (haute) se retrouve en l'air
  */
void afficher_arbre (p_arbre a, int niveau)
{
	int i ;

	if (a != NULL)
	{
		afficher_arbre (a->f_droite,niveau+1) ;

		for (i = 0; i < niveau; i++)
			printf ("\t") ;
		printf (" %lf %d (%d)\n\n", a->poids, a->caractere, a->profondeur) ;

		afficher_arbre (a->f_gauche, niveau+1) ;
	}
	return ;
}


// Création de l'arbre de Huffman

p_arbre creation_arbre(double f[ASCII], p_lecture l){
	int nb_car = char_dif(*l);
	p_arbre *tab_noeud;
	tab_noeud = init_tab(f, nb_car,*l);
	int nb_noeud = nb_car;

	p_arbre gauche, droite, parent;

	while (nb_noeud > 1){
		// On récupère les deux noeuds avec les fréquences les plus faibles
		gauche = mini(tab_noeud, nb_car);

		// Et on les supprime du tableau
		supprimer(&tab_noeud, gauche, nb_car);
		droite = mini(tab_noeud, nb_car);
		supprimer(&tab_noeud, droite, nb_car);
		// On crée le noeud parent
		parent = creer_parent(gauche, droite);
		// Et on l'ajoute au tableau
		ajouter(&tab_noeud, nb_car, parent);
		nb_noeud--;
	}

	return *tab_noeud;
}



//Fonction qui permet de trouver une feuille et de modifier la correspondance et la longueur de la feuille
void trouver_feuille(table *t, p_arbre a, int valeur){
	if(a->f_gauche == NULL && a->f_gauche == NULL){
		//C'est une feuille, modification
		modifier_correspondance(t, a->caractere, valeur);
		modifier_longueur(t, a->caractere, a->profondeur);
	}else{
		//Ce n'est pas une feuille, si on va à gauche on multiplie la valeur par 2 et on ajoute +1
		trouver_feuille(t, a->f_gauche, (valeur<<1)+1);
		//Si on va à droite on multiplie seulement la valeur par 2
		trouver_feuille(t, a->f_droite, (valeur<<1));

	}

}
//Initialisation de la table avec tous ses champs à 0
table faire_table(p_arbre a){
	table t;
	for (int i=0; i<ASCII; i++){
		modifier_longueur(&t, i,0);
		modifier_correspondance(&t,i,0);
	}
	trouver_feuille(&t,a,0);
	return t;
}

void afficher_table(table t){
	for(int i=0; i<ASCII; i++){
		if (acces_longueur(t, i)){
			printf("code ascii : %d, valeur :%d, longueur : %d\n", i, acces_correspondance(t,i), acces_longueur(t,i) );
		}
	}

}
