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

void Objet_setvalue_idObjet(int value);
void Objet_setvalue_coordx(int value);
void Objet_setvalue_coordy(int value);
void Objet_setvalue_poids(int value);


#endif //CLUSTERFIRST_H
