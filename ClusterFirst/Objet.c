#include "Objet.h"


void Objet_init(Objet * objet){
	objet->idObjet = 0;
	objet->coordx = 0; 
	objet->coordy = 0;
	objet->poids = 0;
}

void Objet_setvalue_idObjet(int value){
	objet->idObjet = value; 
}

void Objet_setvalue_coordx(int value){
	objet->coordx = value; 
}

void Objet_setvalue_coordy(int value){
	objet->coordy = value; 
}

void Objet_setvalue_poids(int value){
	objet->poids = value; 
}