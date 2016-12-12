#ifndef FILE_IO_H_
#define FILE_IO_H_

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

/**
 * \struct PPM file_io.h
 * \brief La structure struct PPM permet de stocker les informations
 * d'entête pour le format PPM.
 **/
struct PPM{
	// PPM header
	char magic[2];	/*!< 2 bytes - 'P' '3' */
	int width;      /*!< 4 bytes : the image width */
	int height;		/*!< 4 bytes : the image height */
	int max;		/*!< 4 bytes : max value (less than 65536 and more than zero).*/
};

#endif /* FILE_IO_H_ */
