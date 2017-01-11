#ifndef FILE_IO_H_
#define FILE_IO_H_

/**
 * \file file_io.h
 */
 
#include <stdio.h>
#include <stdlib.h>

#define Nblettres 100

typedef int TabINT[TAILLE];


/**
 * \struct PPM file_io.h
 * \brief La structure struct PPM permet de stocker les informations
 * d'entête pour le format PPM.
 **/
struct PPM{
	// PPM header
	char magic[2];	/*!< 2 bytes - JPEG = 0xFFD8 ; BMP= 0x424D ; PPM= "P3" .*/
	int width;      /*!< 4 bytes : the image width */
	int height;		/*!< 4 bytes : the image height */
	int max;		/*!< 4 bytes : max value (less than 65536 and more than zero).*/
};

void imagewritePPM(char fileName[NbLettres+1], int height, int width, TabINT* red, TabINT* blue, TabINT* green);
#endif /* FILE_IO_H_ */
