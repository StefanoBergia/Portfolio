#ifndef E02_BST_H
#define E02_BST_H
#include "Utente.h"

typedef struct binarysearchtree *BST;
typedef Utente Item;

BST BSTinit();
void BSTinsert(BST,Item *);
Item * BST_search(BST, char *);
void BST_print(BST);


#endif
