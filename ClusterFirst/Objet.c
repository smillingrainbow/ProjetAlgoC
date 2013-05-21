#include "Objet.h"


void Objet_init(Objet * objet){
	objet->idObjet = 0;
	objet->coordx = 0; 
	objet->coordy = 0;
	objet->poids = 0;
	objet->trie = FALSE;
}

void Objet_setvalue_idObjet(Objet * objet, const unsigned int value){
	objet->idObjet = value; 
}

void Objet_setvalue_coordx(Objet * objet, const int value){
	objet->coordx = value; 
}

void Objet_setvalue_coordy(Objet * objet, const int value){
	objet->coordy = value; 
}

void Objet_setvalue_poids(Objet * objet, const unsigned int value){
	objet->poids = value; 
}



Objet * Objet_create(void){
	Objet * objet = (Objet *) malloc (sizeof(Objet));
	if (objet == NULL){
		printf("Erreur creation objet \n");
	    exit(1);
	}
	return objet;
}