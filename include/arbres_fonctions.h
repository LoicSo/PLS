#include "arbres.h"
#include "lecture_ecriture.h"

/**
 * @brief Permet d'initialiser lun tableau de noeud en fonction des fréquences.
 *
 *
 * @param f un tableau de fréquence
 * @param nb_car le nombre de caractère qui correspondra au nombre de noeuds
 *
 * @return un tableau de pointeur d'arbre
 */
p_arbre* init_tab(double *f, int nb_car);

/**
 * @brief Permet de renvoyer le pointeur d'abre avec la plus petite fréquence.
 *
 *
 * @param tab_noeud un tableau de pointeur d'arbre
 * @param nb_car nombre de noeud restant.
 *
 * @return le pointeur d'arbre avec la plus petite fréquence
 */
p_arbre mini(p_arbre tab_noeud[], int nb_car);

/**
 * @brief Permet de supprimer le noeud voulu dans un tableau de noeud
 *
 *
 * @param tab_noeud Un tableau de noeud
 * @param noeud Le noeud a supprimer
 * @param nb_car La taille dans le tableau.
 */
void supprimer(p_arbre **tab_noeud, p_arbre noeud, int nb_car);

/**
 * @brief Permet de savoir si le noeud passer en paramètre est une feuiille
 *
 *
 * @param noeud Noeud a tester
 * @return 1 si c'est une feuille 0 sinon
 */
int est_feuille(p_arbre noeud);

/**
 * @brief Permet d'incrémenter la profondeur d'un noeud et de ses fils
 *
 *
 * @param noeud Le noeud ou l'on veut incrémenter la profondeur
 */
void incrementer_prof(p_arbre noeud);

/**
 * @brief Permet de créer un arbre avec les deux fils donnés en paramètre
 *
 *
 * @param gauche Fils gauche
 * @param droite Fils droit
 *
 * @return Le pointeur d'arbre correspondant
 */
p_arbre creer_parent(p_arbre gauche, p_arbre droite);

/**
 * @brief Permet d'ajouter un noeud dans un tableau de noeud
 *
 *
 * @param tab_noeud Un tableau de noeud
 * @param nb_car la taille du tableau de noeud
 * @param noeud Le noeud a ajouter
 */
void ajouter(p_arbre **tab_noeud, int nb_car, p_arbre noeud);

/**
 * @brief Permet de creer un arbre en fonction d'un tableau de fréquence et d'une structure lecture
 *
 *
 * @param f Tableau de fréquence
 * @param l structure de lecture complète
 *
 * @return Un pointeur de noeud sur la racine
 */
p_arbre creation_arbre(double *f, p_lecture l);

/**
 * @brief Permet de trouver une feuille et de modifier la table en conséquence
 *
 *
 * @param t un pointeur de table
 * @param a Le pointeur de noeud correpsondant
 * @param valeur la valeur du code de Huffman au noeud courant
 */
void trouver_feuille(table *t, p_arbre a, int valeur);

/**
 * @brief Permet de créer une table a partir d'un arbre
 *
 *
 * @param a Le pointeur d'arbre de la racine
 * @return La table correspondante
 */
table faire_table(p_arbre a);


/**
 * @brief Permet d'afficher une table mis en paramètre
 * 
 * 
 * @param  Une table
 */
void affciher_table(table);

/**
 * @brief Permet de réalisé un arbre canonisé
 * 
 * 
 * @param t La table d'un arbre non cononisé
 * @param l  Une structure lecture 
 * @return Un arbre canonisé
 */
p_arbre arbre_decompression(p_table t, p_lecture l);

/**
 * @brief Permet d'afficher un arbre mis en paramètre
 * 
 * 
 * @param a Un arbre
 * @param niveau la profondeur duquel on veut afficher l'arbre 
 */
void afficher_arbre(p_arbre a, int niveau);
