#ifndef JPEG_8x8_BLOCK_H_
#define JPEG_8x8_BLOCK_H_

/**
 * \file jpeg_8x8_block.h
   \brief On introduit ici les fonctions pour les blocks 8x8.  cf page 8.
    
 */
 
#include "common_jpeg.h"

static int ZigZagArray[64] =
{
    0,   1,   5,  6,   14,  15,  27,  28,
    2,   4,   7,  13,  16,  26,  29,  42,
    3,   8,  12,  17,  25,  30,  41,  43,
    9,   11, 18,  24,  31,  40,  44,  53,
    10,  19, 23,  32,  39,  45,  52,  54,
    20,  22, 33,  38,  46,  51,  55,  60,
    21,  34, 37,  47,  50,  56,  59,  61,
    35,  36, 48,  49,  57,  58,  62,  63,
};

/**
* \brief convertie une liste de 64 elem en un tableau 8x8
* \param tableau source, tableau dest
*/
void array1Dto2D( int[64], int[8][8]);
/**
* \brief convertie un tableau 8x8 en une liste de 64 elem
* \param tableau source, tableau dest
*/
void array2Dto1D( int[8][8], int[64]);

/**
* \brief Applique la quantification inverse en multipliant les blocs terme à terme. 
* F(u,v)*Q(u,v)= DCT(u,v) Attantion : la table de quantification sont au format zigZag.
* \param le bloc 8×8 (1D) et la table de quantification associée 8x8(1D) 
* \see array1Dto2D 
*/
void iQuantize( int[64], int[64]);

void deZigZag( int[64], int[64]);
float coeffC( int);
void iDCT8( int*);
void transposeBlock(int[8][8],int[8][8]);
void iDCT8x8( int[8][8], int[8][8]);
int boundValue( int, int, int);
void levelShift( int[8][8]);
void processBlock8x8( pJPEGDATA, int[8][8], int);

#endif /* JPEG_8x8_BLOCK_H_ */
