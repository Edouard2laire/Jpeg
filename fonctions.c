/*
 * fonctions.c
 *
 *  Created on: 14 déc. 2016
 *      Author: ensea
 */

#include "common_jpeg.h"
#include "error.h"
#include "file_io.h"
#include "jpeg_8x8_block.h"
#include "jpeg_data_stream.h"
#include "jpeg_header_parser.h"


int intoYCbCr[3][3]={{0.257,-0.148,0.439},{0.504,-0.291,-0.368},{0.098,0.439,-0.071}};
int intoRGB[3][3]={{1,1,1},{0,-0.34414,1.772},{1.402,-0.71414,0}};

void RGBintoYCbCr (JPEGDATA img){
	int i; int j; int k;
	int R; int G; int B;
	for (i=0;i<=Taille_IMG;i++){
		for (j=0;j<=Taille_IMG;j++){
			for (k=0;k<=2;k++){
				R=img[i][j][0];
				G=img[i][j][1];
				B=img[i][j][2];
				if (k==0){
					img[i][j][k]=R*intoYCbCr[0][k]+G*intoYCbCr[1][k]+B*intoYCbCr[2][k]+16;
				}else{
					img[i][j][k]=R*intoYCbCr[0][k]+G*intoYCbCr[1][k]+B*intoYCbCr[2][k]+128;
				}
			}
		}
	}
}

void YCbCrintoRGB (JPEGDATA img){
	int i ; int j ; int k;
	int Y; int Cb; int Cr;
	for (i=0;i<=Taille_IMG;i++){
		for (j=0;j<=Taille_IMG;i++){
			for (k=0;k<=2;k++){
				Y=img[i][j][0];
				Cb=img[i][j][1];
				Cr=img[i][j][2];
				img[i][j][k]=(Y-16)*intoRGB[0][k]+(Cb-128)*intoRGB[1][k]+(Cr-128)*intoRGB[2][k];
				}
			}
		}
	}


void SubSampling_4_2_2 (JPEGDATA img){
	int i; int j;
	for (i=0;i<=Taille_IMG;i++){
		for (j=0;j<=Taille_IMG;i++){
			if (i%2==0){
				free(img[i][j]);
			}
		}
	}
}

void SubSampling_4_4_0 (JPEGDATA img){
	int i; int j;
	for (i=0;i<=Taille_IMG;i++){
		for (j=0;j<=Taille_IMG;i++){
			if (j%2==0){
				free(img[i][j]);
			}
		}
	}
}

void SubSampling_4_2_0 (JPEGDATA img){
	int i; int j;
	for (i=0;i<=Taille_IMG;i++){
		for (j=0;j<=Taille_IMG;i++){
			if ((j%2==0)||(i%2==0)){
				free(img[i][j]);
			}
		}
	}
}



int isFileJPEGFormat (unsigned char adresse){
	unsigned char adresseJPEG = 0xFFD8;
	int* K0= &(adresse),K1=&(adresse+1),K2= &(adresse+2),K3=&(adresse+3);
	int L0=*K0,L1=*K1,L2=*K2,L3=*K3;
	if ((L0==15)&(L1==15)&(L2==13)&(L3=8)){
		return 1;
	}else{
		return 0;
	}
}


int shortToInt(int LSB, int MSB){
	int* pk=&(LSB), pk1=&(MSB);
	int taille=pk-pk1;
	return taille;

}

void imagewritePPM(char fileName[NbLettres+1], int height, int width, TabINT* red, TabINT* green, TabINT* blue) {
	FILE* imagePPM = fopen(fileName,"w");
	if (imagePPM!=NULL) {
		fprintf(imagePPM,"P3 \n %d %d \n 255\n",width,height);
		int i=0;
		for (i=0;i<height*width<;i++) {
			if (i*height==0) {
				fprintf(imagePPM,"\n");
			}
			fprintf(imagePPM,"%d %d %d ",*red[i],*green[i],*blue[i]);
		}
		fclose(imagePPM);
	}
}
