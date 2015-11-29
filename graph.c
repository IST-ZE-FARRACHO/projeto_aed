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

#define P (wt[(*v)] + t->weight)

#define ROAD 0
#define WALL 1
#define ENTRY_DOOR 2
#define PED_ACCESS 3
#define EMPTY_SPOT 4
#define OCCUPIED 5
#define RAMP_UP 6
#define RAMP_DOWN 7
#define ENTRY_DOOR 2

/******************************************************************************
 * NEW()
 *
 * Arguments: v
 *             next - next node of list
 * Returns: link struct
 * Description: Creates a new node of the linked struct
 *
 *****************************************************************************/
link * NEW(int v, int weight, link *next)
{
	link * x = (link *) malloc(sizeof(link));

	if (x == NULL)
	{
		fprintf(stderr, "Error in malloc of node.\n");
		exit(1);
	}

	x->v = v;
	x->weight = weight;
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
	int i;
	Graph *G = (Graph *) malloc(sizeof(struct graph));

	if(G == NULL)
	{
		fprintf(stderr, "Error in malloc of graph.\n");
		exit(1);
	}

	G->V = V;
	G->E = 0;
	G->adj = (link **) malloc(V * sizeof(link *));
	G->node_info = (Graph_node *) malloc(V * sizeof(Graph_node));

	if(G->adj == NULL || G->node_info == NULL)
	{
		fprintf(stderr, "Error in malloc of graph vectors.\n");
		exit(1);
	}

	for(i = 0; i < V; i++)
	{
		G->node_info[i].pos = (Position *) malloc(sizeof(Position));

		if(G->node_info[i].pos == NULL)
		{
			fprintf(stderr, "Error in malloc of graph nodes information vector.\n");
		}
	} 

	for (i = 0; i < V; i++)
		G->adj[i] = NULL;

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

 	free(G->node_info);
 	free(G->adj);	
 	free(G);
 }


 /******************************************************************************
 * GRAPHpfs()
 *
 * Arguments: G - graph
 *	          s
 *
 * Description: Dijkstra's Algorithm
 *
 *****************************************************************************/

void GRAPHpfs(Graph *G, int s, int st[], double wt[])
 {
 	int * v, w; link * t;
 	double maxWT = G->V;

 	PQinit(G->V);
 	for((*v) = 0; (*v) < G->V; (*v)++)
 	{
 		st[(*v)] = -1;
 		wt[(*v)] = maxWT;
 		printf("pila\n");
 		PQinsert((Item) v);
 	}
 	wt[s] = 0.0;
 	PQdec(s);
 	while(!PQempty())
 		if(wt[(*v) = PQdelmin()] != maxWT)
 			for(t = G->adj[(*v)]; t != NULL; t = t->next)
 				if(wt[w = t->v] > P)
 				{
 					wt[w] = P;
 					PQdec(w);
 					st[w] = (*v);
 				}
 }