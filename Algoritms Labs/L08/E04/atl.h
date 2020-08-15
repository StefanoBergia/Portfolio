#ifndef E04_ATL_H
#define E04_ATL_H

#include <stdio.h>
#include <malloc.h>
#include "esList.h"
#define MAXC 25

typedef  struct at atleta_t;
typedef  struct at * atleta_p;

struct at{
    char codice[5+1];
    char nome[MAXC+1];
    char cognome[MAXC+1];
    char categoria[MAXC +1];
    char data[10+1];
    int ore;

    char *chiave;
    int flag;


    atleta_p next;
    eserPiano_lp  esercizi;
} ;



atleta_p crea_atleta();
void distruggi_atleta(atleta_p);
atleta_p input_atleta(FILE *fp);
void output_atleta(atleta_p at ,FILE *fp,int print_pianoEs);

#endif //E04_ATL_H
