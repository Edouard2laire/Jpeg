/*
 * jpeg_8x8_block.c
 *
 *  Created on: 18 janv. 2017
 *      Author: ensea
 */


#include "jpeg_8x8_block.h"
#include "math.h"

void iQuantize( int block[64], int tableq[64]){
	deZigZag(block,block);
	int i;
	for (i=0;i<=64;i++){
		block[i]=block[i]*tableq[i];
	}
}

float coeffC( int indice){
	if (indice==0){
		return Sqrt(2)/2;
	}else{
		return 1;
	}
}

void iDCT8( float* p){ //Pointeur sur le premier des 8 éléments constituant le tableau.
	int x;
	int u;
	float temp;
	float valpoint;
	for (x=0;x<8;x++){
		temp=0;
		for (u=0;u<8;u++){
			valpoint=*(p+u);
			temp+=(1/2)*coeffC(u)*valpoint*Cos(((2*x+1)*Pi()*u)/16);

		}
		*(p+x)=temp;
	}
}


void iDCT8x8( int block1[8][8], int block2[8][8]){
	int i;
	for (i=0;i<8;i++){
		block2[i]=iDCT8((&block1[0][0])+i*8);
	}
}

int boundValue( int min, int max, int valeur){
	if ((valeur<max)&(valeur>min)){
		return valeur;
	}else if (valeur<=min){
		return min;
	}else{
		return max;
	}
}
