#include "lecture_ecriture.h"
#include "structure.h"

#define TAILLE_CHAR 8

int taille_ecriture;

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
		exit(EXIT_FAILURE);
	}
	int taille=0;
	while((fgetc(f)) != EOF){
		taille++;
		// printf("%c",c );
	}
	fclose(f);
	return taille;
}

//On remplit notre structure à partir des données d'un fichier passé en paramètre
void lire_fichier(char** nom, p_lecture fichier){
	unsigned char caractere;
	unsigned int entier;
	int i=0;
	
	//printf("%s\n",*nom );
	
	initialisation_struct(fichier);
	//printf("%s\n",*nom );

	fichier->taille = longueur_fichier(nom);
	//printf("%i\n", fichier->taille);

	fichier->donnee=malloc(sizeof(char)*fichier->taille);
	FILE* f = fopen(*nom,"r");
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
	//printf("char dif : %d\n", fichier->char_dif);
	fclose(f);
}

void ecrire_fichier (char *nom_fichier, lecture l, table t)
{
	int i = 0;
	// size_t taille = 0;

  //création et ouverture d'un fichier dont le nom est passé en paramètre
  //"w" pour write : pour écrire dedans
    // char* dir ="../examples/";
	char* extension = ".cpr";
	char *nom = malloc(sizeof(char)*(1+strlen(nom_fichier)+strlen(extension)));
    // strcat(nom,dir);
	size_t taille = 0;

  //création et ouverture d'un fichier dont le nom est passé en paramètre
  //"w" pour write : pour écrire dedans
	char* dir ="../examples/";
	char* extension = ".cpr";
	char *nom = malloc(sizeof(char)*(1+strlen(nom_fichier)+strlen(extension)));
	strcat(nom, nom_fichier);
	strcat(nom, extension);
	FILE* fichier = fopen (nom, "w+");
  //si création du fichier impossible : erreur
	if (fichier == NULL)
	{
		printf ("Erreur lors de la création du fichier.\n");
		exit(1);
	}
	fprintf(fichier, "%i ", l.taille );
	for(int j=0; j<ASCII; j++)
		fprintf(fichier, "%i ",t.longueur[j]);
  	//écriture dans le fichier des données du fichier
	// taille = strlen(ecriture);
  	//printf("taille : %d\n", (int)taille );
	while (i != taille_ecriture) {
		fprintf (fichier, "%c", ecriture[i]);
		i++;
	}
	printf("Ecriture dans le fichier %s\n", nom);

  fclose (fichier); //fermeture du fichier
  return;
}

void faire_donnee(p_table t, p_lecture l){
	int i=0;
	int j=0;
	// nous initialisons la taille des données à ecrire
	ecriture = malloc(sizeof(char) * l->taille);
	unsigned char current =*(l->donnee+i);
	unsigned int entier;
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
    		// printf("%d\n",entier );
		//on prend la longueur du code correspondant
		longueur =  acces_longueur(*t,entier);
   		 // printf("longueur : %d\n", longueur );
		//on prend l'entier correspondant au code du caractère dans l'arbre de huffman
		corresp = acces_correspondance(*t,entier);
   		 // printf("corresp : %d\n", corresp );

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
				car_fin += (caractere_tmp << (compteur_current-espacement));
				compteur_current =compteur_current -espacement;
				k++;

			}while(espacement > 8);
		}
		i++;
		current =*(l->donnee+i);

	}
	car = (char)car_fin;
	*(ecriture+j) = car;
	taille_ecriture = j;
  // printf("j : %d\n", j );
  // printf("strlen ecriture %li\n", strlen(ecriture) );

}

int prendre_byte(char current, int i){
	int res=0;
	res &= 1<<(i-1);
	res= res >>(i-1);
	return res;

}

void traiter_bit(p_arbre *tmp, int byte, p_arbre *a, int *i ){
	if(byte){
		*tmp = *tmp->f_gauche;
	}
	else{
		*tmp = *tmp->f_droite;
	}

	if(*tmp->f_droite == NULL && *tmp->f_gauche == NULL ){
		*(ecriture+*i) = (char)*tmp->caractere ;
		*i=*i+1;
		*tmp = *a;
	}
}

void decripter_donnee(p_arbre a, p_lecture l){
	int byte;
	int k=0;
	p_arbre tmp = a;
	char current;
	int taille = taille(l);
	ecriture = malloc(sizeof(char)*taille);

	current =*(l->donnee+i);
	while(current != '\0' && i<taille){
		for(int i=TAILLE_CHAR; i >0; i--){
			byte = prendre_byte(current, i);
			traiter_bit(&tmp, byte, &a, &k);
		}
	}
	
	return;
}
