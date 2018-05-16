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
        exit(0);
      }
    }
    //c'est le nom de fichier
    else {
      *nomFichier = malloc((sizeof(char)*strlen(argv[i])));
      *nomFichier = argv[i];
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
}
//On initialise notre structure lecture
void initialisation_struct(p_lecture fichier){
  fichier->taille = 0;
  fichier->char_dif = 0;
  for (int i=0; i<ASCII; i++)
    fichier->occurrence[i]=0;
}

//Renvoie le nombre de caractère du fichier
int longueur_fichier(char** nom){
  FILE* f=fopen(*nom,"r");
  if (f == NULL)
    {
      printf ("Erreur lors de l'ouverture du fichier.\n");
      exit(1);
    }
  int taille=0; char c;
  while((c=fgetc(f)) != EOF){
    taille++;
    printf("%c",c );
  }
  fclose(f);
  return taille;
}

//On remplit notre structure à partir des données d'un fichier passé en paramètre
void lire_fichier(char** nom, p_lecture fichier){
  unsigned char caractere;
  unsigned int entier;
  int i=0;
  printf("hlleo\n" );
  printf("%s\n",*nom );
  printf("coucou\n");
  initialisation_struct(fichier);
  printf("%s\n",*nom );
  fichier->taille = longueur_fichier(nom);
  printf("%i\n", fichier->taille);
  fichier->donnee=malloc(sizeof(char)*fichier->taille);
  FILE* f=fopen(*nom,"r");
  while(!feof(f)){
    //on lit un caractère du fichier
    fscanf(f,"%c", (char*)&entier);
    caractere = (char)entier;
    //On ajoute ce caractère dans notre structure
    fichier->donnee[i]=caractere;
    //Si le caractère n'a encore jamais été lu, on incrémente la variable qui correspond au nombre de caractères différents
    if (fichier->occurrence[(int)caractere] == 0)
      fichier->char_dif++;
    //On incrémente l'occurence du caractère
    fichier->occurrence[(int)caractere]++;
    i++;
  }
  printf("char dif : %d\n", fichier->char_dif);
  fclose(f);
}





void compression (char** nom_fichier){
  // lire
  double frequence[ASCII];
  p_lecture l= malloc(sizeof(lecture));
  p_arbre a = malloc(sizeof(arbre));
  p_table t= malloc(sizeof(table));
  printf("%s\n", *nom_fichier );
  char* temp = malloc(sizeof(50));
  strcpy(temp, *nom_fichier);
  printf("%s\n",temp );
  lire_fichier(&temp,l);
  // freq
  printf("nombre différent %d\n", l->char_dif);
  calcul_frequence(frequence, *l);
  // arbre
  a = creation_arbre(frequence, l);
  canoniser(a);
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
    printf("%s\n",nomFichier );
    compression(&nomFichier);
  }
  else if(param_d){
    //TODO decompression()
  }

  return 0;
}
