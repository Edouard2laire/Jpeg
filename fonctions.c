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
