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
#include "heap.h"

link * NEW(int, int, link *next);
Edge *EDGE(int, int, int);
Graph *GRAPHinit(int);
void GRAPHinsertE(Graph *G, Edge *e);
void GRAPHremoveE(Graph *G, Edge*);
Graph *GRAPHcopy(Graph *G);
void GRAPHdestroy(Graph *G);

int LessNumPQ (Item a, Item b);
void PrintNumPQ(Item hi);

 void GRAPHpfs(Graph *G, int s, int parent[], long int dist[]);

 #endif