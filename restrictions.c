/******************************************************************************
 *
 * File Name: restrictions.c
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *		reads the file with the information about the restrictions
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "restrictions.h"

#define DONTCARE 0
#define POSITION 0
#define FLOOR 1

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

 	 if (f == NULL) 
 	 {
  	  fprintf(stderr, "Error: Unable to open park-config file %s\n.", name);
  	  exit(1);
 	 }
 	 return f;
}

/******************************************************************************
 * NewRestrictions ()
 *
 * Arguments: 
 * Returns: Restrictions
 *
 * Description: Creates a new Restrictions structure
 *
 *****************************************************************************/

Restrictions *NewRestrictions(int rest_type, int ta, int tb, int x, int y, int z)
{
	Restrictions * rest;

	rest = (Restrictions *) malloc(sizeof(Restrictions)); //allocates memory for the struct

	if (rest == NULL)
	{
		fprintf(stderr, "Error in malloc of restrictions struct.\n");
		exit(1);
	}

	rest->type = type;
	rest->ta = ta;
	rest->tb = tb;
	rest->xs = x;
	rest->ys = y;
	rest->zs = z;

	return rest;
}

/******************************************************************************
 * ReadRestrictsFile ()
 *
 * Arguments: file
 * Returns: Restrictions
 *
 * Description: Reads the file with the restrictions
 *
 *****************************************************************************/

void ReadRestrictsFile(char * file, LinkedList * restrictionslist)
{
	int ta, tb, ind, ex, ey, ez, nr_reads, nr_floors = 0, nr_pos = 0, i = 0, j = 0;
	char r;
	Restrictions * aux;

	FILE * f;

	f = AbreFicheiro(file, "r");

	while(nr_reads = fscanf(f, "%s %d %d %d %d %d", &r, &ta, &tb, &ind, &ey, &ez)) // Reads each line of the file
	{
		if(nr_reads == 4) // Its a floor restriction - use type = 1
		{	
			aux = NewRestrictions(FLOOR, ta, tb, DONTCARE, DONTCARE, ez);
			restrictionslist = insertUnsortedLinkedList(restrictionslist, (Item) aux); // Inserts new floor restriction in restriction list
 		
		}
		else if(nr_reads == 6) // Its a position restriction - use type = 0
		{
			aux = NewRestrictions(POSITION, ta, tb, ex, ey, ez);
			restrictionslist = insertUnsortedLinkedList(restrictionslist, (Item) aux); // Inserts new position restriction in restriction list
		}

		else if(nr_reads != 4 || nr_reads != 6)
		{
			break;
		}
	}

	fclose(f);
}