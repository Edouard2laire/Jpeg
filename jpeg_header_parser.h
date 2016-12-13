#ifndef JPEG_HEADER_PARSER_H_
#define JPEG_HEADER_PARSER_H_

#include "common_jpeg.h"
/**
 * \file Jpeg_header_parser
 * \brief Contient l'ensemble de fonctions/structure pour le parsage des header JPEG
 * \see "common_jepeg.h"
 */
/**
 * \define MARKER_SOF
 * \brief Start Of Frame :Identifie le début d'une section pour l'encodage d'Huffman : baseline  0xFF 0xC0
 *  Offset dans la section | Taille en octet | Description
 *  --------------------------------------------------------
 *  0x00 | 2 | Marqueur SOF pour identifier la section(0xFFC0 )
 *  0x02 | 2 | Taille de la section sans le marqueur, mais les 2 octets de taille sont compris
 *  0x04 | 1 | Précision en bits par composante
 *  0x05 | 2 | Hauteur en pixels de l’image
 *  0x07 | 2 | Largeur en pixels de l’image
 *  0x09 | 1 | Nombre de composantes N(3 pour YCbCR, 1 pour une image en niveau de gris )
 *  0x0A | 3N| Information pour chaque composante 1 octet : indice de composante ; b7,b6,b5,b4 facteur d’échant. horizontal; b3,b2,b1,b0 facteur d'échant vetical; 1 octet : table de quantification associé
 *
 */
#define MARKER_SOF 0xC0
#define MARKER_DHT 0xC4
#define MARKER_SOS 0xDA
#define MARKER_DQT 0xDB
#define MARKER_SOI 0xD8
#define MARKER_EOI 0xD9
#define MARKER_COM 0xFE

/**
 * \struct Component parserHeader.h
 * \brief La structure struct Component (COMPONENT) permet de stocker les informations
 * relatives à une composante (Y, Cb ou Cr). Dans le cas où il y a 3 composantes, il y
 * aura 3 structures.
 **/
struct Component{
	int id;		/*!< identifiant de la composante (généralement 1 pour Y, 2 pour Cb, 3 pour Cr) (à lire dans SOF) */
	int idDC;	/*!< identifiant pour la table de codage Huffman pour la valeur DC (à lire dans SOS) */
	int idAC;	/*!< identifiant pour la table de codage Huffman pour la valeur AC (à lire dans SOS) */
	int previousDC;	/*!< initialiser à 0 pendant la lecture de SOF */
	int horizontal_sample_factor;	/*!< facteur de sous-echantillonnage de la composante (1 pour Y, 1 ou 2 pour Cb/Cr) */
	int vertical_sample_factor;	/*!< facteur de sous-echantillonnage de la composante (1 pour Y, 1 ou 2 pour Cb/Cr) */
	int idQ;	/*!< identifiant de la table de quantification pour cette composante (à lire dans SOF) */
};

/**
 * \struct StartOfFrame parserHeader.h
 * \brief La structure struct StartOfFrame (SOF) permet de stocker les informations lues dans la section SOF.
**/
struct StartOfFrame{
	int precision;		/*!< precision en bits par composante (8 ou 16 bits) */
	int height;			/*!< hauteur de l'image */
	int width;			/*!< largeur de l'image */
	int extendedheight;	/*!< hauteur de l'image multiple de la hauteur d'une MCU supérieure ou égale à height
						 * (format 444 : HAUTEURmcu = 8, format 422 H : HAUTEURmcu = 8,
						 * format 422 V : HAUTEURmcu = 16, format 420 : HAUTEURmcu = 16) */
	int extendedwidth;	/*!< largeur de l'image multiple de la largeur d'une MCU supérieure ou égale à width
						 * (format 444 : LARGEURmcu = 8, format 422 H : LARGEURmcu = 16,
						 * format 422 V : LARGEURmcu = 8, format 420 : LARGEURmcu = 16) */
	int Vupfactor;		/*!< facteur de sous-échantillonnage vertical (à calculer pendant la lecture de SOF) */
	int Hupfactor;		/*!< facteur de sous-échantillonnage horizontal (à calculer pendant la lecture de SOF) */
	int nbComponents;	/*!< nombre de composantes (1 ou 3) */
	struct Component* components; 	/*!< tableau des composantes, à allouer dynamiquement pendant la lecture de SOF
									 * et la détermination de nbComponents. Une fois allouée(s), il faut penser à
									 * remplir les champs de chaque composante. */
};

