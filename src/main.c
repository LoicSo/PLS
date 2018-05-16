#include "lecture_ecriture_fonctions.h"
#include "arbres_fonctions.h"
#include "calcul.h"

/*
incrémente les options possibles
Ouvre le fichier en lecture
return le nom du fichier
*/
char *lignecommande(int argc, char *argv[], int* d, int* c, FILE **fichier) {
  char *nomfichier;
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
        exit(0);
      }
    }
    //c'est le nom de fichier
    else {
      *fichier = fopen(argv[i], "r");
      nomfichier = argv[i];
    }
  }
  //si il n'y a pas de parmètres
  if(!*c && !*d){
    printf("Au moins un paramètre -c (compression) ou -d (decompression) est requis.\n");
    exit(0);
  }
  //si on a pas de nom de fichier: pb
  if (argc - *c - *d == 1){
    printf("Il manque le nom de fichier...\n");
    exit(0);
  }
  return nomfichier;
}

void compression (FILE* fichier, char* nom_fichier){
  // lire
  p_lecture l=NULL;
  p_arbre a=NULL;
  p_table t=NULL;

  lire_fichier(fichier,l);
  // freq
  calcul_frequence(*l);
  // arbre
  a = creation_arbre(frequence, l);
  canoniser(a);
  // table
  *t=faire_table(a);
  // donnees
  faire_donnee(t,l);
  // ecrire donnees
  ecrire_fichier(nom_fichier, *l, *t);
}

void decompression (){
  //lire_entete
  //decoder
  //ecrire donnees
}


int main(int argc, char* argv[]){
  int param_c, param_d;
  FILE* fichier = NULL;
  char* nomFichier = lignecommande(argc, argv, &param_d, &param_c, &fichier);
  if (fichier == NULL)
    {
      printf ("Erreur lors de l'ouverture du fichier.\n");
      exit(1);
    }
  if(param_c){
    compression(fichier,nomFichier);
  }
  else if(param_d){
    //TODO decompression()
  }

  return 0;
}
