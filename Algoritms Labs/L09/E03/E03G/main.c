#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>

#define MAXC 35

typedef enum {NA, AA, AI} categoria;

typedef struct{
    char nome[MAXC+1];
    float punteggio;
    int diff;
    categoria cat;
    float p_su_d;

    int flag;
}Elemento;

typedef struct{
    int maxNA;
    int maxAA;
    int maxAI;

    int maxTOT;
}Atleta;

Elemento ** LeggiFile(int* n,FILE * fp);
float calcolaPunteggio(Elemento **sol,int k);
void MergeSort(Elemento **,int ,int);
void MergeSortR(Elemento **,Elemento **,int ,int,int);
void Merge(Elemento **, Elemento **,int,int,int,int);
int less(Elemento *,Elemento *, int);
int eq(Elemento *,Elemento *, int);
int greedy(Elemento ** ,Elemento **  ,int ,int ,Atleta);
int checkDif(Elemento *,Atleta);
void add_bonus(Elemento **,int,categoria);
void remove_bonus(Elemento **,int);
void add_bonus_2(Elemento **  ,int ,categoria );

char * CatToString(categoria cat){
    char * ret=malloc(MAXC+1);
    switch(cat){
        case NA:
            strcpy(ret,"non acrobatico");
            break;
        case AA:
            strcpy(ret,"acrobatico avanti");
            break;
        case AI:
            strcpy(ret,"acrobatico indietro");
            break;
    }
    return ret;
}

int main(int argc, char ** argv) {
    FILE * fp;
    Elemento ** elementi,** sol;
    Atleta at;
    int n,i,l;
    if(argc==6){
        fp=fopen(argv[1],"r");
        elementi=LeggiFile(&n,fp);
        fclose(fp);

        at.maxNA=atoi(argv[2]);
        at.maxAA=atoi(argv[3]);
        at.maxAI=atoi(argv[4]);
        at.maxTOT=atoi(argv[5]);

        sol=malloc(8*sizeof(Elemento *));

        l=greedy(elementi,sol,n,8,at);
        for(i=0;i<l;i++)
            printf("%s %s %f %d\n",sol[i]->nome,CatToString(sol[i]->cat),sol[i]->punteggio,sol[i]->diff);
        printf("\n il punteggio totale è %f",calcolaPunteggio(sol,8));

    }
    return 0;
}


Elemento ** LeggiFile(int* n,FILE * fp){
    Elemento ** dati;
    int na,aa,ai,tot,i;
    fscanf(fp,"%d %d %d",&na,&aa,&ai);
    tot=na+aa+ai;
    dati=malloc(tot*sizeof(Elemento *));
    for(i=0;i<tot;i++)
        dati[i]=malloc(sizeof(Elemento));
    aa+=na;
    ai+=aa;
    for(i=0;i<tot;i++){
        fscanf(fp,"%s %d %f",dati[i]->nome,&dati[i]->diff,&dati[i]->punteggio);
        if(i<na)
            dati[i]->cat=NA;
        else if(i<aa)
            dati[i]->cat=AA;
        else if(i<ai)
            dati[i]->cat=AI;
        dati[i]->flag=0;
        dati[i]->p_su_d=dati[i]->punteggio/dati[i]->diff;
    }
    *n=tot;
    return dati;
}

float calcolaPunteggio(Elemento **sol,int k){
    float sum;
    int flags[4],i;
    for(i=0,sum=0;i<k-1;i++){

        if(sol[i]->flag==0){
            flags[sol[i]->cat]=1;
            sum+=sol[i]->punteggio;
            sol[i]->flag=1;
        }
    }

    if((flags[0]+flags[1]+flags[2])>=2) {
        sum += 2.5;
        flags[3]=1;
    }


    if(sol[i]->flag==0){
        flags[sol[i]->cat]=1;
        sum+=sol[i]->punteggio;
    }

    if(!flags[3] && (flags[0]+flags[1]+flags[2])>=2) {
        sum += 2.5;
        flags[3]=2;
    }

    if(flags[3]!=2 && (sol[i]->cat==AA || sol[i]->cat==AI) && sol[i]->diff>=5)
        sum+=2.5;

    for(i=0;i<k;i++)
        sol[i]->flag=0;

    return sum;
}

