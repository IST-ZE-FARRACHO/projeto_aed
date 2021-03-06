/******************************************************************************
 *
 * File Name: tree.h
 * Author:    José Correia / António Farracho
 *
 * DESCRIPTION
 *
 *****************************************************************************/

 #ifndef tree_H
 #define tree_H

 #include "defs.h"

link_tree * NEW_tree(Parking_spot *spot);
link_tree * parse();
int height(link_tree *tree);
link_tree *rotate_right(link_tree * tree);
link_tree *rotate_left(link_tree * tree);
link_tree * insert(Parking_spot *i, link_tree *tree);
link_tree * join(link_tree *a, link_tree *b);
link_tree * delete(Parking_spot *i, link_tree *tree);

 #endif
