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


 struct _park {
 	int N; //number of columns
 	int M; //number of lines
 	int P; //number of floors
 	int E; //number of entrances
 	int S; //number of accesses
 	int ***matrix; //3D matrix that stores the info about each floor;
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
	int i, j;

 	p->matrix = (int ***) malloc((p->N)*sizeof(int **));  //allocates z coordinates of the matrix

 	if(p->matrix == NULL){
 		printf("Error in malloc of matrix.\n");
 		exit(1);
 	}

  	for (i = 0; i < p->N; i++) {  

    	p->matrix[i] = (int **) malloc((p->M)*sizeof(int *)); //allocates x coordinates

    	if(p->matrix[i] == NULL){
 			printf("Error in malloc of matrix.\n");
 			exit(1);
 		}

    	for (j = 0; j < p->M; j++){
     		p->matrix[i][j] = (int*) malloc((p->P)*sizeof(int)); //allocates y coordinates

     		if(p->matrix[i][j] == NULL){
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

Park *NewPark(int columns, int lines, int entrances, int accesses, int floors){
	Park *p;

	p = (Park *) malloc(sizeof(Park)); //allocates memory for the struct

	if (p == ((Park *) NULL)) {
		fprintf(stderr, "Error in malloc of park.\n", );
		exit(1);
	}

	p->N = columns;
	p->M = lines;
	p->P = floors;
	p->E = entrances;
	p->S = accesses;

	AlocaMatrizPark(p);

	return (p);
}



