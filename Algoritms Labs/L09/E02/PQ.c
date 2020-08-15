#include <stdlib.h>
#include <memory.h>
#include "Item.h"
#include "PQ.h"

struct pqueue{
    Item_p A;
    int heapsize;
};

int LEFT(int i){ return (i*2+1);}
int RIGHT(int i){return (i*2+2);}
int PARENT(int i){return (i-1)/2;}

void Swap(PQ pq,int pos1, int pos2){
    Item supp=pq->A[pos1];
    pq->A[pos1]=pq->A[pos2];
    pq->A[pos2]=supp;
}

void HEAPify(PQ pq, int i){
    int l,r,lowest;
    l=LEFT(i);
    r=RIGHT(i);
    if((l<pq->heapsize)&& (ITEMless(pq->A[l],pq->A[i])))
        lowest=l;
    else
        lowest=i;
    if((r<pq->heapsize)&& (ITEMless(pq->A[r],pq->A[lowest])))
        lowest=r;
    if(lowest!=i){
        Swap(pq,i,lowest);
        HEAPify(pq,lowest);
    }
    return;

}

void HEAPbuild(PQ pq){
    int i;
    for(i=(pq->heapsize/2-1);i>=0;i--)
        HEAPify(pq,i);
    return;;
}

PQ PQUEUEinit(int maxN){
    PQ pq;
    pq=malloc(sizeof(*pq));
    pq->A=(Item *)malloc(maxN*sizeof(Item));
    pq->heapsize=0;
    return pq;
}

int PQUEUEempty(PQ pq){
    return pq->heapsize==0;
}

void PQUEUEinsert(PQ pq,Item item){
    int i;
    i=pq->heapsize++;
    while((i>=1)&& (ITEMGreater(pq->A[PARENT(i)],item))){
        pq->A[i]=pq->A[PARENT(i)];
        i=(i-1)/2;
    }
    pq->A[i]=item;
    return;
}


Item PQUEUEextractMin(PQ pq){
    Item item;
    Swap(pq,0,pq->heapsize-1);
    item=pq->A[pq->heapsize-1];
    pq->heapsize--;
    HEAPify(pq,0);
    return item;

}

Item PQUEUEshowMin(PQ pq){
    return  pq->A[0];
}

void PQUEUEdisplay(PQ pq){
    int i;
    for(i=0;i<pq->heapsize;i++)
        ItemPrint(&(pq->A[i]),stdout);
}

int PQUEUEsize(PQ pq){
    return pq->heapsize;
}

void PQUEUEchange(PQ pq,int pos,Item item){
    while((pos>=1)&& (ITEMGreater(pq->A[PARENT(pos)],item))){
        pq->A[pos]=pq->A[PARENT(pos)];
        pos=(pos-1)/2;
    }
    pq->A[pos]=item;
    HEAPify(pq,pos);
    return;
}

int PQLinearSearch(PQ pq,char * nome){
    int i;
    for(i=0;i<pq->heapsize;i++)
        if(strcmp(pq->A[i].nome,nome)==0)
            return i;
    return -1;
}

void PQRemove(PQ pq,int pos){
    if(pos>=0){
        pq->heapsize--;
        Swap(pq,pos,pq->heapsize);
        HEAPify(pq,pos);
    }
}

void PQRead(PQ pq,FILE * fp){
    Item_p new;
    new=IteamScan(fp);
    while (!ItemCheckVoid(new)){
        PQUEUEinsert(pq,*new);
        ItemFree(new);
        new=IteamScan(fp);
    }
    ItemFree(new);
}

void PQWrite(PQ pq,FILE * fp){
    int i;
    for(i=0;i<pq->heapsize;i++)
        ItemPrint(&(pq->A[i]),fp);
}

void PQfree(PQ pq){
    int i=0;
    for(i=0;i<pq->heapsize;i++,pq->A++)
        ItemFree(pq->A);
    free(pq);
}

PQ PQcpy(PQ pq){
    PQ new=PQUEUEinit(pq->heapsize);
    new->heapsize=pq->heapsize;
    int i;
    for(i=0;i<pq->heapsize;i++)
        new->A[i]=pq->A[i];
    return new;
}

void PQShowRank(PQ pq){
    int i;
    PQ sup=PQcpy(pq);
    while(sup->heapsize>0)
        PQUEUEextractMin(sup);
    for(i=0;i<pq->heapsize;i++)
        printf("Posizione %d: %s %d punti\n",i+1,ItemGetNome(&sup->A[i]),ItemGetPunti(&sup->A[i]));
    PQfree(sup);
}