#include "lecture_ecriture_fonctions.h"
#include "arbres_fonctions.h"
#include "calcul.h"

/*
incrémente les options possibles
Ouvre le fichier en lecture
return le nom du fichier
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
				printf("%s : bad argument\n", argv[i]);
				exit(EXIT_FAILURE);
			}
		}
    //c'est le nom de fichier
		else {
			*nomFichier = malloc((sizeof(char)*strlen(argv[i])));
			strcpy(*nomFichier, argv[i]);
		}
	}
  //si il n'y a pas de parmètres
	if((*c + *d) != 1){
		printf("Un seul un paramètre -c (compression) ou -d (decompression) est requis.\n");
		exit(EXIT_FAILURE);
	}
  //si on a pas de nom de fichier: pb
	if (argc - *c - *d == 1){
		printf("Il manque le nom de fichier...\n");
		exit(EXIT_FAILURE);
	}
}

void compression (char** nom_fichier){
  // lire
	double frequence[ASCII];	// tableau des frequence de chaque caractere
	p_lecture l = malloc(sizeof(lecture));	// notre structure de lecture
	p_arbre a = malloc(sizeof(arbre));	// notre arbre de Huffman
	p_table t= malloc(sizeof(table));	// notre table de correspondance
	
	//printf("%s\n", *nom_fichier );
	// char* temp = malloc(sizeof(50));
	// strcpy(temp, *nom_fichier);
	// printf("%s\n",temp );
	lire_fichier(nom_fichier, l);

  // freq
	//printf("nombre différent %d\n", l->char_dif);
	calcul_frequence(frequence, *l);
  // arbre
	a = creation_arbre(frequence, l);
	*t=faire_table(a);
	a = arbre_decompression(t, l);
	//canoniser(a);
  // table
	*t=faire_table(a);
	affciher_table(*t);
  // donnees
	faire_donnee(t,l);
  // ecrire donnees
	ecrire_fichier(*nom_fichier, *l, *t);
}

void decompression (){
  //lire_entete
  //decoder
  //ecrire donnees
}


int main(int argc, char* argv[]){
	int param_c, param_d;
	char* nomFichier;
	lignecommande(argc, argv, &param_d, &param_c, &nomFichier);
	if(param_c){
		//printf("%s\n", *nom_fichier );
		compression(&nomFichier);
	}
	else if(param_d){
    //TODO decompression()
	}

	return 0;
}
