#include <memory.h>
#include <malloc.h>
#include "Utente.h"

Utente * New(char * cardID,int n){
    Utente * ret=malloc(sizeof(*ret));
    strcpy(ret->cardID,cardID);
    ret->stazioni=calloc(n,sizeof(int));
    ret->inizio=0;
    ret->fine=0;
    ret->flag=0;
    ret->n=n;
    return  ret;
}

Utente * ItemSetVoid(){
    return New("",0);
}

int ITEMCompare(Utente * u1,Utente *u2){
    return  strcmp(u1->cardID,u2->cardID);
}

void ITEMprint(Utente * utente){
    int i;
    printf("cardID:%s\n",utente->cardID);
    if(utente->flag)
        printf("noleggio in corso\n");
    for(i=0;i<utente->n;i++){
        printf("%d:%d ",i,utente->stazioni[i]);
    }
    printf("\n");
}