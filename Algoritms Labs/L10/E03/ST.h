#ifndef E03_ST_H
#define E03_ST_H

#include "Item.h"
typedef struct symboltable *ST;

ST STinit(int);
void STinsert(ST,Item);
int STcount(ST);
int STempty(ST);
Item STsearch(ST,char *);
void STdelete(ST,char *);
void STdisplay(ST st);
Item STGet(ST st,int id);

#endif //E03_ST_H
