/******************************************************************************
 *
 * File Name: graph.c
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *		creates graph
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

#define ROAD 0
#define WALL 1
#define ENTRY_DOOR 2
#define PED_ACCESS 3
#define EMPTY_SPOT 4
#define OCCUPIED 5
#define RAMP_UP 6
#define RAMP_DOWN 7
#define ENTRY_DOOR 2

#define NORMAL_TIME 1
#define RAMP_TIME 2

/******************************************************************************
 * NEW()
 *
 * Arguments: v
 *             next - next node of list
 * Returns: link struct
 * Description: Creates a new node of the linked struct
 *
 *****************************************************************************/
link * NEW(int v, int type, link *next)
{
	link * x = (link *) malloc(sizeof(link));

	if (x == NULL)
	{
		fprintf(stderr, "Error in malloc of node.\n");
		exit(1);
	}

	x->v = v;
	x->type = type;
	x->next = next;

	return x;
}

/******************************************************************************
 * EDGE()
 *
 * Arguments: v - node 1
 *            w - node 2
 *            weight
 * Returns: Edge
 * Description: Creates an edge
 *
 *****************************************************************************/

Edge * EDGE(int v, int w, int weight)
{
	Edge * e;
	e = (Edge *) malloc(sizeof(Edge));

	if(e == NULL)
	{
		fprintf(stderr, "Error in malloc of edge.\n");
	}

	e->v = v;
	e->w = w;
	e->weight = weight;

	return e;
}

/******************************************************************************
 * GRAPHinit()
 *
 * Arguments: V - number of nodes

 * Returns: Graph
 * Description: Creates a graph with the final number of nodes, but with no edges
 *
 *****************************************************************************/

Graph *GRAPHinit(int V)
{
	int v;
	Graph *G = (Graph *) malloc(sizeof(struct graph));

	if(G == NULL)
	{
		fprintf(stderr, "Error in malloc of graph.\n");
		exit(1);
	}

	G->V = V;
	G->E = 0;
	G->adj = (link **) malloc(V * sizeof(link *));

	for (v = 0; v < V; v++)
		G->adj[v] = NULL;

	return G;
}

