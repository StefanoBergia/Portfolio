//
// Created by stefano on 27/12/17.
//

#ifndef L01_ITEM_H
#define L01_ITEM_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAXC 10

typedef struct {
    char nome[MAXC+1];
    int val;
    int dx;
    int sx;
}Item;

typedef char * Key;
typedef Item * Item_p;

Item_p ItemNew();
void ItemFree(Item_p);
Key KeyGet(Item_p);
int KeyCompare(Key a, Key b);
int ItemCompare(Item_p a, Item_p b);
Item_p Itemscan(FILE *);
void ItemShow(Item_p ,FILE *);
Item_p ItemSetVoid();
int ItemCheckVoid(Item_p);
int GetVal(Item_p);
void ItemSetVal(Item_p,int );
void ItemSetKey(Item_p, Key);
int ItemGetDx(Item_p);
int ItemGetSx(Item_p);
void  ItemSetDx(Item_p,int );
void  ItemSetSx(Item_p, int );

#endif //L01_ITEM_H
