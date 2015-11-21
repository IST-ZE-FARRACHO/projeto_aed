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
#include "park_config.h"
#include "defs.h"

/*******************Defines**************************/
#define road 0
#define wall 1
#define entry_door 2
#define ped_access 3
#define empty_spot 4
#define occupied 5
#define ramp_up 6
#define ramp_down 7
/****************************************************/

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

 	if(p->matrix == NULL)
 	{
 		printf("Error in malloc of matrix.\n");
 		exit(1);
 	}

  	for (y = 0; y < p->N; y++) 
  	{  
    	p->matrix[y] = (int **) malloc((p->M)*sizeof(int *)); //allocates y coordinates

    	if(p->matrix[y] == NULL)
    	{
 			printf("Error in malloc of matrix.\n");
 			exit(1);
 		}

    	for (z = 0; z < p->M; z++)
    	{
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

	if (p == ((Park *) NULL))
	{
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

/******************************************************************************
 * Char_to_Number ()
 *
 * Arguments: character to transform
 * Returns: integer
 *
 * Description: Transforms a character from the map to the equivalent integer
 *
 *****************************************************************************/

int Char_to_Number (char * c)
{
	if(strcmp(c, " ") == 0)
	{
		return road;
	}

	if(strcmp(c, "@") == 0)
	{
		return wall;
	}

	if(strcmp(c, "a") == 0)
	{
		return ped_access;
	}

	if(strcmp(c, ".") == 0)
	{
		return empty_spot;
	}

	if(strcmp(c, "x") == 0)
	{
		return occupied;
	}

	if(strcmp(c, "u") == 0)
	{
		return ramp_up;
	}

	if(strcmp(c, "d") == 0)
	{
		return ramp_down;
	}

	else
	{
		printf("\nMap file is poorly built!\n");
		exit(1);
	}
}

/******************************************************************************
 * Map_to_matrix ()
 *
 * Arguments: File to read
 *            Struct of park
 *			  Line, column, _floor
 * Returns: ----
 *
 * Description: Reads the map and inserts in matrix
 *
 *****************************************************************************/

void Map_to_matrix (Park * p, FILE * f, int line, int column, int _floor) 
{
	char c;

	fscanf(f, "%c", &c);

	p->matrix[column][line][_floor] = Char_to_Number(c);
}

/******************************************************************************
 * Read_Doors_info ()
 *
 * Arguments: File to read
 *            Struct of park
 *			  i, j
 * Returns: ----
 *
 * Description: Reads the info about the entries and accesses
 *
 *****************************************************************************/

void Read_Doors_info (Park * p, FILE * f, int *i, int *j) //i, j, declare where to start inserting entries or accesses in the vectors
{
	int door_x, door_y, door_z;
	char door_name[4], door_type; 

	while(fscanf(f, "%s %d %d %d %c", door_name, door_x, door_y, door_z, door_type)) //reads line
	{
		if (door_name[0] == 'E')
		{
			strcpy(p->entries[(*i)].name, door_name);
			p->entries[(*i)].xs = door_x;
			p->entries[(*i)].ys = door_y;
			p->entries[(*i)].zs = door_z;
			(*i)++;
		}

		else if (door_name[0] == 'A')
		{
			strcpy(p->accesses[(*j)].name, door_name);
			p->accesses[(*j)].xs = door_x;
			p->accesses[(*j)].ys = door_y;
			p->accesses[(*j)].zs = door_z;
			(*j)++;
		}

		else
		{
			printf("Invalid door information in park file!\n");
		}

		if(strcmp(door_name, "+") == 0)
		{
			break;
		}
	}
}

/******************************************************************************
 * Read_floor()
 *
 * Arguments: File to read
 *            Struct of park
 *			  _floor
 *			  i, j;
 * Returns: ----
 *
 * Description: Reads the info about each floor and inserts in the structs
 *
 *****************************************************************************/

void Read_floor (Park * p, FILE * f, int _floor, int *i, int *j) //i, j indicates the position to insert the entries/accesses in the vectors
{
	int x, y;

	for(y = 0; y < p->M; y++)
		for(x = 0; x < p->N; x++)
		{
			Map_to_matrix(p, f, y, x, _floor);
		}

	Read_Doors_info(p, f, (*i), (*j));
}

/******************************************************************************
 * ReadFilePark ()
 *
 * Arguments: File to read
 *			  Structure of the park
 * Returns: Park
 *
 * Description: Reads the file with the info about the park
 *
 *****************************************************************************/

Park *ReadFilePark (char * file)
{
	int i = 0, j = 0, l = 0, n, m, p, e, s;

	FILE *f;
	Park *p;

	f = AbreFicheiro(file, "r");

	fscanf(f, "%d %d %d %d %d", &n, &m, &p, &e, &s);

	p = NewPark(n, m, e, s, p);

	for(l = 0; l < p; l++)
	{
		Read_floor(p, f, l, &i, &j);
	}

	return (p);
}

	 
  







//-------------------------------------------------------------------------------------------------------
//main para testes:
/*
int main()
{

	Park *p;

	p = NewPark(3, 4, 2, 3, 2);

	p->entries[2].name = "E1";

	printf("%s\n", p->entries[2].name);

	return 0;
}*/


