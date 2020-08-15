#ifndef E04_ESLIST_H
#define E04_ESLIST_H

#include "es.h"
#include "esArray.h"

typedef struct esp_l eserPiano_l;
typedef struct esp_l * eserPiano_lp;
typedef struct esp eserPiano_t;
typedef struct esp * eserPiano_p;


struct esp_l{
    int nEs;
    eserPiano_p head;
    eserPiano_p tail;
};

struct esp{
    esercizio_p es;
    int set;
    int rip;
    eserPiano_p next;
};

eserPiano_lp crea_listaEs();
void distruggi_listaEs(eserPiano_lp lista);
void add_esPiano(eserPiano_lp lista,eserPiano_p piano);
void removeEserPiano(eserPiano_lp lista, eserPiano_p piano);
eserPiano_p ricerca_eserPiano(eserPiano_lp lista,char * nome_es);
void set_ripetizioni(eserPiano_lp lista,char * nome_es,int rip);
void set_setr(eserPiano_lp lista,char * nome_es,int set);
void set_es(eserPiano_lp lista,char *nome,esercizio_p esp);
int get_ripetizioni(eserPiano_lp lista,char * nome_es);
int get_setr(eserPiano_lp lista,char * nome_es);
int get_nEs(eserPiano_lp lista);
void leggi_esPiano(eserPiano_lp lista,esArray_p  array,FILE *fp);
void scrivi_esPiano(eserPiano_lp lista,FILE *fp);

#endif //E04_ESLIST_H
