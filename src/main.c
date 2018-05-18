#include "lecture_ecriture_fonctions.h"
#include "arbres_fonctions.h"
#include "calcul.h"

/*
incrémente les options possibles
Ouvre le fichier en lecture
retourne le nom du fichier
*/
void lignecommande(int argc, char *argv[], int* d, int* c, char** nomFichier) {
	*d = *c = 0;
	for (int i = 1; i < argc; i++) {
    //si c'est un paramètre
		if(argv[i][0] == '-'){
			if (strcmp(argv[i], "-d") == 0){
				*d += 1;
			}
			else if (strcmp(argv[i], "-c") == 0) {
				*c += 1;
			}
			else{
				printf("%s : Mauvais argument.\n", argv[i]);
				exit(EXIT_FAILURE);
			}
		}
    //c'est le nom de fichier
		else {
			*nomFichier = malloc((sizeof(char)*strlen(argv[i])));
			strcpy(*nomFichier, argv[i]);
		}
	}
  //si il n'y a pas de parmètre
	if((*c + *d) != 1){
		printf("Un paramètre est requis : -c (compression) ou -d (decompression).\n");
		exit(EXIT_FAILURE);
	}
  //si on a pas de nom de fichier: problème
	if (argc - *c - *d == 1){
		printf("Il manque le nom de fichier...\n");
		exit(EXIT_FAILURE);
	}
}

void compression (char** nom_fichier){
  // lire
	double frequence[ASCII];	// tableau des frequences de chaque caractère
	p_lecture l = malloc(sizeof(lecture));	// notre structure de lecture
	p_arbre a;	// notre arbre de Huffman
	p_table t = malloc(sizeof(table));	// notre table de correspondance
	
	printf("Début compression :\n");
	lire_fichier(nom_fichier, l);
	printf("     Lecture de fichier..\n");

  // frequence
	calcul_frequence(frequence, *l);
	printf("     Calcul des fréquences..\n");
  // arbre
	a = creation_arbre(frequence, l);
	*t = faire_table(a);
	printf("     Création de l'arbre..\n");
	a = arbre_decompression(t, l);
  // table
	*t=faire_table(a);
  // données
	printf("     Transcodage..\n");
	faire_donnee(t,l);
  // écrire données
	ecrire_fichier(*nom_fichier, *l, *t, 0);
}

void decompression (char **nom_fichier){
	printf("Début de décompression :\n");
	p_lecture l = malloc(sizeof(lecture));	// notre structure de lecture
	p_arbre a;	// notre arbre de Huffman
	p_table t = malloc(sizeof(table));	// notre table de correspondance

  //lire_entête
	printf("     Lecture d'entete..\n");
	lire_entete(nom_fichier, l, t);
	// arbre
	a = arbre_decompression(t, l);
  //decoder
	printf("     Decryptage des données..\n");
	decripter_donnee(a, l);

  //ecrire données
	ecrire_fichier(*nom_fichier, *l, *t, 1);
}


int main(int argc, char* argv[]){
	int param_c, param_d;
	char* nomFichier;
	lignecommande(argc, argv, &param_d, &param_c, &nomFichier);
	if(param_c){
		printf("%s\n", nomFichier );
		compression(&nomFichier);
	}
	else if(param_d){
		decompression(&nomFichier);
	}
	return 0;
}
