/*
 * sans titre.c
 * 
 * Copyright 2013 rainbow <rainbow@rainbow>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <stdio.h>
#include "RootFirst.h"
#include "ListeObjet.h"
#include "Objet.h"
#include "util.h"
#include "ListeCluster.h"

void init(int argc, char ** argv, char ** filename, unsigned int * cap_max){
	if(argc > 2){
		*filename = argv[2];
		*cap_max = strtod(argv[1], NULL);
	}
	else{
		printf("veuillez préciser le nom du fichier à lire et la capacite max du chariot \n\t %s <capacite max> <nom du fichier>\n", argv[0]);
		exit(1);
	}
}

int main(int argc, char **argv)
{
	char * filename;
	unsigned int cap_max;
	ListeObjet * listeObjet; 
#ifndef NDEBUG
	printf("Lancement du main \n");
#endif
	init(argc, argv, &filename, &cap_max);

	listeObjet = trieTabObjet(filename, cap_max);
	creationListeCluster(listeObjet, cap_max);

	return 0;
	
}

