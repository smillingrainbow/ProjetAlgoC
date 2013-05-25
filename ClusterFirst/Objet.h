#ifndef OBJET_H
#define OBJET_H
 
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "util.h"

/**
 * Structure Objet 
 * Chaque cellule contient :
 * @param idObjet un entier non signé correspondant à l'identifiant du produit
 * @param coordx un entier correspondant au coordonnée suivant l'axe des abscisses
 * @param coordy un entier correspondant au coordonnée suivant l'axe des ordonnées
 * @param poids un entier non signé indiquant le poids du produit
 * @param trie un booleen indiquant si le produit a été trié dans un Cluster
 */
typedef struct _Objet
{
	unsigned int idObjet;
	int coordx;
	int coordy;
	unsigned int poids;
	bool trie; 
} Objet;

void Objet_init(Objet * objet);

void Objet_setvalue_idObjet(Objet * objet, const unsigned int value);
void Objet_setvalue_coordx(Objet * objet, const int value);
void Objet_setvalue_coordy(Objet * objet, const int value);
void Objet_setvalue_poids(Objet * objet, const unsigned int value);

Objet * Objet_create(void); 

#endif //OBJET_H
