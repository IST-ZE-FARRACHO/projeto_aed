/******************************************************************************
 *
 * File Name: liberation.c
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *		reads the file with the information about the restrictions
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "liberation.h"
 

/******************************************************************************
 * LiberationStructCreator
 *
 * Arguments: Liberation coordinates
 *
 * Returns: Created liberation structure
 *
 * Description: Allocates and fills an liberation structure
 *
 *****************************************************************************/

Liberation * NewLiberation(int x, int y, int z, int time)
{
	Liberation * libert;

	libert = (Liberation *) malloc(sizeof(Liberation)); /*allocates memory for the struct*/

	if (libert == NULL)
	{
		fprintf(stderr, "Error in malloc of liberation struct.\n");
		exit(0);
	}

	libert->pos = (Position*) malloc(sizeof(Position));

 	if(libert->pos == NULL)
 	{
 		fprintf(stderr, "Error in malloc of entries/accesses.\n");
 		exit(0);
 	}

	libert->time = time;
	libert->pos->x = x;
	libert->pos->y = y;
	libert->pos->z = z;

	return libert;

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

LinkedList * ReadLiberationFile(char * file, LinkedList * liberationlist)
{	

	 int n, tmpta, tmpxs, tmpys, tmpzs;
	 char tmptype;
	 char tmpid[5];
	 Liberation * newliberation;

	FILE * f;

	f = AbreFicheiro(file, "r");

	do{	
 		
 		n = fscanf(f, "%s   %d %c %d %d %d", tmpid, &tmpta, &tmptype, &tmpxs, &tmpys, &tmpzs); /*Reads each line*/
 		if( n < 3 ) break;

		if(tmptype == 'S') /*If it is not exit info (it is an entrance)*/
 			{	

 				if(n > 3) 
 				{
 						newliberation = NewLiberation(tmpxs, tmpys, tmpzs, tmpta); /*Creates a new struct to save liberation info*/
 						liberationlist = insertUnsortedLinkedList(liberationlist, (Item) newliberation); /*Inserts new liberation in liberation list*/			
 				}

 			}

 		}while(n >= 3);

	fclose(f);

	return liberationlist;
}