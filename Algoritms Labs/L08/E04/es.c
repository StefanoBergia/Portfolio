#include "es.h"

esercizio_p crea_esercizio(){
    esercizio_p  new=(esercizio_p)malloc(sizeof(esercizio_t));
    new->tipoEs[0]='\0';
    new->catEs[0]='\0';
    new->nomeEs[0]='\0';
    return new;
}

void distruggi_esercizio(esercizio_p es){
    if(es!=NULL)
        free(es);
}

esercizio_p input_esercizio(FILE *fp){
    esercizio_p new=crea_esercizio();
    if(fp!=NULL)
        fscanf(fp,"%s %s %s",new->nomeEs,new->catEs,new->tipoEs);
    return new;
}

void output_esercizio(esercizio_p es,FILE *fp){
    if(fp!=NULL)
        fprintf(fp,"%s %s %s",es->nomeEs,es->catEs,es->tipoEs);
}