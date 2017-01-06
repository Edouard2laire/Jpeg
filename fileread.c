/*
 * fonctions.c
 *
 *  Created on: 22 déc. 2016
 *      Author: ensea
 */
#include "fileread.h"
#include <stdlib.h>
#include <stdio.h>


unsigned char fileRead(char nomDuFichier[NBLETTERS+1],int* p){
	FILE* fichier = NULL;
	int carac =0;
	int k =0;
	int nombre = 0;
	int* taboctet = NULL;
	if(fopen(nomDuFichier, "r")!= NULL){
		fichier = fopen(nomDuFichier, "r");
		taboctet = malloc(p * sizeof(int));
		while(carac!=EOF){
			for(k=1;k<=8;k++){
				carac = fgetc(fichier);
				nombre = nombre + carac*2^(8-k);
			}
			p=p+1;
			taboctet = realloc(taboctet, p * sizeof(int));
			if(taboctet){
				taboctet[p-1]=nombre;
			}
			else{
				exit(0);
			}
		}
	}
	else{
		fclose(fichier);
		printf("Le fichier est vide");
	}
	return (&taboctet);
}
