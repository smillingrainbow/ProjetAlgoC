#ifndef CLUSTERFIRST_H
#define CLUSTERFIRST_H

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


#endif //CLUSTERFIRST_H
