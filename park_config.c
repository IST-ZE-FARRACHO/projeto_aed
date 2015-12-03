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

/******************* Defines **************************/

#define ROAD 0
#define WALL 1
#define ENTRY_DOOR 2
#define PED_ACCESS 3
#define EMPTY_SPOT 4
#define OCCUPIED 5
#define RAMP_UP 6
#define RAMP_DOWN 7
#define NAME_SIZE 4

#define NORMAL_TIME 1
#define RAMP_TIME 2

 #define CAN_GO 0
 #define CANT_GO 1
/******************************************************************************
 * NewPark
 *
 * Arguments: Number of columns
 *            Number of lines
 *			  Number of entrances
 *            Number of accesses
 *
 * Returns: Allocated Park
 *
 * Description: Creates a new Park Structure
 *
 *****************************************************************************/

Park * NewPark(int columns, int lines, int entrances, int nr_accesses, int floors)
{
	Park * p;
	int i;

 	p = (Park *) malloc(sizeof(Park)); // Allocates memory for the struct


	if (p == (NULL)) // Memory allocation testing
	{
		fprintf(stderr, "Error in malloc of park.\n");
		exit(0);
	}

	p->entries = (Entrance*) malloc(entrances*sizeof(Entrance));  // Entries array

 	p->accesses = (Access*) malloc(nr_accesses*sizeof(Access)); // Access array

 	if(p->entries == NULL || p->accesses == NULL)
 	{
 		fprintf(stderr, "Error in malloc of entries/accesses.\n");
 		exit(0);
 	}

  	for(i = 0; i < entrances; i++) // Allocates entries coordinates storage
 	{	
 		p->entries[i].pos = (Position*) malloc(sizeof(Position));
 		
 		if(p->entries[i].pos == NULL)
 		{
 			fprintf(stderr, "Error in malloc of entries/accesses.\n");
 			exit(0);
 		}
 	}

 	for(i = 0; i < nr_accesses; i++) // Allocates accesses coordinates storage
 	{	
 		p->accesses[i].pos = (Position*) malloc(sizeof(Position));
 		
 		if(p->accesses[i].pos == NULL)
 		{
 			fprintf(stderr, "Error in malloc of entries/accesses.\n");
 			exit(0);
 		}
 	}	

 	p->G = GRAPHinit(columns*lines*floors); // Initializes a park-sized Graph

	p->N = columns;
	p->M = lines;
	p->P = floors;
	p->E = entrances;
	p->S = nr_accesses;
	p->Spots = 0;

	return (p);
}

/******************************************************************************
 * Char_to_Number
 *
 * Arguments: Character to transform
 *
 * Returns: Integer
 *
 * Description: Transforms a character from the map to the equivalent integer
 *
 *****************************************************************************/

