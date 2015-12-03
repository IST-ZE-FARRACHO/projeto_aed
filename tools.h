/******************************************************************************
 *
 * File Name: tools.h
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *
 *****************************************************************************/

#ifndef ToolsHeader
#define ToolsHeader

#include "defs.h"

FILE *OpenFile(char *name, char *mode);
void CloseFile(FILE * f);
LinkedList * ListCreator();
int Get_Pos(int, int, int, int, int);
void exch(int *i, int *j);

#endif