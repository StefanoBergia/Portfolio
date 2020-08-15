#include <stdio.h>
#include <malloc.h>
#include "atleti.h"



#define MAXC 25

void stampa_x_categoria(tabAtleti *lista);
int leggiComando();

int main(int argc, char **argv){
    FILE *fp;
    tabAtleti * atleti;
    tabEser * esercizi;
    atleta_t * supp;
    int cmd,agg,set,rip;
    char ricerche[MAXC+1],ricerche2[MAXC+1];
    if (argc == 3) {
        fp = fopen(argv[1], "r");
        atleti = leggiFile(fp);
        fclose(fp);
        fp=fopen(argv[2],"r");
        esercizi=leggiFileEs(fp);
        fclose(fp);
        do {
            cmd = leggiComando();
            switch (cmd) {
                case 1:
                    printf("\n");
                    listPrint(atleti,stdout);
                    break;
                case 2:
                    printf("\n");
                    stampa_x_categoria(atleti);
                    printf("\n");
                    break;
                case 3:
                    printf("inserisci codice e aggiornamento ");
                    scanf("%s %d",ricerche,&agg);
                    aggiorna_monte_ore(atleti,ricerche,agg);
                    break;
                case 4:
                    printf("inserisci codice-->");
                    scanf("%s",ricerche);
                    setChiaveCodice(atleti);
                    supp=ricerca_lineare2(atleti,ricerche);
                    if(supp!=NULL) {
                        fprintf(stdout, "%s %s %s %s %d\n", supp->codice, supp->cognome, supp->nome, supp->categoria,
                                supp->ore);
                        stampa_es(supp,stdout);
                    }
                    else
                        printf("elemento non trovato\n");
                    break;
                case 5:
                    printf("inserisci cognome-->");
                    scanf("%s",ricerche);
                    setChiaveCognome(atleti);
                    ricerca_lineare(atleti,ricerche,1,0);
                    break;
                case 6:
                    supp=(atleta_t *)malloc(sizeof(atleta_t));
                    printf("inserisci dati atleta (codice cognome nome categoria data monte ore)\n");
                    scanf("%s %s %s %s %s %d",supp->codice,supp->cognome,supp->nome,supp->categoria,supp->data,&supp->ore);
                    supp->next=NULL;
                    listAdd(atleti,supp);
                    printf("comando eseguito");
                    break;
                case 7:
                    printf("inserisci codice-->");
                    scanf("%s",ricerche);
                    setChiaveCodice(atleti);
                    supp=ricerca_lineare2(atleti,ricerche);
                    if(supp!=NULL)
                        listDelete(atleti,supp);
                    printf("comando eseguito");
                    break;
                case 8:
                    printf("inserisci codice-->");
                    scanf("%s",ricerche);
                    setChiaveCodice(atleti);
                    supp=ricerca_lineare2(atleti,ricerche);
                    if(supp!=NULL)
                        leggiFileEsP(esercizi,supp);
                    printf("comando eseguito");
                    break;
                case 9:
                    printf("inserisci codice nome esercizo set e ripetizioni");
                    scanf("%s %s %d %d",ricerche,ricerche2,&set,&rip);
                    modifica_set_rip(atleti,ricerche,ricerche2,set,rip);
                    printf("comando eseguito");
                    break;
                case 0:
                    printf(" fine programma");
                    break;
                default:
                    printf("comando non riconosciuto");
                    break;
            }
        } while(cmd>0);
        freeAt(atleti);
        free(esercizi->vettEs);
        free(esercizi);
    }
    return 0;
}

int leggiComando(){
    int n;
    printf("1-visualizza dati\n");
    printf("2-raggruppa atleti\n");
    printf("3-aggiorna monte ore\n");
    printf("4-ricerca per codice\n");
    printf("5-ricerca per cognome\n");
    printf("6-aggiungi atleta\n");
    printf("7-elimina atleta\n");
    printf("8-carica esercizi per un atleta\n");
    printf("9-modifica il numero di set per un atleta\n");
    printf("0-fine\n");
    printf("inserisci comando-->");
    scanf("%d",&n);
    return n;
}

void stampa_x_categoria(tabAtleti *lista){
    setChiaveCategoria(lista);
    atleta_t * sup=lista->head;
    while(sup!=NULL){
        if(sup->flag==0){
            printf("%s\n",sup->categoria);
            ricerca_lineare(lista,sup->categoria,0,1);
            printf("\n");
        }
        sup=sup->next;
    }
    sup=lista->head;
    while (sup!=NULL){
        sup->flag=0;
        sup=sup->next;
    }
}