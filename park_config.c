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


struct _entrance 
{ //struct for entrances
	char *name; //name of the entrance
 	int xs;  //coordinates
 	int ys;
 	int zs;
};

struct _access
{
	char *name; //name of the access
 	int xs;  //coordinates
 	int ys;
 	int zs;
 	char type; //type of the access;
};

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
	printf("%s\n", c);
	if(c == " ")
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

void Map_to_matrix (Park * p, FILE * f, int _floor) 
{
	int x, y;
	char vector[p->N];
	
	for(y = 0; y < p->M; y++)
	{
		fgets(vector, p->N+1, f);
		for (x = 0; x < p->N; x++)
		{
			p->matrix[x][y][_floor] = Char_to_Number(&(vector[x]));	
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

void Read_Doors_info (Park * p, FILE * f, int *i, int *j) //i, j, declare where to start inserting entries or accesses in the vectors
{
	int door_x, door_y, door_z;
	char door_name[4], door_type; 

	while(fscanf(f, "%s %d %d %d %c", door_name, &door_x, &door_y, &door_z, &door_type)) //reads line
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
	Map_to_matrix(p, f, _floor);

	Read_Doors_info(p, f, &(*i), &(*j));
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
	Park *new_park;

	char line [5];

	f = AbreFicheiro(file, "r");

	fscanf(f, "%d %d %d %d %d", &n, &m, &p, &e, &s);

	fgets(line, sizeof(line), f);

	new_park = NewPark(n, m, e, s, p);

	for(l = 0; l < p; l++)
	{
		Read_floor(new_park, f, l, &i, &j);
	}

	return (new_park);
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


