/******************************************************************************
 *
 * File Name: park_config.h
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *
 *****************************************************************************/

 #ifndef park_config_H
 #define park_config_H

 typedef struct _entrance Entrance;

 typedef struct _access Access;

 typedef struct _park Park;

 FILE *AbreFicheiro(char *name, char *mode);

 void AlocaMatrizPark(Park * p);

 Park *NewPark(int columns, int lines, int entrances, int nr_accesses, int floors);

 int Char_to_Number (char * c);

 void Map_to_matrix (Park * p, FILE * f, int line, int column, int _floor);

 void Read_Doors_info (Park * p, FILE * f, int *i, int *j);

 void Read_floor (Park * p, FILE * f, int _floor, int *i, int *j);

 Park *ReadFilePark (char * file);

 #endif
