#ifndef COMMON_JPEG_H_
#define COMMON_JPEG_H_

#define BLOCK_SIZE_H 8
#define BLOCK_SIZE_W 8

#define Taille_IMG 64

#define intoYCbCr {{0.257,-0.148,0.439},{0.504,-0.291,-0.368},{0.098,0.439,-0.071}}
#define intoRGB {{1,1,1},{0,-0.34414,1.772},{1.402,-0.71414,0}}

typedef struct jpegData {
	int image[Taille_IMG][Taille_IMG][3];
}JPEGDATA;

typedef struct jpegData* pJPEGDATA;

typedef struct pixel {
	int pixel[3];
}PIXEL;

typedef struct pixel* pPIXEL;

#endif /* COMMON_JPEG_H_ */

void YCbCrintoRGB (JPEGDATA);
void RGBintoYCbCr (JPEGDATA);
void SubSampling (JPEGDATA);
