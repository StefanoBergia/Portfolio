#ifndef L02_ITEM_H
#define L02_ITEM_H
#include <stdio.h>
#define MAXC 10

typedef struct player Item;
typedef struct player * Item_p;

struct player{
    char nome[MAXC+1];
    int punti;

    int void_flag;
};

Item_p ItemNew();
void ItemFree(Item_p);
Item_p ItemSetVoid();
int ItemCheckVoid(Item_p);
int ItemGetPunti(Item_p);
char * ItemGetNome(Item_p);
void ItemSetPunti(Item_p,int);
void ItemSetNome(Item_p, char *);
Item_p  IteamScan(FILE *);
void ItemPrint(Item_p,FILE *);
int ITEMless(Item,Item);
int ITEMGreater(Item,Item);

Item_p ItemMatch(Item_p,Item_p);

#endif //L02_ITEM_H
