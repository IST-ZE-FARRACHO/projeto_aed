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

Restrictions *NewRestrictions(int rest_pos, int rest_floors)
{
	Restrictions * rest;

	rest = (Restrictions *) malloc(sizeof(Restrictions)); //allocates memory for the struct

	if (rest == ((Restrictions *) NULL))
	{
		fprintf(stderr, "Error in malloc of restrictions.\n");
		exit(1);
	}

	rest->restricted_floors = malloc(rest_floors*sizeof(*rest->restricted_floors));  //use p->restricted_floors[i].ta

 	rest->restricted_positions = malloc(rest_pos*sizeof(*rest->restricted_positions));	

 	if (rest->restricted_floors == ((Rest_floor *) NULL) || rest->restricted_positions == ((Rest_pos *) NULL))
 	{
 		fprintf(stderr, "Error in malloc of restriction vectors.\n");
 		exit(1);
 	}

 	return (rest);
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

void ReadRestrictsFile(Restrictions * rest, char * file)
{
	int ta, tb, ind, ex, ey, ez, nr_reads, nr_floors = 0, nr_pos = 0, i = 0, j = 0;
	char r;

	FILE * f;

	f = AbreFicheiro(file, "r");

	while(nr_reads = fscanf(f, "%s %d %d %d %d %d", &r, &ta, &tb, &ind, &ey, &ez))
	{
		if(nr_reads == 4)
		{
			nr_floors++;
		}
		else if(nr_reads == 6)
		{
			nr_pos++;
		}

		else if(nr_reads != 4 || nr_reads != 6)
		{
			break;
		}
	}

	fclose(f);

	rest = NewRestrictions(nr_pos, nr_floors);

	f = AbreFicheiro(file, "r");


	while(nr_reads = fscanf(f, "%s %d %d %d %d %d", &r, &ta, &tb, &ind, &ey, &ez))
	{
		if(nr_reads == 4)
		{
			rest->restricted_floors[i].ta = ta;
			rest->restricted_floors[i].tb = tb;
			rest->restricted_floors[i].px = ind;
			i++;
		}
		else if(nr_reads == 6)
		{
			rest->restricted_positions[j].ta = ta;
			rest->restricted_positions[j].tb = tb;
			rest->restricted_positions[j].ex = ind;
			rest->restricted_positions[j].ey = ey;
			rest->restricted_positions[j].ez = ez;
			j++;
		}

		else if(nr_reads != 4 || nr_reads != 6)
		{
			break;
		}
	}
	fclose(f);
}


/**********main para testes************************************/

int main(int argc, char **argv)
{
	Restrictions * rest;

	ReadRestrictsFile(rest, argv[1]);

	printf("%d\n %d\n", rest->restricted_positions[1].ta, rest->restricted_floors[0].px);

	return 0;
}