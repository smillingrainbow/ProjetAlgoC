#include "ClusterFirst.h"

FILE * open_Fichier(char *filename){
	FILE * file; 
	file = fopen(filename, "rt"); // ouvrir en lecture
  	if(file == NULL){
	    printf("Impossible d'ouvrir le fichier %s\n", filename);
	    exit(1);
	}
	return file; 
}

void close_Fichier(FILE * file, char * filename){
	if(fclose(file) == EOF){
	    printf("Probleme de fermeture du fichier %s", filename);
	    exit(1);
  }
}

void creationTableauObjet(char * filename){
	int indice, nb_lignes, idObjet, coordx, coordy, poids; 
	Objet ** tabObjet;
	FILE * file = open_Fichier(filename);
	fscanf(file, "%d", &nb_lignes);
	tabObjet = (Objet **) malloc (sizeof(Objet *) * nb_lignes);
	
	for (indice = 0; indice <= nb_lignes; indice++){
		fscanf(file, "%d %d %d %d", &idObjet, &coordx, &coordy, &poids);
		Objet *  objet = Objet_create(); 
		Objet_setvalue_idObjet(objet, idObjet);
		Objet_setvalue_coordx(objet, coordx);
		Objet_setvalue_coordy(objet, coordy);
		Objet_setvalue_poids(objet, poids);
		tabObjet[indice] = objet; 
	}

	close_Fichier(file, filename); 

}


void remplissageCluster(Objet ** tabObjet){

}