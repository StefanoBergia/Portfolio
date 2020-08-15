#ifndef E03_ESERCIZI_H
#define E03_ESERCIZI_H

#include <stdio.h>
#include <malloc.h>
#define MAXC 25

typedef struct es esercizio_t;

struct es{
    char nomeEs[MAXC+1];
    char catEs[MAXC+1];
    char tipoEs[MAXC+1];
};

typedef struct {
    esercizio_t * vettEs;
    int nEser;
}tabEser;

tabEser * leggiFileEs(FILE *fp);
esercizio_t * ricerca_lineareEs(tabEser *tab, char * nome);
void stampa_esercizi(tabEser * tab);

#endif //E03_ESERCIZI_H
