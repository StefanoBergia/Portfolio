#include "esList.h"

eserPiano_lp crea_listaEs(){
    eserPiano_lp lista=(eserPiano_lp)malloc(sizeof(eserPiano_l));
    lista->nEs=0;
    lista->head=NULL;
    lista->tail=NULL;
}

void distruggi_listaEs(eserPiano_lp lista){
    eserPiano_p cur,sup;
    int i;
    cur=lista->head;
    while(cur!=lista->tail){
        sup=cur->next;
        free(cur);
        cur=sup;
    }
    free(cur);
    free(lista);
}

void add_esPiano(eserPiano_lp lista,eserPiano_p piano){
    if(lista->head==NULL) {
        lista->head = piano;
        lista->tail=piano;
    }else
    {
        lista->tail->next=piano;
        lista->tail=piano;
    }
    lista->nEs++;
}

void removeEserPiano(eserPiano_lp lista,eserPiano_p piano){
    eserPiano_p  cur=lista->head,sup;
    if(cur==piano) {
        lista->head = lista->head->next;
        free(cur);
        return;
    }
    sup=cur->next;
    while(cur!=lista->tail){
        if(sup==piano){
            cur->next=sup->next;
            free(sup);
            return;
        }
        cur=cur->next;
        sup=sup->next;
    }
}

eserPiano_p ricerca_eserPiano(eserPiano_lp lista,char * nome_es){
    eserPiano_p cur=lista->head;
    while(cur!=NULL){
        if(strcmp(cur->es->nomeEs,nome_es)==0)
            return cur;
        cur=cur->next;
    }
    return NULL;
}

void set_ripetizioni(eserPiano_lp lista,char * nome_es,int rip){
        eserPiano_p es=ricerca_eserPiano(lista,nome_es);
        es->rip=rip;
}

void set_setr(eserPiano_lp lista,char * nome_es,int set){
    eserPiano_p es=ricerca_eserPiano(lista,nome_es);
    es->set=set;
}

void set_es(eserPiano_lp lista,char *nome,esercizio_p esp){
    eserPiano_p es=ricerca_eserPiano(lista,nome);
    es->es=esp;
}

int get_ripetizioni(eserPiano_lp lista,char * nome_es){
    eserPiano_p es=ricerca_eserPiano(lista,nome_es);
    return  es->rip;
}

int get_setr(eserPiano_lp lista,char * nome_es){
    eserPiano_p es=ricerca_eserPiano(lista,nome_es);
    return  es->set;
}

int get_nEs(eserPiano_lp lista){
    return  lista->nEs;
}

void leggi_esPiano(eserPiano_lp lista,esArray_p  array,FILE *fp){
    eserPiano_p new;
    char  suppNome[MAXC+1];
    new=(eserPiano_p)malloc(sizeof(eserPiano_t));
    while(fscanf(fp,"%s %d %d",suppNome,&new->set,&new->rip)!=EOF){
        new->es=ricerca_es(array,suppNome);
        new->next=NULL;
        add_esPiano(lista,new);
        new=(eserPiano_t *)malloc(sizeof(eserPiano_t));
    }
}

void scrivi_esPiano(eserPiano_lp lista,FILE *fp){
    eserPiano_p  cur=lista->head;
    while (cur!=NULL){
        fprintf(fp,"%s %d %d\n",cur->es->nomeEs,cur->set,cur->rip);
        cur=cur->next;
    }
}