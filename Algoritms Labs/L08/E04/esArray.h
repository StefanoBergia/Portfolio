#ifndef E04_ESARRAY_H
#define E04_ESARRAY_H

#include "es.h"
#include <string.h>

typedef struct tabEser esArray;
typedef struct tabEser * esArray_p;

struct tabEser{
    esercizio_p vettEs;
    int nEser;
};

esArray_p crea_esArray();
void  distruggi_esArray(esArray_p array);
esercizio_p ricerca_es(esArray_p array, char * nome_es);
void set_nome(esArray_p array,char * old_name,char * nome);
void set_categoria(esArray_p array,char * nome,char * cat);
void set_tipo(esArray_p array,char * nome, char * tipo);
char * get_categoria(esArray_p array,char * nome);
char * get_tipo(esArray_p array,char * nome);
int get_nEser(esArray_p array);
void leggi_esArray(esArray_p array,FILE *fp);
void scrivi_Array(esArray_p array, FILE *fp);

#endif //E04_ESARRAY_H
