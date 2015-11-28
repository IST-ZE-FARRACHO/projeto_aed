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
LinkedList * ListCreator();
int Get_Pos(int, int, int, int, int);
void exch(int *i, int *j);


 /* End of: Protect multiple inclusions                              */
#endif