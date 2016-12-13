#ifndef COMMON_JPEG_H_
#define COMMON_JPEG_H_

/**
 * \file common_jpeg.h
 */
 
#define BLOCK_SIZE_H 8
#define BLOCK_SIZE_W 8

/**
 * \DEFINE JPEG_MAGIC
 * \brief Contient la valeur du nombre magique permantant d'identifier un fichier JPEG
 */
#define JPEG_MAGIC 0xFFD8

typedef struct jpegData JPEGDATA;
typedef struct jpegData* pJPEGDATA;

#endif /* COMMON_JPEG_H_ */
