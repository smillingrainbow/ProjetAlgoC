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

Objet ** creationTableauObjet(char * filename){
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
	return tabObjet; 
}


void remplissageCluster(const int cap_max, char * filename){ 
	int indice = 0; 
	int newCap =0; 
	ListeCluster * listeCluster = ListeCluster_create();
	ListeCluster * listeClusterTmp;
	Cluster * cluster;
	Cluster * clusterTmp;
	Objet * objet;
	Objet ** tabObjet = creationTableauObjet(filename);
	int nb_lignes = (int) sizeof(tabObjet);
	ListeCluster_init(listeCluster);

	while (indice <= nb_lignes){
		objet = tabObjet[indice]; 
		newCap = listeCluster->cap + objet->poids;
		while ((cap_max < newCap) || listeCluster != NULL){
			listeCluster = listeCluster->succ; 
		}

		if (listeCluster == NULL){
			listeClusterTmp = ListeCluster_create();
			listeCluster->succ = listeClusterTmp;
			ListeCluster_init(listeClusterTmp);
			listeClusterTmp->cap = objet->poids; 
			if (listeClusterTmp->cap = cap_max)
				listeClusterTmp->fini = TRUE;
			cluster = Cluster_create();
			listeClusterTmp->ptrC = cluster; 
			cluster->ptrO = objet;
			cluster->succ = NULL; 
		}
		else{
			clusterTmp = listeCluster->ptrC;
			while (clusterTmp->succ != NULL){
				clusterTmp = clusterTmp->succ;
			}
			cluster = Cluster_create(); 
			clusterTmp->succ = cluster;
			cluster->ptrO = objet;
			cluster->succ =  NULL;
			listeCluster->cap = newCap; 
			if (newCap = cap_max)
				listeCluster->fini =  TRUE;
		}
		indice ++; 
	}
}