#ifndef COMMON_JPEG_H_
#define COMMON_JPEG_H_

#define BLOCK_SIZE_H 8
#define BLOCK_SIZE_W 8

#define Taille_IMG 64


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

void SubSampling_4_2_2 (JPEGDATA);
void SubSampling_4_4_0 (JPEGDATA);
void SubSampling_4_2_0 (JPEGDATA);

int isFileJPEGFormat (unsigned char*);

int shortToInt(int, int);
