//
// Created by stefano on 27/12/17.
//

#ifndef L01_BST_H
#define L01_BST_H
#include <stdio.h>
#include "Item.h"

typedef struct binarysearchtree *BST;

BST BSTinit();
BST BSTreadPreorder(FILE *);
void BSTwritePreorder(BST,FILE *);
int BSTcount(BST,int,int);
int BSTdistance(BST, Key,Key);
void BSTmirror(BST);
void BSTfree(BST);



#endif //L01_BST_H
