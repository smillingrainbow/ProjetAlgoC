#ifndef LISTEOBJET_H
#define LISTEOBJET_H
 
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "util.h"
#include "Objet.h"

typedef struct _ListeObjet
{
	struct _Objet * ptrO; 
	struct _ListeObjet * succ; 
} ListeObjet;

void ListeObjet_init(ListeObjet * liste); 
ListeObjet * ListeObjet_create(void); 

#endif //LISTEOBJET_H