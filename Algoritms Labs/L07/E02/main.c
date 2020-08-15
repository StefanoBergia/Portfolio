#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAXC 25

typedef  struct at atleta_t;
typedef struct esp eserPiano_t;
typedef struct es esercizio_t;

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


struct es{
    char nomeEs[MAXC+1];
    char catEs[MAXC+1];
    char tipoEs[MAXC+1];
};

struct esp{
    esercizio_t * es;
    int set;
    int rip;
    eserPiano_t * next;

};

typedef struct {
    esercizio_t * vettEs;
    int nEser;
}tabEser;

tabAtleti * leggiFile(FILE *fp);
void listAdd(tabAtleti *tab, atleta_t * new);
void listPrint(tabAtleti * tab,FILE * fp );
void listDelete(tabAtleti *tab,atleta_t * del);
void setChiaveCodice(tabAtleti * atleti);
void setChiaveCognome(tabAtleti * atleti);
void setChiaveNome(tabAtleti * atleti);
void setChiaveCategoria(tabAtleti * atleti);
void stampa_x_categoria(tabAtleti *lista);
void ricerca_lineare(tabAtleti *tab, char * chiave, int p,int f);
atleta_t * ricerca_lineare2(tabAtleti *tab, char * codice);
tabEser * leggiFileEs(FILE *fp);
esercizio_t * ricerca_lineareEs(tabEser *tab, char * nome);
void leggiFileEsP(tabEser * tab, atleta_t * atleta);
void freeEsP(atleta_t * a);
void freeAt(tabAtleti * tab);
void stampa_es(atleta_t * at,FILE *fp);
int leggiComando();
void modifica_set_rip(tabAtleti *tab,char * codice, char *nomeEs,int set, int rip);
void aggiorna_monte_ore(tabAtleti * tab,char * codice,int n_ore);

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

tabAtleti * leggiFile(FILE *fp){
    tabAtleti * ret;
    atleta_t * new;
    ret=(tabAtleti *)malloc(sizeof(tabAtleti));
    new=(atleta_t *)malloc(sizeof(atleta_t));
    ret->head=NULL;
    ret->tail=NULL;
    ret->nAtleti=0;
    while(fscanf(fp,"%s %s %s %s %s %d",new->codice,new->cognome,new->nome,new->categoria,new->data,&new->ore)!=EOF){
        new->chiave=NULL;
        new->flag=0;
        new->next=NULL;
        new->head=NULL;
        new->tail=NULL;
        listAdd(ret,new);
        new=(atleta_t *)malloc(sizeof(atleta_t));
    }
    return ret;
}

tabEser * leggiFileEs(FILE *fp){
    tabEser * ret;
    int i;
    ret=(tabEser *)malloc(sizeof(tabEser));
    fscanf(fp,"%d",&ret->nEser);
    ret->vettEs=(esercizio_t *)malloc(ret->nEser*sizeof(esercizio_t));
    for(i=0;i<ret->nEser;i++){
        fscanf(fp,"%s %s %s",ret->vettEs[i].nomeEs,ret->vettEs[i].catEs,ret->vettEs[i].tipoEs);
    }
    return ret;
}

void leggiFileEsP(tabEser * tab, atleta_t * atleta){
    eserPiano_t * new;
    FILE *fp;
    char  suppNome[MAXC+1];
    char path[MAXC+8]="../";
    new=(eserPiano_t *)malloc(sizeof(eserPiano_t));
    freeEsP(atleta);
    strcat(path,atleta->codice);
    strcat(path,".txt");
    fp=fopen(path,"r");
    //fp=fopen("../A0001.txt","r");
    while(fscanf(fp,"%s %d %d",suppNome,&new->set,&new->rip)!=EOF){
        new->es=ricerca_lineareEs(tab,suppNome);
        new->next=NULL;
        if(atleta->head==NULL)
            atleta->head=new;
        if(atleta->tail!=NULL)
            atleta->tail->next=new;
        atleta->tail=new;
        new=(eserPiano_t *)malloc(sizeof(eserPiano_t));
    }

    fclose(fp);

}

void listAdd(tabAtleti *tab, atleta_t * new){
    if(tab->head==NULL){
        tab->head=new;
        tab->tail=new;
        return;
    }
    tab->tail->next=new;
    tab->tail=new;
    tab->nAtleti++;
}

