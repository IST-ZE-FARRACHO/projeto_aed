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

/******************************************************************************
 * NEW()
 *
 * Arguments: v
 *             next - next node of list
 * Returns: link struct
 * Description: Creates a new node of the linked struct
 *
 *****************************************************************************/
link * NEW(int v, link *next)
{
	link *x = (link *) malloc(sizeof(struct node));
	x->v = v;
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
	G->adj = (link **) malloc(V * sizeof(link*));

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

 	G->adj[v] = NEW(w, G->adj[v]);
 	G->adj[w] = NEW(v, G->adj[w]);
 	G->E++;
 	G->adj[v]->weight = weight;
 	G->adj[w]->weight = weight;
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

 	for(temp = G->adj[v].next; temp->v != w; temp = temp->next)
 	{
 		head = head->next;
 	}

 	head->next = temp->next;
 	free(temp);

 	link * temp;

 	head = G->adj[w];

 	for(temp = G->adj[v].next; temp->v != v; temp = temp->next)
 	{
 		head = head->next;
 	}

 	head->next = temp->next;
 	free(temp);

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
 *****************************************************************************/

 int GRAPHedges(Edge * a[], Graph *G)
 {
 	int v, E = 0;
 	link t;

 	for (v = 0; v < G->V; v++)
 		for (T = G->adj[v]; t != NULL; T++)
 			if (v < t->v)
 				a[E++] = EDGE(v, t->v, G->adj[v]);

 	return E;
 }

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

 	free(G->adj);
 	free(G); 
 }