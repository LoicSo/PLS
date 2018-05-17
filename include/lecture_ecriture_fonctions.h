#include "lecture_ecriture.h"
#include "arbres.h"

/**
 * @brief Permet d'écrire dans un fichier
 * @details Prend les données compressées
 *
 * @param nom_fichier un tableau de caractère
 * @param structure du fichier de départ
 * @param table du codage
 */
void ecrire_fichier (char *nom_fichier, lecture l, table t);

/**
 * @brief Permet d'initialiser la structure passé en paramètre
 *
 *
 * @param fichier une typedef lecture
 */
 // void initialisation_struct(p_lecture fichier);

/**
 * @brief Permet de renvoyer la longueur d'un fichier
 *
 *
 * @param f fichier de depart
 * @return la longueur du fichier
 */
// int longueur_fichier(char* nom);

/**
 * @brief Permet d'initialisé la structure depuis un fichier
 *
 *
 * @param f fichier de départ
 * @param l structure du fichier
 * @return une structure de lecture complete
 */
// lecture lire_fichier(char** nom, p_lecture l);

/**
 * @brief Permet de transcoder les caractère grace au code de Huffman
 *
 *
 * @param t la table correspondant à l'arbre de Huffman
 * @param l la structure lecture
 */
void faire_donnee(p_table t, p_lecture l);

void lire_fichier(char** nom, p_lecture fichier);
