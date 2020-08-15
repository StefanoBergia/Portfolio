#ifndef L02_PQ_H
#define L02_PQ_H
#include "Item.h"

typedef struct pqueue *PQ;

PQ PQUEUEinit(int);
int PQUEUEempty(PQ);
void PQUEUEinsert(PQ,Item);
Item PQUEUEextractMin(PQ);
Item PQUEUEshowMin(PQ pq);
void PQUEUEdisplay(PQ);
int PQUEUEsize(PQ);
void PQUEUEchange(PQ,int,Item);


int PQLinearSearch(PQ,char *);
void PQRemove(PQ,int);
void PQRead(PQ,FILE *);
void PQWrite(PQ,FILE *);
void PQfree(PQ);
PQ PQcpy(PQ);
void PQShowRank(PQ);

#endif //L02_PQ_H
