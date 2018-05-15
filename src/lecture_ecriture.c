#include "lecture_ecriture.h"

//On initialise notre structure lecture
void initialisation_struct(lecture* fichier){
  fichier->taille = 0;
  fichier->char_dif = 0;
  for (int i=0; i<ASCII; i++)
    fichier->occurrence[i]=0;
}
//Renvoie le nombre de caractère du fichier
int longueur_fichier(FILE* f){
  int taille;
  fseek(f,0,SEEK_END);
  taille = ftell(f);
  rewind(f);
  return taille;
}

//On remplit notre structure à partir des données d'un fichier passé en paramètre
lecture lire_fichier(FILE* f){
  lecture fichier;
  char caractere;
  int i=0;
  int j;
  initialisation_struct(&fichier);
  fichier.taille = longueur_fichier(f);
  fichier.donnee=malloc(sizeof(char)*fichier.taille);
  while(!feof(f)){
    //on lit un caractère du fichier
    fscanf(f,"%c", &caractere);
    //On ajoute ce caractère dans notre structure
    fichier.donnee[i]=caractere;
    //Si le caractère n'a encore jamais été lu, on incrémente la variable qui correspond au nombre de caractères différents
    if (!fichier.occurrence[caractere])
      fichier.char_dif++;
    //On incrémente l'occurence du caractère
    fichier.occurrence[caractere]++;
    i++;
  }
  return fichier;
}
