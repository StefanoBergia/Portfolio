#include "atleti.h"

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