#include "lecture_ecriture.h"
#include "arbres_fonctions.h"

char* int_to_char(int entier){
	int j=0;
	int h;
	float temp =(float)entier;
	int compteur =1;
	while(temp >= 10){
		temp=temp/10;
		compteur++;
	}
	char* res = malloc(compteur+1);
	for(int i=compteur-1; i>=0; i--){
		h = entier/pow(10,i);
		entier=entier-h*pow(10,i);
		*(res+j)= h + '0';
		j++;
	}
	return res;
}


char* faire_entete_RLE(p_table p){
	int cmp =0;
	int temp =-1;
	int j=0;
	int i=0;
	char* buffer = malloc(sizeof(char)*4);

	char* entete = malloc(sizeof(char)*(2*ASCII+4));
	while(i<ASCII){
		
		if (p->longueur[i] == temp){
			i++;
			while(p->longueur[i] == temp && i<ASCII){
				
				i++;
				cmp++;
			}
			strcat(buffer, int_to_char(temp));
			strcat(entete, buffer);
			j+=strlen(buffer);
			*(entete+j)= ' ';
			j++;
			free(buffer);
			buffer = malloc(sizeof(char)*4);

			strcat(buffer, int_to_char(cmp));
			strcat(entete, buffer);
			j+=strlen(buffer);
			*(entete+j)= ' ';
			j++;
			free(buffer);
			buffer = malloc(sizeof(char)*4);
			cmp=0;
			
			if(i<ASCII){
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
			strcat(buffer, int_to_char(p->longueur[i]));
			strcat(entete, buffer);
			j+=strlen(buffer);
			*(entete+j)= ' ';
			j++;
			free(buffer);
			buffer = malloc(sizeof(char)*4);

		}
		temp = p->longueur[i];
		i++;
	}
	if(cmp >0){
		strcat(buffer, int_to_char(cmp));
		strcat(entete, buffer);
		j+=strlen(buffer);
		*(entete+j)= ' ';
		j++;
	}
	return entete;

}
