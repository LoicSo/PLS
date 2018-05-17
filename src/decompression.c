#include "arbres.h"
#include "structure.h"
#include "lecture_ecriture.h"
#include "arbres_fonctions.h"

p_arbre* init_tab_decomp(p_table t, int nb_car){
	int i = 0;

	p_arbre noeud;
	p_arbre *tab_noeud = malloc(nb_car * sizeof(p_arbre));

	for (int j = 0; j < nb_car; ++j)
	{
		noeud = malloc(sizeof(arbre));

		// On cherche les caracteres dont la longueur est superieure a 0
		while(i < ASCII && !acces_longueur(*t, i))
			i++;

		// On creer une feuille pour chaque caractere
		if (i < ASCII)
		{
			noeud->f_gauche = NULL;
			noeud->f_droite = NULL;
			noeud->profondeur = acces_longueur(*t, i);
			noeud->poids = 0.0;
			noeud->caractere = i;

			tab_noeud[j] = noeud;
			i++;
		}
	}
	return tab_noeud;
}

// Tri par insertion du tableau de noeud par profondeur croissante
void trier_longueur(p_arbre **tab_noeud, int nb_car){
	int i, j;
	int long_en_cours, char_en_cours;

	for (i = 1; i < nb_car; i++) {
		long_en_cours = (*tab_noeud)[i]->profondeur;
		char_en_cours = (*tab_noeud)[i]->caractere;
		for (j = i; j > 0 && (*tab_noeud)[j-1]->profondeur > long_en_cours; j--) {
			(*tab_noeud)[j]->profondeur = (*tab_noeud)[j-1]->profondeur;
			(*tab_noeud)[j]->caractere = (*tab_noeud)[j-1]->caractere;
		}
		(*tab_noeud)[j]->profondeur = long_en_cours;
		(*tab_noeud)[j]->caractere = char_en_cours;
	}
}

// Retourne un tableau avec les noeuds a la profondeur p
p_arbre* symbole(p_arbre* tab_noeud, int longueur, int nb_car, int* nb_symb){
	int tete = 0;
	int queue = 0;

	while(queue < nb_car && tab_noeud[queue]->profondeur < longueur){
		queue++;
		tete++;
	}
	while(queue < nb_car && tab_noeud[queue]->profondeur == longueur){
		queue++;
	}

	p_arbre *symb = malloc(sizeof(p_arbre) * (queue - tete));
	for (int i = tete; i < queue; ++i)
	{
		symb[i - tete] = tab_noeud[i];
	}
	*nb_symb = queue - tete;
	return symb;
}

// Creer les noeuds fils de ceux de anciens qui ne sont pas de feuille
p_arbre* creer_nouveaux(p_arbre* anciens, int *taille){
	int i = 0;
	int j = 0;
	p_arbre *res = malloc(2 * (*taille) * sizeof(arbre));
	p_arbre noeud_g, noeud_d;

	while(i < *taille){
		if (anciens[i]->caractere == -1)
		{
			noeud_d = malloc(sizeof(arbre));
			noeud_d->f_droite = NULL;
			noeud_d->f_gauche = NULL;
			noeud_d->caractere = -1;
			noeud_d->profondeur = 0;
			noeud_d->poids = 0.0;
			anciens[i]->f_droite = noeud_d;
			res[j++] = noeud_d;

			noeud_g = malloc(sizeof(arbre));
			noeud_g->f_droite = NULL;
			noeud_g->f_gauche = NULL;
			noeud_g->caractere = -1;
			noeud_g->profondeur = 0;
			noeud_g->poids = 0.0;
			anciens[i]->f_gauche = noeud_g;
			res[j++] = noeud_g;
		}
		i++;
	}
	*taille = j;
	return res;
}

p_arbre arbre_decompression(p_table t, p_lecture l){
	int nb_car = char_dif(*l);

	p_arbre *tab_noeud;
	tab_noeud = init_tab_decomp(t, nb_car);

	trier_longueur(&tab_noeud, nb_car);
	//trier_caractere(&tab_noeud, nb_car);

	int lmax = tab_noeud[nb_car-1]->profondeur;

	int p = 0;
	int c = 0;
	int taille_symbole;
	int taille_anciens;
	p_arbre *anciens;
	p_arbre *nouveaux;
	p_arbre *symb;

	p_arbre racine = malloc(sizeof(arbre));
	racine->profondeur = 0;
	racine->caractere = -1;
	racine->f_droite = NULL;
	racine->f_gauche = NULL;

	anciens = &racine;
	taille_anciens = 1;


	for (p = 1; p <= lmax; ++p)
	{
		nouveaux = creer_nouveaux(anciens, &taille_anciens);
		c <<= 1;
		symb = symbole(tab_noeud, p, nb_car, &taille_symbole);
		for (int i = 0; i < taille_symbole; ++i)
		{
			nouveaux[i]->profondeur = symb[i]->profondeur;
			nouveaux[i]->caractere = symb[i]->caractere;
			c++;
		}
		anciens = nouveaux;
	}
	return racine;
}
