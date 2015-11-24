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

int **MATRIXint(int V, int K, int init);

link * NEW(int v, link *next);
Edge *EDGE(int, int, int);
Graph *GRAPHinit(int);
void GRAPHinsertE(Graph *G, Edge*, int);
void GRAPHremoveE(Graph *G, Edge*);
int GRAPHedges(Edge * a[], Graph *G);
Graph *GRAPHcopy(Graph *G);
void GRAPHdestroy(Graph *G);


 #endif