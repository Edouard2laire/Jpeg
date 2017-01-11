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


void RGBintoYCbCr (pJPEGDATA img){

}

void imagewritePPM(char fileName[NbLettres+1], int height, int width, TabINT* red, TabINT* green, TabINT* blue) {
	FILE* imagePPM = fopen(fileName,"w");
	if (imagePPM!=NULL) {
		fprintf(imagePPM,"P3 \n %d %d \n 255\n",width,height);
		int i=0;
		for (i=0;i<height*width<;i++) {
			int j=0;
			for (j=0;j<width;j++) {
				fprintf(imagePPM,"%d\n %d\n %d\n",*red[i],*green[i],*blue[i]);
			}
		}
		fclose(imagePPM);
	}
}
