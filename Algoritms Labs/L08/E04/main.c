#include <stdio.h>
#include "atlList.h"
#include "esList.h"

#define MAXC 25

int leggiComando();

int main(int argc, char **argv){
    FILE *fp;
    atlList_p atleti=crea_atlList();
    esArray_p esercizi=crea_esArray();
    atleta_p supp;
    int cmd,agg,set,rip;
    char ricerche[MAXC+1],ricerche2[MAXC+1];
    char path[MAXC+8]="../";
    if (argc == 3) {
        fp = fopen(argv[1], "r");
        leggi_atlList(atleti,fp);
        fclose(fp);
        fp=fopen(argv[2],"r");
        leggi_esArray(esercizi,fp);
        fclose(fp);
        do {
            cmd = leggiComando();
            switch (cmd) {
                case 1:
                    printf("\n");
                    scrivi_atList(atleti,stdout,1);
                    printf("\n");
                    break;
                case 2:
                    printf("\n");
                    set_chiave_categoria(atleti);
                    print_categorie(atleti,stdout);
                    printf("\n");
                    break;
                case 3:
                    printf("inserisci codice-->");
                    scanf("%s",ricerche);
                    set_chiave_codice(atleti);
                    supp=ricerca_atleta(atleti,ricerche);
                    if(supp!=NULL){
                        printf("\n");
                        output_atleta(supp,stdout,1);
                        printf("\n");
                    }
                    else
                        printf("elemento non trovato\n");
                    break;
                case 4:
                    printf("inserisci cognome-->");
                    scanf("%s",ricerche);
                    set_chiave_cognome(atleti);
                    set_flag(atleti,ricerche);
                    printf("\n");
                    output_atleta_flag(atleti,stdout,1);
                    printf("\n");
                    break;
                case 5:
                    printf("inserisci dati atleta (codice cognome nome categoria data monte ore)\n");
                    supp=input_atleta(stdin);
                    atList_add(atleti,supp);
                    printf("comando eseguito\n");
                    break;
                case 6:
                    printf("inserisci codice-->");
                    set_chiave_codice(atleti);
                    scanf("%s",ricerche);
                    supp=ricerca_atleta(atleti,ricerche);
                    if(supp!=NULL)
                        atList_remove(atleti,supp);
                    printf("comando eseguito\n");
                    break;
                case 7:
                    set_chiave_codice(atleti);
                    printf("inserisci codice-->");
                    scanf("%s",ricerche);
                    supp=ricerca_atleta(atleti,ricerche);
                    strcpy(path,"../");
                    strcat(path,supp->codice);
                    strcat(path,".txt");
                    fp=fopen(path,"r");
                    if(supp!=NULL)
                        leggi_esPiano(supp->esercizi,esercizi,fp);
                    printf("comando eseguito\n");
                    fclose(fp);
                    break;
                    break;
                case 8:
                    printf("inserisci codice nome esercizo set e ripetizioni");
                    scanf("%s %s %d %d",ricerche,ricerche2,&set,&rip);
                    set_chiave_codice(atleti);
                    supp=ricerca_atleta(atleti,ricerche);
                    set_ripetizioni(supp->esercizi,ricerche2,rip);
                    set_setr(supp->esercizi,ricerche2,set);
                    printf("comando eseguito\n");
                    break;
                case 9:
                    printf("\n");
                    scrivi_Array(esercizi,stdout);
                    printf("\n");
                    break;
                case 0:
                    printf(" fine programma");
                    break;
                default:
                    printf("comando non riconosciuto");
                    break;
            }
        } while(cmd>0);
        distruggi_listaEs(esercizi);
        distruggi_atlList(atleti);
    }
    return 0;
}

int leggiComando(){
    int n;
    printf("1-visualizza dati\n");
    printf("2-raggruppa atleti\n");
    printf("3-ricerca per codice\n");
    printf("4-ricerca per cognome\n");
    printf("5-aggiungi atleta\n");
    printf("6-elimina atleta\n");
    printf("7-carica esercizi per un atleta\n");
    printf("8-modifica il numero di set e ripetizioni per un atleta\n");
    printf("9-stampa elenco esercizi\n");
    printf("0-fine\n");
    printf("inserisci comando-->");
    scanf("%d",&n);
    return n;
}