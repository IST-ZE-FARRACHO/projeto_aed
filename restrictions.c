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
 * NewRestrictions ()
 *
 * Arguments: 
 * Returns: Restrictions
 *
 * Description: Creates a new Restrictions structure
 *
 *****************************************************************************/

Restrictions *NewRestrictions(int rest_type, int ta, char inout, int x, int y, int z)
{
	Restrictions * rest;

	rest = (Restrictions *) malloc(sizeof(Restrictions)); /*allocates memory for the struct*/

	if (rest == NULL)
	{
		fprintf(stderr, "Error in malloc of restrictions struct.\n");
		exit(0);
	}

	rest->pos = (Position*) malloc(sizeof(Position));

 	if(rest->pos == NULL)
 	{
 		fprintf(stderr, "Error in malloc of rest->pos.\n");
 		exit(0);
 	}


	rest->type = rest_type;
	rest->ta = ta;
	rest->inout = inout;
	rest->pos->x = x;
	rest->pos->y = y;
	rest->pos->z = z;

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
LinkedList * ReadRestrictsFile(char * file, LinkedList * restrictionslist)
{
	int ta, tb, ind, ex, ey, ez, nr_reads;
	char r;
	Restrictions * aux;

	FILE * f;

	f = AbreFicheiro(file, "r");

	while((nr_reads = fscanf(f, "%s %d %d %d %d %d", &r, &ta, &tb, &ind, &ey, &ez))) /*Reads each line of the file*/
	{
		if(nr_reads == 4) /*Its a floor restriction - use type = 1*/
		{	
			aux = NewRestrictions(FLOOR, ta, 'E', DONTCARE, DONTCARE, ez);
			restrictionslist = insertUnsortedLinkedList(restrictionslist, (Item) aux); /*Inserts new floor restriction in restriction list*/
			aux = NewRestrictions(FLOOR, tb, 'S', DONTCARE, DONTCARE, ez);
			restrictionslist = insertUnsortedLinkedList(restrictionslist, (Item) aux); /*Inserts new floor restriction in restriction list*/

 		
		}
		else if(nr_reads == 6) /*Its a position restriction - use type = 0*/
		{
			aux = NewRestrictions(POSITION, ta, 'E', ex, ey, ez); /*Inserts restriction entrance time with ta and 'E'*/
			restrictionslist = insertUnsortedLinkedList(restrictionslist, (Item) aux); /*Inserts new position restriction in restriction list*/
			aux = NewRestrictions(POSITION, tb, 'S', ex, ey, ez); /*Inserts restriction lift time with tb and 'S'*/
			restrictionslist = insertUnsortedLinkedList(restrictionslist, (Item) aux); /*Inserts new position restriction in restriction list*/

		}

		else if(nr_reads != 4 || nr_reads != 6)
		{
			break;
		}
	}

	fclose(f);

	return restrictionslist;
}