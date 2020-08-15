#include "atlList.h"

atlList_p crea_atlList(){
    atlList_p new=(atlList_p)malloc(sizeof(atlList));
    new->nAtleti=0;
    new->head=NULL;
    new->tail=NULL;
    return  new;
}

void  distruggi_atlList(atlList_p lista){
    atleta_p cur=lista->head;
    atleta_p  sup=cur->next;
    while(cur!=NULL){
        distruggi_atleta(cur);
        cur=sup;
        sup=sup->next;
    }
}

atleta_p  ricerca_atleta(atlList_p lista, char * key){
    atleta_p cur=lista->head;
    while (cur!=NULL){
        if(strcmp(cur->chiave,key)==0)
            return cur;
        cur=cur->next;
    }
    return NULL;
}

void set_flag(atlList_p lista, char * key){
    atleta_p cur=lista->head;
    while (cur!=NULL){
        if(strcmp(cur->chiave,key)==0)
            cur->flag=1;
        cur=cur->next;
    }
}

void atList_add(atlList_p lista,atleta_p at){
    if(lista->head==NULL){
        lista->head=at;
        lista->tail=at;
    }else {
        lista->tail->next = at;
        lista->tail=at;
    }
}
void atList_remove(atlList_p lista,atleta_p at){
    atleta_p cur=lista->head;
    atleta_p sup=cur->next;
    if(cur==at){
        lista->head=sup;
        distruggi_atleta(cur);
        return;;
    }
    while (cur!=NULL){
        if(sup==at)
        {
            cur->next=sup->next;
            distruggi_atleta(sup);
            return;
        }
        cur=sup;
        sup=sup->next;
    }
}

void set_chiave_codice(atlList_p lista){
    atleta_p cur=lista->head;
    while(cur!=NULL){
        cur->chiave=cur->codice;
        cur=cur->next;
    }
}

void set_chiave_nome(atlList_p lista){
    atleta_p cur=lista->head;
    while(cur!=NULL){
        cur->chiave=cur->nome;
        cur=cur->next;
    }
}
void set_chiave_cognome(atlList_p lista){
    atleta_p cur=lista->head;
    while(cur!=NULL){
        cur->chiave=cur->cognome;
        cur=cur->next;
    }
}

void set_chiave_categoria(atlList_p lista){
    atleta_p cur=lista->head;
    while(cur!=NULL){
        cur->chiave=cur->categoria;
        cur=cur->next;
    }
}

void set_nomeat(atlList_p lista,char * key,char *nome){
    atleta_p cur=ricerca_atleta(lista,key);
    strcpy(cur->nome,nome);
}

void set_cognome(atlList_p lista,char * key,char *cognome){
    atleta_p cur=ricerca_atleta(lista,key);
    strcpy(cur->cognome,cognome);
}

void set_codice(atlList_p lista,char * key,char *codice){
    atleta_p cur=ricerca_atleta(lista,key);
    strcpy(cur->codice,codice);
}

void set_data(atlList_p lista,char * key,char *data){
    atleta_p cur=ricerca_atleta(lista,key);
    strcpy(cur->data,data);
}
char * get_codice(atlList_p lista,char * key){
    atleta_p cur=ricerca_atleta(lista,key);
    return cur->codice;
}

char * get_nome(atlList_p lista,char * key){
    atleta_p cur=ricerca_atleta(lista,key);
    return cur->nome;
}
char * get_cognome(atlList_p lista,char * key){
    atleta_p cur=ricerca_atleta(lista,key);
    return cur->cognome;
}
char * get_data(atlList_p lista,char * key){
    atleta_p cur=ricerca_atleta(lista,key);
    return cur->data;
}

void leggi_atlList(atlList_p lista, FILE * fp){
    atleta_p  new;
    new=input_atleta(fp);
    while (new!=NULL){
        atList_add(lista,new);
        new=input_atleta(fp);
    }
}
void scrivi_atList(atlList_p lista,FILE * fp,int piano_es){
    atleta_p  cur=lista->head;
    while(cur!=NULL){
        output_atleta(cur,fp,piano_es);
        cur=cur->next;
    }
}

void print_categorie(atlList_p lista,FILE *fp){
    atleta_p sup=lista->head;
    atleta_p cur;
    while(sup!=NULL){
        if(sup->flag==0){
            fprintf(fp,"%s\n",sup->chiave);
            cur =lista->head;
            while (cur!=NULL){
                if(strcmp(cur->chiave,sup->chiave)==0 && cur->flag==0){
                    cur->flag=1;
                    output_atleta(cur,fp,0);
                }
                cur=cur->next;
            }
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


void output_atleta_flag(atlList_p lista ,FILE * fp,int piano_es){
    atleta_p cur=lista->head;
    while (cur!=NULL){
        if(cur->flag==1){
            cur->flag=0;
            output_atleta(cur,fp,piano_es);
        }
        cur=cur->next;
    }
}