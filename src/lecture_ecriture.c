#include "lecture_ecriture.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void
ecrire_fichier (char *nom_fichier)
{
  int i = 0;
  size_t taille = 0;

  //création et ouverture d'un fichier dont le nom est passé en paramètre
  //"w" pour write : pour écrire dedans
    char* dir ="../examples/";
    char *nom = malloc(sizeof(char)*(1+strlen(nom_fichier)+strlen(dir)));
    strcat(nom,dir);
    strcat(nom, nom_fichier);
    FILE* fichier = fopen (nom, "w+");
  //si création du fichier impossible : erreur
  if (fichier == NULL)
    {
      printf ("Erreur lors de la création du fichier.\n");
      exit(1);
    }
  taille = strlen(ecriture);
  //écriture dans le fichier des données du fichier
  while (i != taille) {
    fprintf (fichier, "%c", ecriture[i]);
    i++;
  }

  fclose (fichier); //fermeture du fichier
  return;
}