int Char_to_Number (char c)
{
	if(c == ' ')
	{
		return ROAD;
	}

	else if(c == '@')
	{
		return WALL;
	}

	else if(c == 'e')
	{
		return ENTRY_DOOR;
	}

	else if(c == 'a')
	{
		return PED_ACCESS;
	}

	else if(c == '.')
	{
		return EMPTY_SPOT;
	}

	else if(c == 'x')
	{
		return OCCUPIED;
	}

	else if(c == 'u')
	{
		return RAMP_UP;
	}

	else if(c == 'd')
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
 * Matrix_to_GRAPH()
 *
 * Arguments: p - struct of park
 *            vector1 - actual line of the file
 *            vector2 - next line of the file
 *            y1 - line of the vector1
 *            y2 - line of the vector2
 *            floor - actual floor
 * Description: Receives two lines of the file, and inserts the connections between every possible 
 *              position on the graph
 *
 *****************************************************************************/

 void Get_edges(Park *p, int vector1[], int vector2[], int nr_columns, int y1, int y2, int _floor)
 {
 	int x, actual_node1 = Get_Pos(0, y1, _floor, p->N, p->M), actual_node2 = Get_Pos(0, y2, _floor, p->N, p->M);
 	int node_above;

 	for(x = 0; x < nr_columns; x++)
 	{	
 		if(vector1[x] != OCCUPIED && vector1[x] != WALL)
 			p->G->node_info[actual_node1].status = CAN_GO;
 		else{
 			p->G->node_info[actual_node1].status = CANT_GO;
 		}

 		if(vector2[x] != OCCUPIED && vector2[x] != WALL)
 			p->G->node_info[actual_node2].status = CAN_GO;
 		else{
 			p->G->node_info[actual_node2].status = CANT_GO;
 		}

 		p->G->node_info[actual_node1].pos->x = x;
 		p->G->node_info[actual_node1].pos->y = y1;
 		p->G->node_info[actual_node1].pos->z = _floor;
 		p->G->node_info[actual_node1].type = vector1[x];

 		p->G->node_info[actual_node2].pos->x = x;
 		p->G->node_info[actual_node2].pos->y = y2;
 		p->G->node_info[actual_node2].pos->z = _floor;
 		p->G->node_info[actual_node2].type = vector2[x];

 		if(vector1[x] == EMPTY_SPOT)
 			p->Spots++;

 		if(vector1[x] != WALL)
 		{
 			if(vector1[x] == ROAD) /*if the position is a road:*/
 			{
 				if(vector1[x+1] != WALL) /*if the position to the right isnt a wall, it creates an edge and inserts it in the graph*/
 				{
 					GRAPHinsertE(p->G, EDGE(actual_node1, actual_node1 + 1, NORMAL_TIME));
 				}
 				if(vector2[x] != WALL) /*if the position directly below isnt a wall, it searches for the respective node on the node positions vector*/
 				{ 
 					GRAPHinsertE(p->G, EDGE(actual_node1, actual_node2, NORMAL_TIME)); /*inserts the edge on the graph*/
 				}					
 			}
 			else if (vector1[x] == RAMP_UP || vector1[x] == RAMP_DOWN) /*if the position is a ramp:*/
 			{
 				if(vector1[x+1] == ROAD) /*if theres a road to the right, creates edge and inserts on the graph*/
 				{
 					GRAPHinsertE(p->G, EDGE(actual_node1, actual_node1 + 1, NORMAL_TIME));
 				}
 				if(vector2[x] == ROAD) /*if theres a road directly below, it searches for the node on the node positions vector*/
 				{
 					GRAPHinsertE(p->G, EDGE(actual_node1, actual_node2, NORMAL_TIME));
 				}
 				node_above = Get_Pos(x, y1, _floor+1, p->N, p->M);
 				GRAPHinsertE(p->G, EDGE(actual_node1, node_above, RAMP_TIME)); /*inserts it on the graph*/
 			}
 			else if(vector1[x] == EMPTY_SPOT || vector1[x] == PED_ACCESS || vector1[x] == ENTRY_DOOR)
 			{
 				if(vector1[x+1] == ROAD)
 				{
 					GRAPHinsertE(p->G, EDGE(actual_node1, actual_node1 + 1, NORMAL_TIME));
 				}
 				if(vector2[x] == ROAD)
 				{
 					GRAPHinsertE(p->G, EDGE(actual_node1, actual_node2, NORMAL_TIME));
 				}
 			}
 		}
 		actual_node1++;
 		actual_node2++;
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
 * Description: Reads the map and inserts in matrix. Prints the matrix on the screen
 *
 *****************************************************************************/

void Map_to_Park_Graph (Park * p, FILE * f, int _floor) 
{
	int x, y;
	char vector2[p->N]; /*Line storage vector*/
	int vector1_nr[p->N];
	int vector2_nr[p->N];

	printf("\nFloor number: %d\n", _floor);

	fgets(vector2, (p->N+1)*(p->M), f); 
	
	for(y = p->M-1; y > 0; y--) /*For each one of the lines*/
	{
		for (x = 0; x < p->N; x++) /*For each one of the characters*/
		{
			vector1_nr[x] = Char_to_Number(vector2[x]); /*Converts the symbol into integer and fills the numbers vector*/
			printf("%d", vector1_nr[x]); /*prints the type of the position on the screen*/
		}
		printf("\n");

		fgets(vector2, (p->N+1)*(p->M), f); 

		for(x = 0; x < p->N; x++){
			vector2_nr[x] = Char_to_Number(vector2[x]);
			if(y == 1)
				printf("%d", vector2_nr[x]);
		}


		Get_edges(p, vector1_nr, vector2_nr, p->N, y, y-1, _floor); /*Get edges of the graph*/
	}
	printf("\n\n");
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

void Read_Doors_info (Park * p, FILE * f, int *i, int *j) /*i, j, declare where to start inserting entries or accesses in the vectors*/
{
	int door_x, door_y, door_z, doors = 0;
	char door_name[NAME_SIZE], door_type; 

	while(doors < p->E + p->S) /*reads lines until the number of entries + accesses is reached*/
	{
		fscanf(f, "%s %d %d %d %c", door_name, &door_x, &door_y, &door_z, &door_type); /*reads the first line with the dimensions, etc...*/
		if (door_name[0] == 'E')  /*if its an entry inserts the information in the p->entries vector*/
		{
			strcpy(p->entries[(*i)].name, door_name);
			p->entries[(*i)].pos->x = door_x;
			p->entries[(*i)].pos->y = door_y;
			p->entries[(*i)].pos->z = door_z;
			printf("Entrance: %s (%d,%d,%d)\n", p->entries[(*i)].name, p->entries[(*i)].pos->x, p->entries[(*i)].pos->y, p->entries[(*i)].pos->z);
			(*i)++;
		}

		else if (door_name[0] == 'A') /*if its an access inserts the information in the p->accesses vector*/
		{
			strcpy(p->accesses[(*j)].name, door_name);
			p->accesses[(*j)].pos->x = door_x;
			p->accesses[(*j)].pos->y = door_y;
			p->accesses[(*j)].pos->z = door_z;
			printf("Access: %s (%d,%d,%d)\n", p->accesses[(*j)].name,  p->accesses[(*j)].pos->x,  p->accesses[(*j)].pos->y,  p->accesses[(*j)].pos->z);
			(*j)++;
		}

		else if(door_name[0] == '+') /*if +, finishes the reading about the actual floor*/
		{
			break;
		}

		else
		{
			printf("Invalid door information in park file!\n");
		}
		doors++;
	}
}

/******************************************************************************
 * Read_floor
 *
 * Arguments: File to read
 *            Struct of park
 *			  Floor to be read
 *			  Position index i
 *			  Position index j
 *			
 *
 * Returns: -
 *
 * Description: Transforms each floor into a graph. Reads Door info
 *
 *****************************************************************************/

void Read_floor (Park * p, FILE * f, int _floor, int *i, int *j)
{
	Map_to_Park_Graph(p, f, _floor);

	Read_Doors_info(p, f, i, j);
}

/******************************************************************************
 * ReadFilePark
 *
 * Arguments: File to be read
 *			 
 * Returns: Created Park
 *
 * Description: Reads the file with the initial info about the park
 *
 *****************************************************************************/

Park * ReadFilePark (char * file)
{
	int i = 0, j = 0, l = 0, n, m, p, e, s;
	char line [NAME_SIZE];

	FILE *f;
	Park *new_park;

	f = OpenFile(file, "r");

	fscanf(f, "%d %d %d %d %d", &n, &m, &p, &e, &s); /*Reads initial file info*/

	fgets(line, sizeof(line), f); // Carrys on to the second line of the file (line is not used anywhere else)

	new_park = NewPark(n, m, e, s, p); // Creates new park struct with read info

	for(l = 0; l < p; l++) // For each of the floors
	{
		Read_floor(new_park, f, l, &i, &j); // Read floor function - reads floor data

	}

	CloseFile(f); // Closes file

	return new_park; // Returns created Park
}

/******************************************************************************
 * AccessTreesCreator
 *
 * Arguments: Park structure
 *			 
 * Returns: 
 *
 * Description:
 *
 *****************************************************************************/

/*link_tree * AccessTreesCreator(Park *p)
{
	link_tree **trees_vector = (link_tree **) malloc((p->S)*sizeof(link_tree *));
	
	if(trees_vector == NULL)
	{
		fprintf((stderr), "Error in malloc of trees vector.\n");
		exit(1);
	}


}*/

void FreePark(Park * p)
{	
	int i;

	for(i = 0; i < p->E; i++) // Frees structures from Entries array
 	{	
 		free(p->entries[i].pos);
 	}

 	for(i = 0; i < p->S; i++) // Free structures from Accesses array
 	{	
 		free(p->accesses[i].pos);
 	}	

	free(p->entries);
 	free(p->accesses);
 	GRAPHdestroy(p->G);
 	free(p);

}