void listPrint(tabAtleti * tab,FILE * fp ){
    atleta_t * pt;
    pt=tab->head;
    if(pt!=NULL){
        while(pt!=tab->tail) {
            fprintf(fp, "%s %s %s %s %s %d\n", pt->codice, pt->cognome, pt->nome, pt->categoria,pt->data, pt->ore);
            stampa_es(pt,fp);
            pt=pt->next;
            fprintf(fp,"\n");
        }
        fprintf(fp, "%s %s %s %s %s %d", pt->codice, pt->cognome, pt->nome, pt->categoria,pt->data, pt->ore);
        stampa_es(pt,fp);
        fprintf(fp,"\n");
    }else
        fprintf(fp,"lista vuota");
}


void listDelete(tabAtleti *tab,atleta_t * del){
    if(tab->head==NULL)
        return;
    atleta_t * pt=tab->head->next;
    atleta_t * sup=tab->head;
    if(del==sup)
        tab->head=pt;
    while(pt!=tab->tail){
        if(pt==del) {
            sup->next=pt->next;
            freeEsP(del);
            free(del);
            return;
        }
        sup=pt;
        pt=pt->next;
    }
    if(del==tab->tail)
        tab->tail=sup;
    free(del);
    return;
}

void ricerca_lineare(tabAtleti *tab, char * chiave, int p,int f){
    atleta_t * supp=tab->head;
    while(supp!=NULL){
        if(strcmp(supp->chiave,chiave)==0 || (strstr(supp->chiave,chiave)!=NULL && p==1) ) {
            printf("%s %s %s %s %d\n", supp->codice, supp->cognome, supp->nome, supp->categoria, supp->ore);
            supp->flag=f;
        }
        supp=supp->next;
    }
}

atleta_t * ricerca_lineare2(tabAtleti *tab, char * codice){
    atleta_t * supp=tab->head;
    while(supp!=NULL){
        if(strcmp(supp->codice,codice)==0) {
            return supp;
        }
        supp=supp->next;
    }
    return NULL;
}

esercizio_t * ricerca_lineareEs(tabEser *tab, char * nome){
    int i;
    for(i=0;i<tab->nEser;i++)
        if(strcmp(tab->vettEs[i].nomeEs,nome)==0)
            return &(tab->vettEs[i]);
    return NULL;
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

void setChiaveCodice(tabAtleti * atleti){
    atleta_t * pt =atleti->head;
    while(pt!=NULL) {
        pt->chiave=pt->codice;
        pt=pt->next;
    }
}

void setChiaveCognome(tabAtleti * atleti){
    atleta_t * pt =atleti->head;
    while(pt!=NULL) {
        pt->chiave=pt->cognome;
        pt=pt->next;
    }
}

void setChiaveNome(tabAtleti * atleti){
    atleta_t * pt =atleti->head;
    while(pt!=NULL) {
        pt->chiave=pt->nome;
        pt=pt->next;
    }
}


void setChiaveCategoria(tabAtleti * atleti){
    atleta_t * pt =atleti->head;
    while(pt!=NULL) {
        pt->chiave=pt->categoria;
        pt=pt->next;
    }
}

void aggiorna_monte_ore(tabAtleti * tab,char * codice,int n_ore){
    atleta_t * at=ricerca_lineare2(tab,codice);
    if(at!=NULL)
        at->ore=n_ore;
}

void freeEsP(atleta_t * a){
    eserPiano_t * pt=a->head;
    while(pt!=a->tail){
        pt=a->head->next;
        free(a->head);
        a->head=pt;
    }
    free(pt);
    a->head=NULL;
    a->tail=NULL;
}

void freeAt(tabAtleti * tab){
    atleta_t * pt=tab->head;
    while(pt!=tab->tail){
        pt=tab->head->next;
        free(tab->head);
        tab->head=pt;
    }
    free(pt);
    free(tab);
}

void modifica_set_rip(tabAtleti *tab,char * codice, char *nomeEs,int set, int rip){
    atleta_t * at=ricerca_lineare2(tab,codice);
    if(at!=NULL){
        eserPiano_t * es=at->head;
        while (es!=NULL){
            if(strcmp(es->es->nomeEs,nomeEs)==0){
                es->rip=rip;
                es->set=set;
                return;
            }
            es=es->next;
        }
    }
}

void stampa_es(atleta_t * at,FILE *fp){
    eserPiano_t * pt;
    pt=at->head;
    if(pt!=NULL){
        while(pt!=at->tail) {
            fprintf(fp, "\t%s %d %d\n", pt->es->nomeEs, pt->set, pt->rip);
            pt=pt->next;
        }
        fprintf(fp, "\t%s %d %d\n", pt->es->nomeEs, pt->set, pt->rip);
    }else
        fprintf(fp,"\tnessun esercizio\n");
}