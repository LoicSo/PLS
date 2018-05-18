/**
 * @file lecture.c
 */
#include "lecture_ecriture.h"
#include "structure.h"
#include "pretraitement.h"
#include "arbres_fonctions.h"

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
	FILE* f = fopen(*nom,"r");
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
	
	printf("%s\n",*nom );
	
	initialisation_struct(fichier);
	// printf("%s\n",*nom );

	fichier->taille = longueur_fichier(nom);
	//printf("%i\n", fichier->taille);

	fichier->donnee = malloc(sizeof( unsigned char) * fichier->taille);
	FILE* f = fopen(*nom,"r");
	int j = 0;
	while(!feof(f)){
    //on lit un caractère du fichier
		caractere =fgetc(f);
		entier = (unsigned int )caractere;
		// caractere = (unsigned char)entier;
		if ( j++< 5)
			printf("%c ------ %i\n",caractere, entier );

    //On ajoute ce caractère dans notre structure
		fichier->donnee[i] = caractere;

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

/*
lecture de l'entete
remplis la lecture : taille et donnees
remplis la table  : longueur
*/
void lire_entete(char **nom_fichier, p_lecture lect, p_table t){

	FILE* f = fopen(*nom_fichier, "r");
	if(f == NULL){
		printf("erreur lors de l'ouverture du fichier");
		exit(EXIT_FAILURE);
	}

	int l;//sert pour la longueur de chaque lettre
	int prec = -2;//sert pour le RLE, -2 n'est pas un caractère
	int j; //car on commence avec le caractere precedent le nombre d'occurence
	int occur;
	int i = 0;

	initialisation_struct(lect);
  //on écrit le nombre de caract
	fscanf(f,"%d", &(lect->taille));
	printf("taille : %d\n", lect->taille);


	while(i<ASCII && !feof(f)){
		j = 0; //parcours pour RLE
		occur = 0; //
		fscanf(f,"%d",&l);
				//Cas RLE
		if(prec == l){
			fscanf(f,"%d",&occur); //récupère le nombre d'occurence du char
  		}

		  while(j<=occur){
		  	lect->char_dif += (l!=0) ? 1 : 0;
		  	modifier_longueur(t, i, l);
		  	modifier_correspondance(t, i, 0);
			j++;//parcours des occurences
			i++;//parcours la table
		}
		prec = l;
	}
	fseek(f, 1, SEEK_CUR); // on saute l'espace de fin d'entete
	printf("Affichage de la table après lecture de l'entete\n");
	affciher_table(*t);

	  //remplissage des donnees
	lect->donnee = malloc(taille(*lect));
	i = 0;
	while(!feof(f)){
		fscanf(f, "%c", &(lect->donnee[i++]));
	}
	fclose(f);
}

char* creer_nom_fichier(char* nom_fichier){
	char* ajout = "_decomp";
	char* sanscpr = malloc(sizeof(char) * strlen(nom_fichier) - 4);	// .cpr = 4 caracteres
	strncpy(sanscpr, nom_fichier, strlen(nom_fichier) - 4);

	char* nom = malloc(sizeof(char) * (strlen(sanscpr) + strlen(ajout)));

	char *extension;	// extension potentielle
	extension = strrchr(sanscpr, '.');

   	// Un point avec une extension 
	if(extension == NULL){
		strcat(nom, sanscpr);
		strcat(nom, ajout);
	}
   	// Un point mais pas d'extension ou pas de point
	else{
		char *sansext = malloc(sizeof(char) * (strlen(sanscpr) - strlen(extension)));	// .cpr = 4 caracteres
		strncpy(sansext, sanscpr, strlen(sanscpr) - strlen(extension));

		strcat(nom, sansext);
		strcat(nom, ajout);
		strcat(nom, extension);	
	}
	return nom;
}

/**
 * @brief Permet d'écrire dans un fichier
 * @details Prend les données compressées
 *
 * @param nom_fichier un tableau de caractère
 * @param structure du fichier de départ
 * @param table du codage
 */
void ecrire_fichier (char *nom_fichier, lecture l, table t, int decompression)
{
	int i = 0;
	char *nom;

  //création et ouverture d'un fichier dont le nom est passé en paramètre
  //"w" pour write : pour écrire dedans

	if(!decompression){
		char* extension = ".cpr";
		nom = malloc(sizeof(char)*(1+strlen(nom_fichier)+strlen(extension)));

		strcat(nom, nom_fichier);
		strcat(nom, extension);
	}
	else{
		nom = creer_nom_fichier(nom_fichier);
	}

	FILE* fichier = fopen (nom, "w+");
  //si création du fichier impossible : erreur
	if (fichier == NULL)
	{
		printf ("Erreur lors de la création du fichier.\n");
		exit(EXIT_FAILURE);
	}

	if(!decompression){

  //  		ecriture du nombre de caractere
		fprintf(fichier, "%i ", taille(l) );

  //  		// ecriture de la table de longueur
		// for(int j=0; j<ASCII; j++)
		// 	fprintf(fichier, "%i ",acces_longueur(t, j));
		char* table = faire_entete_RLE(&t);
		fputs(table,fichier);
	}

  	//écriture dans le fichier des données du fichier

	while (i != taille_ecriture) {
		fprintf(fichier, "%c",ecriture[i] );
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
	ecriture = malloc(sizeof( unsigned char) * l->taille);
	unsigned char current =*(l->donnee+i);
	unsigned int entier;
	int longueur;
	int  corresp;
	int compteur_current =8;
	unsigned int car_fin=0;
	unsigned char car;

	int espacement;
	int masque;
	unsigned int caractere_tmp;
	int k;
	while(current != '\0'){
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
			car = ( unsigned char)car_fin;
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
				car = ( unsigned char)car_fin;
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
	car = ( unsigned char)car_fin;
	*(ecriture+j) = car;
	taille_ecriture = j;
  // printf("j : %d\n", j );
  // printf("strlen ecriture %li\n", strlen(ecriture) );

}

int prendre_byte( unsigned char current, int i){
	int res=0;
	res = current & (1 << (i-1));
	res >>= (i-1);
	return res;

}

void traiter_bit(p_arbre *tmp, int byte, p_arbre *a, int *i ){
	if(byte){
		*tmp = (*tmp)->f_gauche;
	}
	else{
		*tmp = (*tmp)->f_droite;
	}

	if((*tmp)->f_droite == NULL && (*tmp)->f_gauche == NULL ){
		*(ecriture+*i) = ( unsigned char)(*tmp)->caractere ;
		*i=*i+1;
		*tmp = *a;
	}
}

void decripter_donnee(p_arbre a, p_lecture l){
	int byte;

	int k = 0;
	int j = 0;
	p_arbre tmp = a;
	unsigned char current;
	taille_ecriture = taille(*l);
	ecriture = malloc(sizeof( unsigned char) * taille_ecriture);

	current = l->donnee[j];

	while(k < taille_ecriture){
		for(int i = TAILLE_CHAR; i > 0; i--){
			byte = prendre_byte(current, i);
			traiter_bit(&tmp, byte, &a, &k);
		}
		j++;
		current =*(l->donnee+j);
	}
	return;
}
