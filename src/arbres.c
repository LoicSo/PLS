#include <stdlib.h>

#include "arbres.h"
#include "calcul.h"
#include "structure.h"


/* Initialisation du tableau de noeud avec toutes les feuilles */
p_arbre* init_tab(double f[ASCII], int nb_car, lecture l){
	int i = 0;
	p_arbre noeud;

	p_arbre *tab_noeud = malloc(nb_car * sizeof(p_arbre));

	//printf("nb car %d\n", nb_car);
	for (int j = 0; j < nb_car; ++j)
	{
		noeud = malloc(sizeof(arbre));

		// On cherche les caracteres presents dans les donnees
		while(i < ASCII && acces_occurrence(l,i) == 0){
					i++;
		}
		// On creer une feuille pour chaque caractere
		if (i < ASCII)
		{
			noeud->f_gauche = NULL;
			noeud->f_droite = NULL;
			noeud->profondeur = 0;
			noeud->poids = f[i];
			noeud->caractere = i;
			//printf("poids: %lf    caract: %d    j: %d\n", f[i], i,  j);

			tab_noeud[j] = noeud;
			i++;
		}
	}
	return tab_noeud;
}

// On cherche le noeud avec la frequence la plus basse
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

// On creer le noeud parent des noeuds gauche et droite
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
		printf (" %lf %d (%d)\n\n", a->poids, a->caractere, a->profondeur) ;

		afficher_arbre (a->f_gauche, niveau+1) ;
	}
	return ;
}


// Creation de l'arbre de Huffman

p_arbre creation_arbre(double f[ASCII], p_lecture l){
	int nb_car = char_dif(*l);
	p_arbre *tab_noeud;
	tab_noeud = init_tab(f, nb_car,*l);
	int nb_noeud = nb_car;

	p_arbre gauche, droite, parent;

	while (nb_noeud > 1){
		// On recupere les deux noeuds avec les frequences les plus faible
		gauche = mini(tab_noeud, nb_car);
		// printf("%d\n", gauche->caractere);
		// Et on les supprime du tableau
		supprimer(&tab_noeud, gauche, nb_car);
		droite = mini(tab_noeud, nb_car);
		// printf("%d\n", droite->caractere);
		supprimer(&tab_noeud, droite, nb_car);
		// On cree le noeud parent
		parent = creer_parent(gauche, droite);
		// Et on l'ajoute au tableau
		ajouter(&tab_noeud, nb_car, parent);
		nb_noeud--;
	}
	// afficher_arbre(*tab_noeud, 0);
	return *tab_noeud;
}




void trouver_feuille(table *t, p_arbre a, int valeur){
	//Fonction qui permet de trouver une feuille et de modifier la correspondance et la longueur de la feuille
	if(a->f_gauche == NULL && a->f_gauche == NULL){
		//C'est une feuille, modification
		modifier_correspondance(t, a->caractere, valeur);
		modifier_longueur(t, a->caractere, a->profondeur);
	}else{
		//Ce n'est pas une feuille, si on va a gauche on multiplie la valeur par 2 et nous ajouter +1
		trouver_feuille(t, a->f_gauche, (valeur<<1)+1);
		//Si on va a droite on multiplie seulement la valeur par 2
		trouver_feuille(t, a->f_droite, (valeur<<1));

	}

}

table faire_table(p_arbre a){
	//Initialisation de la table avec tous ses champs a 0
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


//fonctions p_file
void enfile (p_file f, p_arbre n){
	// printf("queue : %d\n", f->queue);
  f->T[f->queue++] = n;
}

p_arbre defile (p_file f){
  return f->T[f->tete++];
}

int fileVide(p_file f){
	// printf("tete: %d, queue: %d\n", f->tete, f->queue);
  if (f->tete == f->queue){
    return 1;
  }
  return 0;
}

//remplis une file simplement avec les noeuds de l'arbre
p_file remplir_file_largeur (p_arbre a){
	// afficher_arbre(a, 0);
  p_file aFaire = (p_file) malloc (sizeof(file));
  aFaire->tete = 0;
  aFaire->queue = 0;
  p_file resultat = (p_file) malloc (sizeof(file));
  resultat->tete = 0;
  resultat->queue = 0;

  // //initialisation de la p_file resultat avec le noeud racine
  // enfile(resultat, a);
  //initialisation de la p_file de noeuds a parcourir
  if(a->f_gauche != NULL)
    enfile(aFaire, a->f_gauche);
  if(a->f_droite != NULL)
    enfile(aFaire, a->f_droite);

    //pour chaque noeud a parcourir on ajoute les enfants dans result
		// printf("okokokokok\n");
  while (!fileVide(aFaire)){
    p_arbre tmp = defile(aFaire);
    if(tmp->f_gauche == NULL && tmp->f_droite == NULL){
			// printf("01\n");
      enfile(resultat, tmp);
			// printf("02\n");
    }else{
			// printf("03\n");
      if(tmp->f_gauche != NULL)
        enfile(aFaire, tmp->f_gauche);
			// printf("04\n");
      if(tmp->f_droite != NULL)
        enfile(aFaire, tmp->f_droite);
			// printf("05\n");
		}
  }
  return resultat;
}

//trie la sequence entre n->tete et n->queue-1
void trier_sequence(p_file n){
  while(n->tete < n->queue-1){
    //on cherche le plus grand caractere de la sequence
    int id_max = n->tete;
    for(int i = n->tete+1; i<n->queue; i++){
      id_max = (n->T[id_max]->caractere > n->T[i]->caractere) ? id_max : i;
    }
    //si ce n'est pas le premier, on les switch
    if(id_max>n->tete){
      int caract_tmp = n->T[n->tete]->caractere;
      double poids_tmp = n->T[n->tete]->poids;
      n->T[n->tete]->caractere = n->T[id_max]->caractere;
      n->T[n->tete]->poids = n->T[id_max]->poids;
      n->T[id_max]->caractere = caract_tmp;
      n->T[id_max]->poids = poids_tmp;
    }
    n->tete++;
  }
  n->tete++;//n->tete == n->queue
}

void canoniser(p_arbre a){
  p_file noeuds = remplir_file_largeur(a);
  int taille = noeuds->queue;
  //NOTE a partir d'ici on utilise la file comme sequence de feuilles de meme poids
  noeuds->queue = 0;
  noeuds->tete = 0;
  while(noeuds->queue < taille){
    int profondeur = noeuds->T[noeuds->queue++]->profondeur; //on charge la profondeur de la sequence de noeud à trier
    while(noeuds->queue < taille && noeuds->T[noeuds->queue]->profondeur == profondeur)
      noeuds->queue++; //on incrémente queue jusqu'a ce que la la feuille ne soit plus sur la meme ligne.
    //trie de la sequence
    trier_sequence(noeuds);
  }
  //en sortie, n->tete = n->queue = taille
  //l'arbre est canoniser grace au trie
  afficher_arbre(a, 0);
}
