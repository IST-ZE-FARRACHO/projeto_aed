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
#include <string.h>
#include "tools.h"

 FILE *AbreFicheiro(char *name, char *mode)
{
  	FILE *f;

 	 f = fopen(name, mode);

 	 if (f == NULL) 
 	 {
  	  fprintf(stderr, "Error: Unable to open park-config file %s\n.", name);
  	  exit(0);
 	 }
 	 return f;
}

void FechaFicheiro(FILE * f)
{
	fclose(f);
}

/******************************************************************************
 * ListCreator
 *
 * Arguments: 
 *
 * Returns: Abstractly created list
 *
 * Description: Creates an abstract list
 *
 *****************************************************************************/

LinkedList * ListCreator()
{
	LinkedList * abstractlist;

	abstractlist = (LinkedList*) malloc(sizeof(LinkedList));



	if (abstractlist == NULL) 
	{
		fprintf(stderr, "Error in malloc of new LinkedList.\n");
		exit(0);
	}

	return abstractlist;	

}


int Get_Pos(int x, int y, int z, int columns, int lines)
{
	return (x + y*columns + columns*lines*z);
}

void exch(int *i, int *j)
{
  int temp;

  temp = *i;
  *i = *j;
  *j = temp;
}
