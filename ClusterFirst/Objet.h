#ifndef CLUSTERFIRST_H
#define CLUSTERFIRST_H
 
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

struct Objet
{
	int idObjet;
	int coordx;
	int coordy;
	int poids;
};

void Objet_init(Objet * objet);

void Objet_setvalue_idObjet(Objet * objet, const int value);
void Objet_setvalue_coordx(Objet * objet, const int value);
void Objet_setvalue_coordy(Objet * objet, const int value);
void Objet_setvalue_poids(Objet * objet, const int value);
 Objet *  = Objet * Objet_create(void); 

#endif //CLUSTERFIRST_H
