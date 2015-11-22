/******************************************************************************
 *
 * File Name: defs.h
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *
 *****************************************************************************/

 #ifndef defs_H
 #define defs_H

 #define NAME_SIZE 4

struct _entrance 
{ //struct for entrances
	char name[NAME_SIZE]; //name of the entrance
 	int xs;  //coordinates
 	int ys;
 	int zs;
};

typedef struct _entrance Entrance;

struct _access
{
	char name[NAME_SIZE]; //name of the access
 	int xs;  //coordinates
 	int ys;
 	int zs;
 	char type; //type of the access;
};

typedef struct _access Access;

struct _park 
{
 	int N; //number of columns
 	int M; //number of lines
 	int P; //number of floors
 	int E; //number of entrances
 	int S; //number of accesses
 	int ***matrix; //3D matrix that stores the info about each floor;
 	Entrance *entries; //vector that stores the info about the entrances;
 	Access *accesses; //vector that stores the info about the accesses;
};

typedef struct _park Park;

 #endif