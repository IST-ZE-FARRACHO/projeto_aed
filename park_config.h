/******************************************************************************
 *
 * File Name: park_config.h
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *
 *****************************************************************************/

 typedef struct _entrance Entrance;

 typedef struct _access Access;

 typedef struct _park Park;

 FILE *AbreFicheiro(char *name, char *mode);

 void AlocaMatrizPark(Park * p);

 Park *NewPark(int columns, int lines, int entrances, int nr_accesses, int floors);
