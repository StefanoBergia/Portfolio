#include "esercizi.h"

tabEser * leggiFileEs(FILE *fp){
    tabEser * ret;
    int i;
    ret=(tabEser *)malloc(sizeof(tabEser));
    fscanf(fp,"%d",&ret->nEser);
    ret->vettEs=(esercizio_t *)malloc(ret->nEser*sizeof(esercizio_t));
    for(i=0;i<ret->nEser;i++){
        fscanf(fp,"%s %s %s",ret->vettEs[i].nomeEs,ret->vettEs[i].catEs,ret->vettEs[i].tipoEs);
    }
    return ret;
}

esercizio_t * ricerca_lineareEs(tabEser *tab, char * nome){
    int i;
    for(i=0;i<tab->nEser;i++)
        if(strcmp(tab->vettEs[i].nomeEs,nome)==0)
            return &(tab->vettEs[i]);
    return NULL;
}

void stampa_esercizi(tabEser * tab){
    int i;
    for(i=0;i<tab->nEser;i++)
        printf("%s %s %s\n",tab->vettEs[i].nomeEs,tab->vettEs[i].catEs,tab->vettEs[i].tipoEs);
}