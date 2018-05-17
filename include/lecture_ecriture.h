#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define ASCII 256

// #ifndef ARBRE_H
// #define ARBRE_H
// #include "arbres.h"
// #endif

#ifndef LECTURE_H
#define LECTURE_H


typedef struct l{
	unsigned char* donnee;
	int occurrence[ASCII];
	int taille;
	int char_dif;
}lecture, *p_lecture; 


unsigned char* ecriture;

#endif
