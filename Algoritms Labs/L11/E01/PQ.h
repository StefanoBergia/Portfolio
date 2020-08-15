#ifndef E01_PQ_H
#define E01_PQ_H

typedef struct pqueue *PQ;

PQ PQUEUEinit(int);
int PQUEUEempty(PQ);
void PQUEUEinsert(PQ,int *,int);
int PQUEUEextractMin(PQ,int *);
void PQUEUEchange(PQ,int,int *);

#endif //E01_PQ_H
