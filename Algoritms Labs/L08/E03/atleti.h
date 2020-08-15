#ifndef E03_ATLETI_H
#define E03_ATLETI_H

#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "esercizi.h"

#define MAXC 25

typedef  struct at atleta_t;
typedef struct esp eserPiano_t;

struct at{
    char codice[5+1];
    char nome[MAXC+1];
    char cognome[MAXC+1];
    char categoria[MAXC +1];
    char data[10+1];
    int ore;

    char *chiave;
    int flag;


    atleta_t * next;
    eserPiano_t *head;
    eserPiano_t *tail;
} ;

typedef struct{
    int nAtleti;
    atleta_t * head;
    atleta_t * tail;
}tabAtleti;

struct esp{
    esercizio_t * es;
    int set;
    int rip;
    eserPiano_t * next;
};

tabAtleti * leggiFile(FILE *fp);
void listAdd(tabAtleti *tab, atleta_t * new);
void listPrint(tabAtleti * tab,FILE * fp );
void listDelete(tabAtleti *tab,atleta_t * del);
void setChiaveCodice(tabAtleti * atleti);
void setChiaveCognome(tabAtleti * atleti);
void setChiaveNome(tabAtleti * atleti);
void setChiaveCategoria(tabAtleti * atleti);
void ricerca_lineare(tabAtleti *tab, char * chiave, int p,int f);
atleta_t * ricerca_lineare2(tabAtleti *tab, char * codice);
esercizio_t * ricerca_lineareEs(tabEser *tab, char * nome);
void leggiFileEsP(tabEser * tab, atleta_t * atleta);
void freeEsP(atleta_t * a);
void freeAt(tabAtleti * tab);
void modifica_set_rip(tabAtleti *tab,char * codice, char *nomeEs,int set, int rip);
void aggiorna_monte_ore(tabAtleti * tab,char * codice,int n_ore);
void stampa_es(atleta_t * at,FILE *fp);


#endif //E03_ATLETI_H
