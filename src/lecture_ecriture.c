#include "lecture_ecriture.h"
#include "arbres.h"
#include "structure.h"

void ecrire_fichier (char *nom_fichier)
{
  int i = 0;
  size_t taille = 0;

  //création et ouverture d'un fichier dont le nom est passé en paramètre
  //"w" pour write : pour écrire dedans
    char* dir ="../examples/";
    char* extension = ".cpr";
    char *nom = malloc(sizeof(char)*(1+strlen(nom_fichier)+strlen(dir)+strlen(extension)));
    strcat(nom,dir);
    strcat(nom, nom_fichier);
    strcat(nom, extension);
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



void faire_donnee(p_table t, p_lecture l){
	int i=0;
	int j=0;
	// nous initialisons la taille des données à ecrire
	ecriture = malloc(sizeof(char) * l->taille);
	char current =*(l->donnee+i);
	int entier;
	int longueur;
	int  corresp;
	int compteur_current =8;
	unsigned int car_fin=0;
	unsigned char car;

	int espacement;
	int masque;
	int caractere_tmp;
	int k;
	while( current != '\0'){
		//on Prend le code ascii du caractère courant
		entier = (int)current;
		//on prend la longueur du code correspondant
		longueur =  acces_longueur(t,entier);
		//on prend l'entier correspondant au code du caractère dans l'arbre de huffman
		corresp = acces_correspondance(t,entier);
		//si la longueur tiens dans 8 les bits restant du carctère a afficher
		if(compteur_current -longueur >0){
			car_fin += (corresp << (compteur_current -longueur));
			compteur_current = compteur_current -longueur;

		}
		else if(compteur_current -longueur == 0){
			car_fin +=corresp;
			car = (char)car_fin;
			*(ecriture+j) = car;
			j++;
			car_fin=0;
			compteur_current=8;
		}
		//Sinon il faut tronquer les premier bit de l'entier afficher le caractère et ajouter le reste dans le caractère suivant
		else{
			k=0;

			do{
				espacement = longueur- compteur_current -k*8;
				masque =(1<< espacement) -1;
				caractere_tmp = corresp & masque;
				car_fin += (corresp >> espacement);
				car = (char)car_fin;
				*(ecriture+j) = car;
				j++;
				car_fin=0;
				compteur_current=8;
				corresp =caractere_tmp;
				car_fin += (caractere_tmp << compteur_current-espacement);
				compteur_current =compteur_current -espacement;
				k++;

			}while(espacement > 8);
		}
		i++;
		current =*(l->donnee+i);

	}
	car = (char)car_fin;
	*(ecriture+j) = car;

}

//////////////// DECODAGE
/*
LE FICHIER MUST BE OPENED
lecture de l'entete :
remplis la lecture : taille et donnees
remplis la table  : longueur
ferme le fichier
*/
void lire_entete(FILE* f, p_lecture lect, p_table t){
  initialisation_struct(lect);
  //on écrit le nombre de caract
  fscanf(f,"%d", &(p_lecture->taille);
  //on remplie le tableau longueur dans la structure table
  int l;//sert pour la longueur de chaque lettre
  for(int i = 0, i<ASCII && !feof(f), i++){
    fscanf(f,"%c",&l);
    modifier_longueur(&t, i, l);
		modifier_correspondance(&t, i, 0);
  }
  //remplissage des donnees
  p_lecture->donnee = malloc(taille(&l));
  int i = 0;
  while(!feof(f)){
    fscanf(f, "%c", p_lecture->donnee[i++];
  }
}

int main_test_faire_donee(){
	table t;
	t.correspondance[65] = 5;
	t.correspondance[66] = 345;
	t.longueur[65]=3;
	t.longueur[66]=9;

	lecture l;
	l.donnee = "BABA";
	l.taille=4;

	faire_donnee(&t,&l);
	printf("chaine compressé :%s\n",ecriture );

}
