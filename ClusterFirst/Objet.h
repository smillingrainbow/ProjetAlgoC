#ifndef OBJET_H
#define OBJET_H
 
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct _Objet
{
	int idObjet;
	int coordx;
	int coordy;
	int poids;
} Objet;

void Objet_init(Objet * objet);

void Objet_setvalue_idObjet(Objet * objet, const int value);
void Objet_setvalue_coordx(Objet * objet, const int value);
void Objet_setvalue_coordy(Objet * objet, const int value);
void Objet_setvalue_poids(Objet * objet, const int value);
Objet * Objet_create(void); 

#endif //OBJET_H
