#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ASCII 256


typedef struct l{
	char* donnee;
	int occurrence[ASCII];
	int taille;
	int char_dif;
}lecture, *p_lecture; 

char* ecriture;
