#include "lecture_ecriture.h"
#include <stdlib.h>

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
    printf("Au moins un paramètre -c (compression) ou -d (decompression) et requis.\n");
    exit(0);
  }
  return nomfichier;
}


int main(int argc, char* argv[]){
  int param_c, param_d;
  FILE* fichier = NULL;
  char* nomFichier = lignecommande(argc, argv, &param_d, &param_c, &fichier);

  if(param_c){
    //TODO compression()
  }
  else if(param_d){
    //TODO decompression()
  }

  return 0;
}
