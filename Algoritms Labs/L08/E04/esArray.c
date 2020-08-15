#include "esArray.h"

esArray_p crea_esArray(){
    esArray_p array=(esArray_p)malloc(sizeof(esArray));
    array->vettEs=NULL;
    array->nEser=0;
}


void  distruggi_esArray(esArray_p array){
    int i;
    for(i=0;i<array->nEser;i++){
        free(array->vettEs[i].tipoEs);
        free(array->vettEs[i].catEs);
        free(array->vettEs[i].nomeEs);
    }
    free(array->vettEs);
    free(array);
}

esercizio_p ricerca_es(esArray_p array, char * nome_es){
    int i=0;
    for(i=0;i<array->nEser;i++)
        if(strcmp(array->vettEs[i].nomeEs,nome_es)==0)
            return &array->vettEs[i];
    return NULL;
}

void set_nome(esArray_p array,char * old_name,char * nome){
    esercizio_p es=ricerca_es(array,old_name);
    strcpy(es->nomeEs,nome);
}
void set_categoria(esArray_p array,char * nome,char * cat){
    esercizio_p  es=ricerca_es(array,nome);
    strcpy(es->catEs,cat);
}

void set_tipo(esArray_p array,char * nome, char * tipo){
    esercizio_p  es=ricerca_es(array,nome);
    strcpy(es->tipoEs,tipo);
}

char * get_categoria(esArray_p array,char * nome){
    esercizio_p  es=ricerca_es(array,nome);
    return es->catEs;
}

char * get_tipo(esArray_p array,char * nome){
    esercizio_p  es=ricerca_es(array,nome);
    return es->tipoEs;
}

int get_nEser(esArray_p array){
    return  array->nEser;
}

void leggi_esArray(esArray_p array,FILE *fp){
    int i;
    fscanf(fp,"%d",&array->nEser);
    array->vettEs=(esercizio_t *)malloc(array->nEser*sizeof(esercizio_t));
    for(i=0;i<array->nEser;i++){
        fscanf(fp,"%s %s %s",array->vettEs[i].nomeEs,array->vettEs[i].catEs,array->vettEs[i].tipoEs);
    }
}

void scrivi_Array(esArray_p array, FILE *fp){
    int i;
    for(i=0;i<get_nEser(array);i++)
        fprintf(fp,"%s %s %s\n",array->vettEs[i].nomeEs,array->vettEs[i].catEs,array->vettEs[i].tipoEs);
}