/**
 * \struct DefineQuantificationTable parserHeader.h
 * \brief Une structure struct DefineQuantificationTable (SQT) permet de stocker les informations lues dans une
 * section DQT. Il faut donc en définir plusieurs pour stocker les différentes sections DQT.
**/
struct DefineQuantificationTable{
	int id;			/*!< identifiant de la table de quantification (à associer avec idQ de chaque composante) */
	int precision;	/*!< precision 8 ou 16 bits */
	int qtable[64];	/*!< 64 octets ranges en zigzag ayant permis la quantification (division terme à terme) et
					 *	à utiliser en tant que coefficients multiplicatifs (quantification inverse) */
	struct DefineQuantificationTable* nextdqt; 	/*!< pointeur sur la structure DQT suivante (liste chainee, car
												 * on ne connait pas par avance le nombre de sections DQT.
												 * L'insertion de chaque DQT se fait en tete pour simplifier
												 * l'opération. Il faudra mettre à jour le champ tetelistedqt
												 * de la structure JPEGDATA à chaque insertion. */
};

/**
 * \struct HuffmanCode parserHeader.h
 * \brief Une structure struct HuffmanCode (HCODE) permet de stocker les informations relatives à un code.
**/
struct HuffmanCode{
	int value;		/*!< valeur/symbole */
	int nbbits;		/*!< nombre de bits du code */
	int code16;		/*!< code de Huffman */
};

/**
 * \struct DefineHuffmanTable parserHeader.h
 * \brief Une structure struct DefineHuffmanCode (DHT) permet de stocker les informations lues dans une
 * section DHT. Il faut donc en définir plusieurs pour stocker les différentes sections DHT.
**/
struct DefineHuffmanTable{
	int id;			/*!< identifiant de la table de codage d'Huffman (à associer avec idDC ou idAC selon le type) */
	int type;		/*!< type de valeurs sur lequel cette table s'applique (0 DC, 1 AC) */
	int nbSymbols[16]; /*!< tableau contenant le nombre de codes par longueur de bits (indice 0 du tableau = longueur 1 bit) */
	int countSymbols;	/*!< nombre total de symboles (doit être inferieur à 256) */
	struct HuffmanCode* codes; 	/*!< tableau de structures de struct HuffmanCode alloué au moment de la lecture de DHT avec
								 * countSymbols. Il faut penser à remplir les champs de chaque code : la connaissance du
								 * nombre de symboles par longueur de code et la lecture des valeurs/symboles qui suivent
								 * permettent de remplir les 2 champs de chaque code. La fonction buildHuffmanCodes remplit
								 * le champ code16. */
	struct DefineHuffmanTable* nextdht; /*!< pointeur sur la structure DHT suivante (liste chainee, car on ne connait pas
										 * par avance le nombre de sections DHT. L'insertion de chaque DHT se fait en tete
										 * pour simplifier l'opération. Il faudra mettre à jour le champ tetelistedht de
										 * la structure JPEGDATA à chaque insertion. */
};

/**
 * \struct jpegData parserHeader.h
 * \brief La structure jpegData (JPEGDATA) contient les informations relatives aux différentes sections. Elle contient
 * également les octets à décoder, les composantes RGB décodées.
**/
struct jpegData{
	struct StartOfFrame *psof;		/*!< pointeur sur la structure SOF de l'image */
	struct DefineQuantificationTable* tetelistedqt; /*!< pointeur sur la liste chainee des DQT */
	struct DefineHuffmanTable* tetelistedht; /*!< pointeur sur la liste chainee des DHT */
	unsigned char *encodedData;		/*!< flux binaire compressé à décoder */
	int nbpixels;					/*!< nombre de pixels */
	unsigned char **decodedPixels; 	/*!< composantes YCrCb décodées dans un premier temps, puis convertis en RGB à la fin
									 * d'une image de la taille de extendedwidth et extendedheight. */
};

typedef struct Component COMPONENT;
typedef struct Component* pCOMPONENT;
typedef struct StartOfFrame SOF;
typedef struct StartOfFrame* pSOF;
typedef struct DefineQuantificationTable DQT;
typedef struct DefineQuantificationTable* pDQT;
typedef struct HuffmanCode HCODE;
typedef struct HuffmanCode* pHCODE;
typedef struct DefineHuffmanTable DHT;
typedef struct DefineHuffmanTable* pDHT;

/**
 * \brief Teste si le nombre magique du fichier est bon (Pour JPEG : 0xFFD8 )
 * \see JPEG_MAGIC
 * \return 1 si le fichier est valide, 0 sinon.
 */
int isFileJPEGFormat(unsigned char*);


int shortToInt(unsigned char*);
int parsingHeader(unsigned char*, pJPEGDATA);
int parsingSOF(unsigned char*,pJPEGDATA);
int parsingDQT(unsigned char*, pJPEGDATA);
int parsingSOS(unsigned char*,pJPEGDATA);
int buildHuffmanCodes(pDHT,unsigned char*,int,int);
int parsingDHT(unsigned char*, pJPEGDATA);

#endif /* JPEG_HEADER_PARSER_H_ */
