#include "lecture_ecriture.h"
#include "arbres.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>


char* int_to_char(int entier){
	int j=0;
	int h;
	float temp =(float)entier;
	int compteur =1;
	while(temp >= 10){
		temp=temp/10;
		compteur++;
	}
	// printf("entier : %d, compteur : %d \n",entier, compteur );
	char* res = malloc(compteur+1);
	for(int i=compteur-1; i>=0; i--){
		h = entier/pow(10,i);
		// printf("h:%d\n",h );
		entier=entier-h*pow(10,i);
		// printf("entier :%d\n",entier );
		*(res+j)= h + '0';
		j++;
	}
	printf(" res : %s\n", res );
	return res;
}


char* faire_entete_RLE(p_table p){
	int cmp =0;
	int temp =-1;
	int j=0;
	int deja_deux_caractere=0;
	char* buffer = malloc(sizeof(char)*4);

	char* entete = malloc(sizeof(char)*(ASCII+4));
	for(int i=0; i<ASCII; i++){
		printf("longueur : %i\n",p->longueur[i] );
		if (p->longueur[i] == temp ){
			if(deja_deux_caractere){
				cmp++;
				printf("%d\n", cmp );
			}
			else{
				deja_deux_caractere =1;
				strcat(buffer, int_to_char(p->longueur[i]));
				strcat(entete, buffer);
				j+=strlen(buffer);
				*(entete+j)= ' ';
				j++;
				free(buffer);
				buffer = malloc(sizeof(char)*4);
			}

		}
		else{
			if(cmp>0){
				printf("compteur : %i\n", cmp );
				strcat(buffer, int_to_char(cmp));
				strcat(entete, buffer);
				j+=strlen(buffer);
				*(entete+j)= ' ';
				j++;
				free(buffer);
				buffer = malloc(sizeof(char)*4);
				cmp=0;
				deja_deux_caractere=0;
			}
			strcat(buffer, int_to_char(p->longueur[i]));
			strcat(entete, buffer);
			j+=strlen(buffer);
			*(entete+j)= ' ';
			j++;
			free(buffer);
			buffer = malloc(sizeof(char)*4);

		}
		temp = p->longueur[i];
	}
	if(cmp >0){
		printf("compteur : %i\n", cmp );
		strcat(buffer, int_to_char(cmp));
		strcat(entete, buffer);
		j+=strlen(buffer);
		*(entete+j)= ' ';
		j++;
	}
	printf("entete %s\n", entete );
	return entete;

}

int main(){
	table table;
	for(int i=0; i<12;i++){
		table.longueur[i]=0;
	}
	for (int i = 12; i < ASCII; i++)
	 {
	 	table.longueur[i]=1;
	 }
	// for (int i = 104; i < ASCII; ++i)
	// {
	// 	table->longueur[i]=0;
	// }
	faire_entete_RLE(&table);
}