#include <malloc.h>
#include <memory.h>
#include "ST.h"
#define MAXC 30

struct symboltable{
    char **a;
    int * eliminated;
    int N;
    int M;
};

ST STinit(int maxN){
    int i;
    ST st=malloc(sizeof(*st));
    st->N=0;
    st->M=maxN;
    st->a=malloc(st->M*sizeof(char *));
    st->eliminated=calloc(st->M,sizeof(int));
    for(i=0;i<st->M;i++)
        st->a[i]=NULL;
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

int full(ST st,int i){
    if(st->a[i]==NULL)
        return 0;
    else
        return 1;
}

void STinsert(ST st,char * item){

    int i=hash(item,st->M);
    while(full(st,i))
        i=(i+1)%st->M;
    st->a[i]=malloc((MAXC+1)*sizeof(char));
    strcpy(st->a[i],item);
    st->N++;
}

int STsearch(ST st,char * k){
    int i=hash(k,st->M);
    while(full(st,i))
        if(strcmp(k,st->a[i])==0) {
                return i;
        }
        else
            i=(i+1)%st->M;
    return  -1;
}

void STdelete(ST st, char * k){
    int i=STsearch(st,k);
    if(i!=-1)
        st->eliminated[i]=1;
}

char * STGet(ST st,int id){
    char * ret=NULL;
    if(id<st->M && st->a[id]!=NULL){
        ret=malloc((MAXC+1)*sizeof(char));
        strcpy(ret,st->a[id]);
    }
    return ret;
}

ST STcopy(ST st){
    ST new=STinit(st->M);
    new ->N=st->N;
    int i;
    for(i=0;i<st->M;i++) {
        if(st->a[i]!=NULL) {
            new->a[i] = malloc((MAXC + 1) * sizeof(char));
            strcpy(new->a[i],st->a[i]);
        }
    }
    return new;
}

int STisEliminated(ST st, int id){
    return st->eliminated[id];
}