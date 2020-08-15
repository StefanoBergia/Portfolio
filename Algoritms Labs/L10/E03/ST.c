#include <malloc.h>
#include <memory.h>
#include "ST.h"

#include "Item.h"

struct symboltable{
    Item *a;
    int N;
    int M;
};

ST STinit(int maxN){
    int i;
    ST st=malloc(sizeof(*st));
    st->N=0;
    st->M=maxN;

    st->a=malloc(st->M*sizeof(Item));
    for(i=0;i<st->M;i++)
        st->a[i]=ITEMSetVoid();
    return st;
}

int hash(char * k,int M){
    int h=0, base=127;
    for(;*k!='\0';k++)
        h=(base*h+*k)%M;
    return h;
}

int STcount(ST st){
    return  st->N;
}

int STempty(ST st){
    if(STcount(st)==0)
        return 1;
    else
        return 0;
}

int full(ST st,int i){              ////////////////OCCHIO
    if(ITEMIsVoid(st->a[i]))
        return 0;
    else
        return 1;
}

void STdisplay(ST st){
    int i;
    for(i=0;i<st->M;i++){
        if(!ITEMIsVoid(st->a[i])) {
            ITEMshow(st->a[i]);
            printf("\n");
        }
    }
}

void STinsert(ST st,Item item){

    int i=hash(item.id_elab,st->M);
    while(full(st,i))
        i=(i+1)%st->M;
    st->a[i]=item;
    st->a[i].id=i;
    st->N++;
}

Item STsearch(ST st,char * k){
    int i=hash(k,st->M);
    while(full(st,i))
        if(strcmp(k,st->a[i].id_elab)==0)
            return st->a[i];
        else
            i=(i+1)%st->M;
    return  ITEMSetVoid();
}

void STdelete(ST st, char * k){
    int j,i=hash(k,st->M);
    Item tmp;
    while(full(st,i))
        if(strcmp(k,KEYget(st->a[i]))==0)
            break;
        else
            i=(i+1)%st->M;
    if(ITEMIsVoid(st->a[i]))
        return;;
    st->a[i]=ITEMSetVoid();
    st->N--;
    for(j=i+1,full(st,j);j=(j+1)%st->M;st->N--){
        tmp=st->a[j];
    }
}

Item STGet(ST st,int id){
    return st->a[id];
}