#include "atl.h"

atleta_p crea_atleta(){
    atleta_p new=(atleta_p)malloc(sizeof(atleta_t));
    new->codice[0]='\0';
    new->nome[0]='\0';
    new->cognome[0]='\0';
    new->categoria[0]='\0';
    new->data[0]='\0';
    new->chiave=NULL;
    new->flag=0;
    new->next=NULL;
    new->esercizi=crea_listaEs();
    return  new;
}

void distruggi_atleta(atleta_p at){
    if(at!=NULL){
        distruggi_listaEs(at->esercizi);
        free(at);
    }
}

atleta_p input_atleta(FILE *fp){
    atleta_p  new=crea_atleta();
    if(fp!=NULL && !feof(fp)){
        fscanf(fp,"%s %s %s %s %s %d",new->codice,new->cognome,new->nome,new->categoria,new->data,&new->ore);
        return new;
    }
    return NULL;
}

void output_atleta(atleta_p at ,FILE *fp,int print_pianoEs){
    if(fp!=NULL){
        fprintf(fp,"%s %s %s %s %s %d\n",at->codice,at->cognome,at->nome,at->categoria,at->data,at->ore);
        if(print_pianoEs){
            scrivi_esPiano(at->esercizi,fp);
            printf("\n");
        }

    }
}