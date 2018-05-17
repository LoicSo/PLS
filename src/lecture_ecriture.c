#include "lecture_ecriture.h"
#include "structure.h"
#include "pretraitement.h"

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
	
	//printf("%s\n",*nom );
	
	initialisation_struct(fichier);
	//printf("%s\n",*nom );

	fichier->taille = longueur_fichier(nom);
	//printf("%i\n", fichier->taille);

	fichier->donnee = malloc(sizeof(char) * fichier->taille);
	FILE* f = fopen(*nom,"r");
	while(!feof(f)){
    //on lit un caractère du fichier
		fscanf(f, "%c", (char*)&entier);
		caractere = (char)entier;

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

void lire_entete(char **nom_fichier, p_lecture lect, p_table t){

	FILE* f = fopen(*nom_fichier, "r");
	if(f == NULL){
		printf("erreur lors de l'ouverture du fichier");
		exit(EXIT_FAILURE);
	}

	int j = 0;	// Pour initialisation des donnees
	int l;	//sert pour la longueur du code de chaque lettre

	initialisation_struct(lect);
  //on écrit le nombre de caract
	fscanf(f,"%d", &(lect->taille));
  //on remplie le tableau longueur dans la structure table

	for(int i = 0; i<ASCII && !feof(f); i++){
		fscanf(f,"%d",&l);
		lect->char_dif += ((l != 0) ?1 :0);
		modifier_longueur(t, i, l);
		modifier_correspondance(t, i, 0);
	}

  //remplissage des donnees
	lect->donnee = malloc(sizeof(char) * taille(*lect));

	while(!feof(f)){
		fscanf(f, "%c", &(lect->donnee[j]));
		// printf("%c", lect->donnee[j]);
		j++;
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
	if(strlen(extension) == 4){
		char *sansext = malloc(sizeof(char) * strlen(sanscpr) - 4);	// .cpr = 4 caracteres
		strncpy(sansext, sanscpr, strlen(sanscpr) - 4);

		strcat(nom, sansext);
		strcat(nom, ajout);
		strcat(nom, extension);	
	}
   	// Un point mais pas d'extension ou pas de point
	else{
		strcat(nom, sanscpr);
		strcat(nom, ajout);
	}
	return nom;
}

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
		fputc(ecriture[i],fichier);
		i++;
	}
	printf("Ecriture dans le fichier %s\n", nom);

  fclose (fichier); //fermeture du fichier
  return;
}
//On initialise notre structure lecture
//   void initialisation_struct(lecture* fichier){
//   	fichier->taille = 0;
//   	fichier->char_dif = 0;
//   	for (int i=0; i<ASCII; i++)
//   		fichier->occurrence[i]=0;
//   }
// //Renvoie le nombre de caractère du fichier
//   int longueur_fichier(FILE* f){
//   	int taille;
//   	fseek(f,0,SEEK_END);
//   	taille = ftell(f);
//   	rewind(f);
//   	return taille;
//   }


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
		*(ecriture+*i) = (char)(*tmp)->caractere ;
		*i=*i+1;
		*tmp = *a;
	}
}

void decripter_donnee(p_arbre a, p_lecture l){
	int byte;

	int k = 0;
	int j = 0;
	p_arbre tmp = a;
	char current;
	taille_ecriture = taille(*l);
	ecriture = malloc(sizeof(char) * taille_ecriture);

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
