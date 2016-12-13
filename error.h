#ifndef ERROR_H_
#define ERROR_H_

/**
 * \file error.h
 * \brief Contitent la définition des différents codes d'erreurs.
 */


/**
 * \define DEBUG
 * \brief 1 si Débug en cours, 0 sinon
 */
#define DEBUG 0

#define ERROR_MEMORY_ALLOCATION -1
#define ERROR_START_SECTION -2
#define ERROR_START_OF_FRAME_NOT_FOUND -3
#define ERROR_DHT -4
#define ERROR_SOI -5
#define ERROR_FILE_FORMAT -6
#define ERROR_DECODING -7

//A completer selon vos erreurs...

#endif /* ERROR_H_ */
