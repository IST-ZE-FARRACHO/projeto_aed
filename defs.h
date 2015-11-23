/******************************************************************************
 *
 * File Name: defs.h
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *
 *****************************************************************************/

 #ifndef defs_H
 #define defs_H

 #define NAME_SIZE 4

typedef void * Item;

struct _entrance 
{ //struct for entrances
	char name[NAME_SIZE]; //name of the entrance
 	int xs;  //coordinates
 	int ys;
 	int zs;
};

typedef struct _entrance Entrance;

/*********************************************************************/
struct _access
{
	char name[NAME_SIZE]; //name of the access
 	int xs;  //coordinates
 	int ys;
 	int zs;
 	char type; //type of the access;
};

typedef struct _access Access;

/************************************************************************/
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

typedef struct _park Park;

/***************************************************************************/
struct _car // Struct for cars
{
	char *id; // Vehicle identification
	int ta; // Entrance moment - TA
	int tb; // Exit time - TE
	char type; // Type of access required
//“C” (Cinema), “H” (Habitacão), “E” (Escritorios), “L” (Loja) ou “R”(Restauracao)
	int xs;  // Entrance coordinates
	int ys; 
	int zs;
};

typedef struct _car Car;

/****************************************************************************/
struct _restFloor
{
	int ta;
	int tb;
	int px;
};

typedef struct _restFloor Rest_floor;

/********************************************************************************/
struct _restPos
{
	int ta;
	int tb;
	int ex;
	int ey;
	int ez;
};

typedef struct _restPos Rest_pos;

/*******************************************************************************/
struct _restrict
{
	Rest_floor *restricted_floors;
	Rest_pos *restricted_positions;
};

typedef struct _restrict Restrictions;

/*********************************************************************************/

struct _event // Struct for events
{
	char type; // Event type
	// 'E' for Entrance, 'S' for Exit (Car is in list), 'F' for Exit (Car not in the list), 'R' (Ending restrition)
	
	int time; // Event starting time


};

typedef struct _event Event;

/*************************************************************************************/

struct _liberation
{	
	int time; // Liberation ocurring time
	int xs; // Coordinates of the position to be liberated
	int ys;
	int zs;
};

typedef struct _liberation Liberation;

/*************************************************************************************/

/*
 *  Data Type: LinkedListStruct
 *
 *  Description: Structure with:
 *                 1) Pointer to the item of the linked list node
 *                 2) Pointer to next node of the linked list.
 */

/*
 *  Data type: LinkedList
 *
 *  Description: Node of a linked list
 */
typedef struct LinkedListStruct LinkedList;

struct LinkedListStruct
{
  Item this;
  LinkedList * next;
};


 #endif