/******************************************************************************
 * GRAPHinsertE()
 *
 * Arguments: G - graph
 			  e - struct of edges
 *            value - edge weight
 *
 * Description: Inserts a new edge, if it doesn't exist
 *
 *****************************************************************************/

 void GRAPHinsertE(Graph *G, Edge *e) 
 {
 	int v = e->v, w = e->w, weight = e->weight;

 	G->adj[v] = NEW(w, weight, G->adj[v]);
 	G->adj[w] = NEW(v, weight, G->adj[w]);

 	G->E++;
 }

 /******************************************************************************
 * GRAPHremoveE()
 *
 * Arguments: G - graph
 *            e - struct of edges
 * Description: Removes an edge from the graph, if the edge exists
 *
 *****************************************************************************/

 void GRAPHremoveE(Graph *G, Edge *e)
 {
 	int v = e->v, w = e->w;

 	link * temp;
 	link * head;

 	head = G->adj[v];

 	for(temp = G->adj[v]->next; temp->v != w; temp = temp->next)
 	{
 		head = head->next;
 	}

 	head->next = temp->next;
 	free(temp);

 	link * temp2;

 	head = G->adj[w];

 	for(temp2 = G->adj[v]->next; temp2->v != v; temp2 = temp2->next)
 	{
 		head = head->next;
 	}

 	head->next = temp2->next;
 	free(temp2);

 	G->E--;
 }

 /******************************************************************************
 * GRAPHedges()
 *
 * Arguments: a - vector of edges
 *            G - graph
*
 * Returns: number of edges
 * Description: Counts the number of edges
 *
 *****************************************************************************

 int GRAPHedges(Edge * a[], Graph *G)
 {
 	int v, E = 0;
 	link * t;

 	for (v = 0; v < G->V; v++)
 		for (t = G->adj[v]; t != NULL; t = t->next)
 			if (v < t->v)
 				a[E++] = EDGE(v, t->v, );

 	return E;
 }*/

 /******************************************************************************
 * GRAPdestroy()
 *
 * Arguments: G - graph
 *
 * Description: Deletes a graph
 *
 *****************************************************************************/

 void GRAPHdestroy(Graph *G)
 {
 	int i;
 	link * head;
 	link * aux;

 	for(i = 0; i < G->V; i++)
 	{
 		for(head = G->adj[i]; head != NULL; )
 		{
 			aux = head;
 			head = head->next;
 			free(aux);
 		} 	
 	}
 	free(G->adj);	
 	free(G);
 }

 /******************************************************************************
 * Matrix_to_GRAPH()
 *
 * Arguments: e - vector of edges
 *            G - graph
 *            p - struct of park
 *            vector - vector with the position of each node
 *            nodes - number of nodes
 *            edges - number of edges
 * Description: Reads the matrix, and inserts the connections between every possible 
 *              position on the graph
 *
 *****************************************************************************/

 void Matrix_to_GRAPH(Graph *G, Edge * e[], Park *p, Position * vector[], int nodes)
 {
 	int x, y, z, actual_node = 0, actual_edge = 0, i;

 	for(z = 0; z < p->P; z++)
 		for(y = 0; y < p->M-1; y++)
 			for(x = 0; x < p->N-1; x++)
 				if(p->matrix[x][y][z] != WALL)
 				{
 					if(p->matrix[x][y][z] == ROAD) //if the position is a road:
 					{
 						if(p->matrix[x+1][y][z] != WALL) //if the position to the right isnt a wall, it creates an edge and inserts it in the graph
 						{
 							e[actual_edge] = EDGE(actual_node, actual_node + 1, NORMAL_TIME);
 							GRAPHinsertE(G, e[actual_edge]);
 							actual_edge++;
 						}
 						if(p->matrix[x][y+1][z] != WALL) //if the position directly below isnt a wall, it searches for the respective node on the node positions vector
 						{ 
 							i = actual_node + 1;

 							while(vector[i]->x != x && vector[i]->y != y+1 && vector[i]->z != z)
 								i++;
 							e[actual_edge] = EDGE(actual_node, i, NORMAL_TIME); //creates the edge
 							GRAPHinsertE(G, e[actual_edge]); //inserts the edge on the graph
 							actual_edge++;
 						}							
 					}
 					else if (p->matrix[x][y][z] == RAMP_UP) //if the position is a ramp:
 					{
 						if(p->matrix[x+1][y][z] == ROAD) //if theres a road to the right, creates edge and inserts on the graph
 						{
 							e[actual_edge] = EDGE(actual_node, actual_node + 1, NORMAL_TIME);
 							GRAPHinsertE(G, e[actual_edge]);
 							actual_edge++;
 						}
 						if(p->matrix[x][y+1][z] == ROAD) //if theres a road directly below, it searches for the node on the node positions vector
 						{
 							i = actual_node + 1;

 							while(vector[i]->x != x && vector[i]->y != y+1 && vector[i]->z != z)
 								i++;
 							e[actual_edge] = EDGE(actual_node, i, NORMAL_TIME); //creates the edge
 							GRAPHinsertE(G, e[actual_edge]); //inserts the edge on the graph
 							actual_edge++;
 						}
 						i = actual_node + 1; //searches in the node positions vector for the node driectly above the ramp

 						while(vector[i]->x != x && vector[i]->y != y && vector[i]->z != z+1)
 							i++;
 						e[actual_edge] = EDGE(actual_node, i, RAMP_TIME); //creates the edge
 						GRAPHinsertE(G, e[actual_edge]); //inserts it on the graph
 						actual_edge++;
 					}
 					actual_node++;
 				}
 }

 /******************************************************************************
 * Count_Park_Nodes_Edges()
 *
 * Arguments: p - struct of park
 *            nodes - number of nodes
 *            edges - number of edges
 * Description: Reads the matrix, and counts the number of nodes and edges
 *
 *****************************************************************************/

 void Count_Park_Nodes_Edges(Park *p, int * edges, int * nodes)
 {
 	int x, y, z;

 	for(z = 0; z < p->P; z++)
 		for(y = 0; y < p->M-1; y++)
 			for(x = 0; x < p->N-1; x++)
 			{
 				if(p->matrix[x][y][z] != WALL)
 				{
 					if(p->matrix[x][y][z] == ROAD) //if its a road, it connects to everything on its sides, except the walls
 					{
 						if(p->matrix[x+1][y][z] != WALL)
 							(*edges)++;
 						if(p->matrix[x][y+1][z] != WALL)
 							(*edges)++;
 					}
 					else //if its not a road, it only connects the roads on its sides
 					{
 						if(p->matrix[x+1][y][z] == ROAD) 
 							(*edges)++;
 						if(p->matrix[x][y+1][z] == ROAD)
 							(*edges)++;						
 					}

 					if(p->matrix[x][y][z] == RAMP_UP)
 						(*edges)++;
  				(*nodes)++;
 				}
 			}
 }

 /******************************************************************************
 * Creates_Park_GRAPH()
 *
 * Arguments: e - vector of edges
 *            vector - vector of graph nodes position
 *            p - struct of park
 *            vector - vector with the position of each node
 * Returns: Graph
 * Description: Creates the graph of the park and the vectors of edges and graph 
 *              nodes positions
 *
 *****************************************************************************/

 Graph * Creates_Park_GRAPH(Park *p, Edge ** e, Position ** vector)
 {
 	int x, y, z, nodes = 0, edges = 0, i = 0;

 	Graph *G;

 	Count_Park_Nodes_Edges(p, &edges, &nodes);

 	printf("%d %d\n", nodes, edges);
 		
 	vector = (Position **) malloc(nodes*sizeof(Position *)); //allocates memory for the graph nodes position vector

 	///////////////FODAAAAASSE SEG FAULT AQUI------------------------------------------------------------------------------------

 	vector[1]->x = 20;
 	printf("%d\n", vector[0]->x);

 	if(vector == NULL)
 	{
 		fprintf(stderr, "Error in malloc of graph nodes prosition vector.\n");
 		exit(1);
 	}

  	for(z = 0; z < p->P; z++)
 		for(y = 0; y < p->M-1; y++)
 			for(x = 0; x < p->N-1; x++)
 				if(p->matrix[x][y][z] != WALL)
 				{
 					vector[i]->x = x;
 					vector[i]->y = y;
 					vector[i]->z = z;
 					i++;
 				}



 	e = (Edge **) malloc(edges*sizeof(Edge *)); //allocates memory for the vector of edges

 	if(e == NULL)
 	{
 		fprintf(stderr, "Error in malloc of edge vector.\n");
 		exit(1);
 	}

 	G = GRAPHinit(nodes); //initiates the graph

 	Matrix_to_GRAPH(G, e, p, vector, nodes);

 	return G;
 }


/****************Main para testes********************************************/

 int main(int argc, char *argv[])
 {
 	/*int i = 0;

 	Graph *G;
 	Edge **e = (Edge **) malloc(3*sizeof(Edge *));

 	G = GRAPHinit(5);

 	e[0] = EDGE(1,2,3);
 	e[2] = EDGE(3,4,2);
 	e[1] = EDGE(2,3,1);

 	while(i < 3)
 	{
 		GRAPHinsertE(G, e[i]);
 		i++;
 	}

 	printf("%d %d %d\n", G->adj[1]->v, G->adj[2]->next->v, G->adj[1]->weight);
 	printf("%d %d %d\n", G->adj[2]->v, G->adj[3]->next->v, G->adj[3]->weight);
 	printf("%d %d %d\n", G->adj[3]->v, G->adj[4]->v, G->adj[4]->weight);
 	printf("%d\n", GRAPHedges(e, G));

 	GRAPHdestroy(G);

 	for(i = 0; i < 3; i++)
 		free(e[i]);

 	free(e);*/

 	Park * p;

	p = ReadFilePark(argv[1]);

 	Position **vector;

 	Edge **e;

 	Graph *G;

 	G = Creates_Park_GRAPH(p, e, vector);





 	return 0;
 }