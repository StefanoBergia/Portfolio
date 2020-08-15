#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <values.h>
#include <stdlib.h>

#define MAXC 35

typedef enum {NA, AA, AI} categoria;

typedef struct{
    char nome[MAXC+1];
    float punteggio;
    int diff;
    categoria cat;

    int flag;
}Elemento;

typedef struct{
    int maxNA;
    int maxAA;
    int maxAI;

    int maxTOT;
}Atleta;

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

Elemento * LeggiFile(int* n,FILE * fp);
void combR(int pos,int * sol,int n,int k,int start,float * max,int * best_sol,Elemento* elementi,Atleta at);
float calcolaPunteggio(Elemento* elementi,int *sol,int n);
int checkDif(int *sol,int n,Elemento* elementi,Atleta at);

int main(int argc, char ** argv) {
    FILE * fp;
    Elemento * elementi;
    Atleta at;
    int * sol,*bstsol,n,i;
    float sum=MINFLOAT;
    if(argc==6){
        fp=fopen(argv[1],"r");
        elementi=LeggiFile(&n,fp);
        fclose(fp);

        at.maxNA=atoi(argv[2]);
        at.maxAA=atoi(argv[3]);
        at.maxAI=atoi(argv[4]);
        at.maxTOT=atoi(argv[5]);

        sol=malloc(8*sizeof(int));
        bstsol=malloc(8*sizeof(int));
        combR(0,sol,n,8,0,&sum,bstsol,elementi,at);

        for(i=0;i<8;i++)
            printf("%s %s %f %d\n",elementi[bstsol[i]].nome,CatToString(elementi[bstsol[i]].cat),elementi[bstsol[i]].punteggio,elementi[bstsol[i]].diff);
        printf("\n il punteggio totale è %f",sum);

    }
    return 0;
}

Elemento * LeggiFile(int* n,FILE * fp){
    Elemento * dati;
    int na,aa,ai,tot,i;
    fscanf(fp,"%d %d %d",&na,&aa,&ai);
    tot=na+aa+ai;
    dati=malloc(tot*sizeof(Elemento));
    aa+=na;
    ai+=aa;
    for(i=0;i<tot;i++){
        fscanf(fp,"%s %d %f",dati[i].nome,&dati[i].diff,&dati[i].punteggio);
        if(i<na)
            dati[i].cat=NA;
        else if(i<aa)
            dati[i].cat=AA;
        else if(i<ai)
            dati[i].cat=AI;
        dati[i].flag=0;
    }
    *n=tot;
    return dati;
}

void combR(int pos,int * sol,int n,int k,int start,float * max,int * best_sol,Elemento* elementi,Atleta at){
    int i;
    float sum;
    if(pos>=k){
        sum=calcolaPunteggio(elementi,sol,k);
        if(sum>*max){
            *max=sum;
            for(i=0;i<k;i++)
                best_sol[i] = sol[i];;
        }
        return;
    }
    //ultimo elemento: disposizioni ripetute
    if(pos==k-1){
        for(i=0;i<n;i++){
            sol[pos]=i;
            if(checkDif(sol,pos+1,elementi,at)>0)
                combR(pos+1,sol,n,k,start,max,best_sol,elementi,at);
        }
        return;
    }

    //elementi da 1 a 7: combinazioni con ripetizione
    for(i=start;i<n;i++){
        sol[pos]=i;
        if(checkDif(sol,pos+1,elementi,at)>0) {
            combR(pos + 1, sol, n, k, start, max, best_sol, elementi, at);
            start++;
        }
    }
}
float calcolaPunteggio(Elemento * elementi,int *sol,int n){
    float sum;
    int flags[4],i;
    for(i=0,sum=0;i<n-1;i++){

        if(elementi[sol[i]].flag==0){
            flags[elementi[sol[i]].cat]=1;
            sum+=elementi[sol[i]].punteggio;
            elementi[sol[i]].flag=1;
        }
    }

    if((flags[0]+flags[1]+flags[2])>=2) {
        sum += 2.5;
        flags[3]=1;
    }


    if(elementi[sol[i]].flag==0){
        flags[elementi[sol[i]].cat]=1;
        sum+=elementi[sol[i]].punteggio;
    }

    if(!flags[3] && (flags[0]+flags[1]+flags[2])>=2) {
        sum += 2.5;
        flags[3]=2;
    }

    if(flags[3]!=2 && (elementi[sol[i]].cat==AA || elementi[sol[i]].cat==AI) && elementi[sol[i]].diff>=5)
        sum+=2.5;

    for(i=0;i<n;i++)
        elementi[sol[i]].flag=0;

    return sum;
}

int checkDif(int *sol,int n,Elemento* elementi,Atleta at){
    int i=0;
    for(i=0;i<n;i++){
        at.maxTOT-=elementi[sol[i]].diff;
        if(at.maxTOT<0)
            return 0;
        switch (elementi[sol[i]].cat){
            case NA:
                if(at.maxNA<elementi[sol[i]].diff)
                    return 0;
                break;
            case AA:
                if(at.maxAA<elementi[sol[i]].diff)
                    return 0;
                break;
            case AI:
                if(at.maxAI<elementi[sol[i]].diff)
                    return 0;
                break;
        }
    }
    return 1;
}

