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

struct _position
{
	int x;
	int y;
	int z;
};

typedef struct _position Position;

/********************************************************/
struct _node
{
	Position * pos;
	int type;
};

typedef struct _node Graph_node;
/**************************************************************************/

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

/***************************************************************************/
struct _car // Struct for cars
{
	char *id; // Vehicle identification
	int ta; // Entrance moment - TA
	int tb; // Exit time - TE
	char type; // Type of access required
//“C” (Cinema), “H” (Habitacão), “E” (Escritorios), “L” (Loja) ou “R”(Restauracao)
	int xs;  // Actual coordinates
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
	int type;
	int tb;
	int ex;
	int ey;
	int px;
};

typedef struct _restPos Rest_pos;

/*******************************************************************************/
struct _restrict
{
	int type; // 0 - Position Restriction | 1 - Floor Restriction
	int ta;
	int tb;
	int xs;
	int ys;
	int zs;
};

typedef struct _restrict Restrictions;

/*********************************************************************************/

struct _event // Struct for events
{
	char type; // Event type
	// 'E' for Entrance, 'S' for Exit (Car is in list), 'F' for Exit (Car not in the list), 'R' (Ending restrition)
	
	int time; // Event starting time

	Item object; //object related to the event (car, restriction, etc...);


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

/************************************************************************/
typedef struct node link;

struct node
{
	int v;
	int weight; //type of the node
	link *next;
};

/**************************************************************************/
struct graph 
{
	int V; //number of nodes
	int E; //number of edges
	link **adj;
	Graph_node *node_info; //vector with the info about each node
};

typedef struct graph Graph;

/************************************************************************/
struct edge
{
	int v; //node 1
	int w; //node 2
	int weight;
};

typedef struct edge Edge;

/************************************************************************/
struct _park 
{
 	int N; //number of columns
 	int M; //number of lines
 	int P; //number of floors
 	int E; //number of entrances
 	int S; //number of accesses
 	Graph *G;
 	Entrance *entries; //vector that stores the info about the entrances;
 	Access *accesses; //vector that stores the info about the accesses;
};

typedef struct _park Park;


 #endif