int checkDif(Elemento *new,Atleta at){
    int i=0;
    switch (new->cat){
        case NA:
            if(at.maxNA<new->diff)
                return 0;
            break;
        case AA:
            if(at.maxAA<new->diff)
                return 0;
            break;
        case AI:
            if(at.maxAI<new->diff)
                return 0;
            break;
    }
    return 1;
}

void MergeSort(Elemento ** elementi,int N,int tipo){
    int l=0,r=N-1,i;
    Elemento ** sup=malloc(N*sizeof(Elemento *));
    for(i=0;i<N;i++)
        sup[i]=malloc(sizeof(Elemento));
    MergeSortR(elementi,sup,l,r,tipo);
    free(sup);
}

void MergeSortR(Elemento ** elementi ,Elemento ** sup,int l,int r,int tipo){
    int q=(l+r)/2;
    if(r<=l)
        return;
    MergeSortR(elementi,sup,l,q,tipo);
    MergeSortR(elementi,sup,q+1,r,tipo);
    Merge(elementi,sup,l,q,r,tipo);
}
void Merge(Elemento ** A, Elemento ** B,int l,int q,int r,int tipo){
    int i,j,k;
    i=l;
    j=q+1;
    for(k=l;k<=r;k++) {
        if (i > q)
            B[k] = A[j++];
        else if (j > r)
            B[k] = A[i++];
        else if (less(A[i], A[j], tipo) || eq(A[i], A[j], tipo))
            B[k] = A[i++];
        else
            B[k] = A[j++];
    }
    for(k=l;k<=r;k++)
        A[k]=B[k];
    return;
}

int less(Elemento * el1,Elemento * el2, int tipo){
    if(tipo)
        return el1->diff>el2->diff; //////attenzione
    else
        return  el1->p_su_d<el2->p_su_d;
}

int eq(Elemento * el1,Elemento  * el2, int tipo){
    if(tipo)
        return 0;
    else
        return  el1->p_su_d==el2->p_su_d;
}

int greedy(Elemento ** elementi,Elemento ** sol ,int n,int k,Atleta at){
    int i,best=n-1,bonus1=0,bonus2=0,j;
    MergeSort(elementi,n,1);
    MergeSort(elementi,n,0);
    for(i=0;i<k;i++){
        sol[i]=elementi[best];
        if(sol[i]->p_su_d==-1)
            return i;
        if(sol[i]->diff<=at.maxTOT/(k-1) && at.maxTOT>sol[i]->diff && checkDif(sol[i],at)){
            sol[i]->p_su_d=0;
            sol[i]->flag=1;
            at.maxTOT-=sol[i]->diff;
            if(i==k-2)
                add_bonus_2(elementi,n,NA);
            if(bonus1==0){
                add_bonus(elementi,n,elementi[best]->cat);
                bonus1=1;
                bonus2=1;
            } else if(bonus2==1){
                remove_bonus(elementi,n);
                bonus2=0;
            }
        }else
        {
            elementi[best]->p_su_d=-1;
            elementi[best]->flag=-1;
            i--;
        }

        MergeSort(elementi,n,1);
        MergeSort(elementi,n,0);

    }
    for(i=0;i<n;i++)
        elementi[i]->flag=0;
    return k;
}

void add_bonus(Elemento ** elementi ,int n,categoria cat){
    int i;
    for(i=0;i<n;i++){
        if(elementi[i]->flag==0 && elementi[i]->cat!=cat) {
            elementi[i]->p_su_d = (2.5 + elementi[i]->punteggio) / (float)elementi[i]->diff;
            elementi[i]->flag=2;
        }
    }
}

void remove_bonus(Elemento ** elementi,int n){
    int i;
    for(i=0;i<n;i++){
        if(elementi[i]->flag==2 ) {
            elementi[i]->p_su_d = (elementi[i]->punteggio) /(float) elementi[i]->diff;
            elementi[i]->flag=0;
        }
    }
}

void add_bonus_2(Elemento ** elementi ,int n,categoria cat){
    int i;
    for(i=0;i<n;i++){
        if(elementi[i]->flag==0 && elementi[i]->cat!=cat && elementi[i]->diff>=5) {
            elementi[i]->p_su_d =((elementi[i]->p_su_d * elementi[i]->diff) + 2.5 ) / elementi[i]->diff;
            elementi[i]->flag=2;
        }
    }
}