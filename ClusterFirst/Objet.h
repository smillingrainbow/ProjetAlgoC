#ifndef OBJET_H
#define OBJET_H
 
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "util.h"


/**
 * \_struct Objet
 * \brief Objet contenant les informations d'un produit
 *
 * Objet contient toutes les informations relatives à un objet : son identifiant, ses coordonées x et y, ainsi que son poids.
 */
typedef struct _Objet
{
	unsigned int idObjet; /*!< entier non signé correspondant à l'identifiant du produit */
	int coordx; /*!< entier signé correspondant au coordonée x du produit */
	int coordy; /*!< entier signé correspondant au coordonée y du produit */
	unsigned int poids; /*!< entier non signé correspondant au poids du produit */
	bool trie; /*!< booleen indiquant si le produit a été trié dans un Cluster */
} Objet;

void Objet_init(Objet * objet);

void Objet_setvalue_idObjet(Objet * objet, const unsigned int value);
void Objet_setvalue_coordx(Objet * objet, const int value);
void Objet_setvalue_coordy(Objet * objet, const int value);
void Objet_setvalue_poids(Objet * objet, const unsigned int value);

Objet * Objet_create(void); 

#endif //OBJET_H
