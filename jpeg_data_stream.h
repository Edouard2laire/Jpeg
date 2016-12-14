#ifndef JPEG_DATA_STREAM_H_
#define JPEG_DATA_STREAM_H_

#include "common_jpeg.h"
#include "jpeg_header_parser.h"
#include "error.h"

#if DEBUG
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#endif

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

union Buffer {
	unsigned int global;
	unsigned char byte[4];
};

typedef struct queue {
	union Buffer buffer;
	char bitshift;
	unsigned char* source;
} QUEUE;
typedef QUEUE* pQUEUE;

pQUEUE newQueue( unsigned char*);
void updateQueue( pQUEUE, char);
int readNewWord( pQUEUE, pDHT);
int decode8x8(pQUEUE, pDHT, pDHT);
unsigned char* retrieveRawdata (unsigned char *, int*);
void upSampler(pJPEGDATA, int *, unsigned char *);
unsigned char** decodeMCU(pJPEGDATA, int* , int*);
void copyMCUtoImage (pJPEGDATA, unsigned char**, int, int);
int processRawdata(pJPEGDATA);

#endif /* JPEG_DATA_STREAM_H_ */
