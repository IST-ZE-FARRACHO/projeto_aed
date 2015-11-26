/******************************************************************************
 *
 * File Name: graph.h
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *
 *****************************************************************************/

 #ifndef graph_H
 #define graph_H

#include "defs.h"
#include "park_config.h"
#include "defs.h"
#include "tools.h"

link * NEW(int, int, link *next);
Edge *EDGE(int, int, int);
Graph *GRAPHinit(int);
void GRAPHinsertE(Graph *G, Edge *e);
void GRAPHremoveE(Graph *G, Edge*);
int GRAPHedges(Edge * a[], Graph *G);
Graph *GRAPHcopy(Graph *G);
void GRAPHdestroy(Graph *G);

void Matrix_to_GRAPH(Graph *G, Edge * e[], Park *p, Position * vector[], int);
void Count_Park_Nodes_Edges(Park *p, int * edges, int * nodes);
Graph *Creates_Park_GRAPH(Park *p, Edge ** e, Position ** vector);



 #endif