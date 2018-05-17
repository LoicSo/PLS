#ifndef LECTURE_H
#define LECTURE_H
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ASCII 256


typedef struct l{
	char* donnee;
	int occurrence[ASCII];
	int taille;
	int char_dif;
}lecture, *p_lecture; 

 char* ecriture;

/**
 * @brief Permet d'écrire dans un fichier 
 * @details Prend les données compressées
 * 
 * @param nom_fichier un tableau de caractère 
 */
void ecrire_fichier (char *nom_fichier);

/**
 * @brief Permet d'initialiser la structure passé en paramètre
 * 
 * 
 * @param fichier une typedef lecture
 */
void initialisation_struct(lecture* fichier);

/**
 * @brief Permet de renvoyer la longueur d'un fichier 
 * 
 * 
 * @param f fichier de depart
 * @return la longueur du fichier
 */
int longueur_fichier(FILE* f);

/**
 * @brief Permet d'initialisé la structure depuis un fichier
 * 
 * 
 * @param f fichier de départ
 * @return une structure de lecture complete
 */
lecture lire_fichier(FILE* f);

// *
//  * @brief Permet de transcoder les caractère grace au code de Huffman
//  * 
//  * 
//  * @param t la table correspondant à l'arbre de Huffman
//  * @param l la structure lecture
 
// void faire_donnee(p_table t, p_lecture l);



