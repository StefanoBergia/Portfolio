#include <malloc.h>
#include "PQ.h"

struct pqueue{
    int * A;
    int heapsize;
};

int LEFT(int i){ return (i*2+1);}
int RIGHT(int i){return (i*2+2);}
int PARENT(int i){return (i-1)/2;}

void Swap(PQ pq,int pos1, int pos2){
    int supp=pq->A[pos1];
    pq->A[pos1]=pq->A[pos2];
    pq->A[pos2]=supp;
}

void HEAPify(PQ pq,int * d, int i){
    int l,r,lowest;
    l=LEFT(i);
    r=RIGHT(i);
    if((l<pq->heapsize)&& d[pq->A[l]]<d[pq->A[i]])
        lowest=l;
    else
        lowest=i;
    if((r<pq->heapsize)&& d[pq->A[r]]<d[pq->A[lowest]])
        lowest=r;
    if(lowest!=i){
        Swap(pq,i,lowest);
        HEAPify(pq,d,lowest);
    }
    return;

}

void HEAPbuild(PQ pq, int * d){
    int i;
    for(i=(pq->heapsize/2-1);i>=0;i--)
        HEAPify(pq,d,i);
    return;;
}

PQ PQUEUEinit(int maxN){
    PQ pq;
    pq=malloc(sizeof(*pq));
    pq->A=(int *)malloc(maxN*sizeof(int));
    pq->heapsize=0;
    return pq;
}

void PQUEUEinsert(PQ pq,int *d,int v){
    int i;
    i=pq->heapsize++;
    while((i>=1)&& d[pq->A[PARENT(i)]]>d[v]){
        pq->A[i]=pq->A[PARENT(i)];
        i=(i-1)/2;
    }
    pq->A[i]=v;
    return;
}

int PQUEUEextractMin(PQ pq,int * d){
    int v;
    Swap(pq,0,pq->heapsize-1);
    v=pq->A[pq->heapsize-1];
    pq->heapsize--;
    HEAPify(pq,d,0);
    return v;
}

void PQUEUEchange(PQ pq,int v,int *d){
    int pos;
    for(pos=0;pos<pq->heapsize;pos++)
    {
        if(pq->A[pos]==v)
            break;
    }
    int tmp=pq->A[pos];
    while((pos>=1)&& d[pq->A[PARENT(pos)]]>d[tmp]){
        pq->A[pos]=pq->A[PARENT(pos)];
        pos=(pos-1)/2;
    }
    pq->A[pos]=tmp;
    HEAPify(pq,d,pos);
    return;
}

int PQUEUEempty(PQ pq){
    if(pq->heapsize>0)
        return 0;
    return 1;
}