//
// Created by stefano on 17/12/17.
//
#ifndef E04_ES_H
#define E04_ES_H

#include <stdio.h>
#include <malloc.h>

#define MAXC 25

typedef struct es esercizio_t;
typedef struct es * esercizio_p;

struct es{
    char nomeEs[MAXC+1];
    char catEs[MAXC+1];
    char tipoEs[MAXC+1];
};

esercizio_p crea_esercizio();
void distruggi_esercizio(esercizio_p);
esercizio_p input_esercizio(FILE *fp);
void output_esercizio(esercizio_p ,FILE *fp);

#endif //E04_ES_H
