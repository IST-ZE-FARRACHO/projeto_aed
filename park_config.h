/******************************************************************************
 *
 * File Name: park_config.h
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *
 *****************************************************************************/

 typedef struct _park Park;

 Park *NewPark(int columns, int lines, int entrances, int accesses, int floors);

 FILE *AbreFicheiro(char *name, char *mode);

 void AlocaMatrizPark(Park * p)