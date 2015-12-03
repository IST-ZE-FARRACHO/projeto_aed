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
<<<<<<< HEAD

FILE *OpenFile(char *name, char *mode);
void CloseFile(FILE * f);
=======
#include "graph.h"
 /******************************************************************************
 * AbreFicheiro ()
 *
 * Arguments: nome - pointer to string containing name of file to open
 *            mode - mode to use to open the file
 * Returns: FILE * - handle to file opened
 * Side-Effects: input file is opened
 *
 * Description: Open file for reading, returns handle
 *
 *****************************************************************************/

FILE *AbreFicheiro(char *name, char *mode);
void FechaFicheiro(FILE * f);
>>>>>>> c49065fa2b97ac2dfd423cdd8d67645a491d18fd
LinkedList * ListCreator();
int Get_Pos(int, int, int, int, int);
void exch(int *i, int *j);

#endif