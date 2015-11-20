/******************************************************************************
 *
 * File Name: park_config.c
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *		reads the file with the configuration of the parking lot
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "park_config.h"

struct _entrance { //struct for entrances
	char *name; //name of the entrance
 	int xs;  //coordinates
 	int ys;
 	int zs;
};

struct _access {
	char *name; //name of the access
 	int xs;  //coordinates
 	int ys;
 	int zs;
 	char type; //type of the access;
};

struct _park {
 	int N; //number of columns
 	int M; //number of lines
 	int P; //number of floors
 	int E; //number of entrances
 	int S; //number of accesses
 	int ***matrix; //3D matrix that stores the info about each floor;
 	Entrance *entries; //vector that stores the info about the entrances;
 	Access *accesses; //vector that stores the info about the accesses;
};


/******************************************************************************
 * AbreFicheiro ()
 *
 * Arguments: nome - pointer to string containing name of file to open
 *            mode - mode to use to open the file
 * Returns: FILE * - handle to file opened
 * Side-Effects: input file is opened
 *
 * Description: Open file for reading, returns handle
 *
 *****************************************************************************/

FILE *AbreFicheiro(char *name, char *mode)
{
  	FILE *f;

 	 f = fopen(name, mode);

 	 if (f == NULL) {
  	  fprintf(stderr, "Error: Unable to open file %s\n.", name);
  	  exit(1);
 	 }
 	 return f;
}


/******************************************************************************
 * AlocaMatrizPark ()
 *
 * Arguments: p - structure of the park 
 * Side-Effects: matrix is allocated;
 *
 * Description: allocates the memory for the 3D matrix;
 *
 *****************************************************************************/

void AlocaMatrizPark(Park * p)
{
	int y, z;

 	p->matrix = (int ***) malloc((p->N)*sizeof(int **));  //allocates x coordinates of the matrix

 	if(p->matrix == NULL){
 		printf("Error in malloc of matrix.\n");
 		exit(1);
 	}

  	for (y = 0; y < p->N; y++) {  

    	p->matrix[y] = (int **) malloc((p->M)*sizeof(int *)); //allocates y coordinates

    	if(p->matrix[y] == NULL){
 			printf("Error in malloc of matrix.\n");
 			exit(1);
 		}

    	for (z = 0; z < p->M; z++){
     		p->matrix[y][z] = (int *) malloc((p->P)*sizeof(int)); //allocates z coordinates

     		if(p->matrix[y][z] == NULL){
 				printf("Error in malloc of matrix.\n");
 				exit(1);
 			}
    	}
  	}
}

/******************************************************************************
 * NewPark ()
 *
 * Arguments: columns- number of columns
 *            lines - number of lines
 *			  entrances - number of entrances
 *            accesses - number of accesses
 * Returns: Park
 *
 * Description: Creates a new Park structure
 *
 *****************************************************************************/

Park *NewPark(int columns, int lines, int entrances, int nr_accesses, int floors)
{
	Park *p;

	p = (Park *) malloc(sizeof(Park)); //allocates memory for the struct

	if (p == ((Park *) NULL)) {
		fprintf(stderr, "Error in malloc of park.\n");
		exit(1);
	}

	p->N = columns;
	p->M = lines;
	p->P = floors;
	p->E = entrances;
	p->S = nr_accesses;

	AlocaMatrizPark(p);

	p->entries = malloc(entrances*sizeof(*p->entries));  //use p->entries[i].xs

 	p->accesses = malloc(nr_accesses*sizeof(*p->accesses));

	return (p);
}



//-------------------------------------------------------------------------------------------------------
//main para testes:
int main(){

	Park *p;

	p = NewPark(3, 4, 2, 3, 2);

	p->entries[2].name = "E1";

	printf("%s\n", p->entries[2].name);

	return 0;
}


