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

/******************* Defines **************************/

#define ROAD 0
#define WALL 1
#define ENTRY_DOOR 2
#define PED_ACCESS 3
#define EMPTY_SPOT 4
#define OCCUPIED 5
#define RAMP_UP 6
#define RAMP_DOWN 7

/******************************************************/

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

     		if(p->matrix[y][z] == NULL)
     		{
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
	printf("%s\n", c);
	if(c == " ")
	{
		return ROAD;
	}

	if(strcmp(c, "@") == 0)
	{
		return WALL;
	}

	if(strcmp(c, "a") == 0)
	{
		return PED_ACCESS;
	}

	if(strcmp(c, ".") == 0)
	{
		return EMPTY_SPOT;
	}

	if(strcmp(c, "x") == 0)
	{
		return OCCUPIED;
	}

	if(strcmp(c, "u") == 0)
	{
		return RAMP_UP;
	}

	if(strcmp(c, "d") == 0)
	{
		return RAMP_DOWN;
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

void Map_to_matrix (Park * p, FILE * f, int _floor) 
{
	int x, y;
	char vector[p->N]; // Line storage vector
	
	for(y = 0; y < p->M; y++) // For each one of the lines
	{
		fgets(vector, p->N+1, f); // Gets de line
		
		for (x = 0; x < p->N; x++) // For each one of the characters
		{
			p->matrix[x][y][_floor] = Char_to_Number(&(vector[x]));	// Converts the symbol into integer and fills the corresponding floor-matrix
			printf("%d", p->matrix[x][y][_floor]); 
		}
		printf("\n");
	}

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

void Read_Doors_Info (Park * p, FILE * f, int *i, int *j) //i, j, declare where to start inserting entries or accesses in the vectors
{
	int door_x, door_y, door_z; // New door coordinates
	char door_name[4], door_type;

	while(fscanf(f, "%s %d %d %d %c", door_name, &door_x, &door_y, &door_z, &door_type)) // Reads line
	{
		if (door_name[0] == 'E') // If the door is an entrance
		{
			strcpy(p->entries[(*i)].name, door_name);
			p->entries[(*i)].xs = door_x;
			p->entries[(*i)].ys = door_y;
			p->entries[(*i)].zs = door_z;
			(*i)++;
		}

		else if (door_name[0] == 'A') // If the door is an access
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
	Map_to_matrix(p, f, _floor);

	Read_Doors_info(p, f, &(*i), &(*j));
}

/******************************************************************************
 * ReadFilePark (char * file)
 *
 * Arguments: File to be read
 *			 
 * Returns: Created Park
 *
 * Description: Reads the file with the info about the park
 *
 *****************************************************************************/

Park *ReadFilePark (char * file)
{
	int i = 0, j = 0, l = 0, n, m, p, e, s;

	FILE *f;
	Park *new_park;

	char line [5];

	f = AbreFicheiro(file, "r");

	fscanf(f, "%d %d %d %d %d", &n, &m, &p, &e, &s); // Reads initial file info

	fgets(line, sizeof(line), f); // Carrys onto the next line

	new_park = NewPark(n, m, e, s, p); // Initialises Park with retrieved info

	for(l = 0; l < p; l++) // For each one of the floors
	{
		Read_floor(new_park, f, l, &i, &j); // Read floor function
	}

	return new_park; // Returns new_park
}

	 
  







//-------------------------------------------------------------------------------------------------------
//main para testes:

int main(int argc, char **argv)
{

	Park *p;
	char *ficheiro = argv[1];
	int k, j, i;

	/*p = NewPark(3, 4, 2, 3, 2);

	p->entries[2].name = "E1";

	printf("%s\n", p->entries[2].name);*/

	p = ReadFilePark(ficheiro);


  for(k = 0; k< 2; k++){
    for(j = 0; j<3; j++){
      for(i = 0; i<5; i++){
        p->matrix[i][j][k] = 3;
        printf("%d   ", p->matrix[i][j][k]);
      }
      printf("\n");
    }
    printf("\n\n");
  }

	return 0;
}


