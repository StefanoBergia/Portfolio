#ifndef E04_ATLLIST_H
#define E04_ATLLIST_H

#include "atl.h"
#include "esArray.h"

typedef struct tabAtleti atlList;
typedef struct tabAtleti * atlList_p;

struct tabAtleti{
    int nAtleti;
    atleta_p head;
    atleta_p tail;
};

atlList_p crea_atlList();
void  distruggi_atlList(atlList_p lista);
atleta_p  ricerca_atleta(atlList_p lista, char * key);
void atList_add(atlList_p lista,atleta_p at);
void atList_remove(atlList_p lista,atleta_p at);
void set_chiave_codice(atlList_p lista);
void set_chiave_nome(atlList_p lista);
void set_chiave_cognome(atlList_p lista);
void set_chiave_categoria(atlList_p lista);
void set_nomeat(atlList_p lista,char * key,char *nome);
void set_cognome(atlList_p lista,char * key,char *cognome);
void set_codice(atlList_p lista,char * key,char *codice);
void set_data(atlList_p lista,char * key,char *data);
char * get_codice(atlList_p lista,char * key);
char * get_nome(atlList_p lista,char * key);
char * get_cognome(atlList_p lista,char * key);
char * get_data(atlList_p lista,char * key);
void leggi_atlList(atlList_p lista, FILE * fp);
void scrivi_atList(atlList_p lista,FILE * fp,int piano_es);
void print_categorie(atlList_p lista,FILE *fp);
void set_flag(atlList_p lista, char * key);
void output_atleta_flag(atlList_p ,FILE * fp,int piano_es);

#endif //E04_ATLLIST_H
