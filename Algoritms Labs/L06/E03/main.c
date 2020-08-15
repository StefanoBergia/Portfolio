#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAXC 25

typedef struct{
    char codice[5+1];
    char nome[MAXC+1];
    char cognome[MAXC+1];
    char categoria[MAXC +1];
    char data[10+1];
    int ore;

    char *chiave;
    int flag;
} atleta;

typedef struct list list_atleta;
struct list {
    atleta * data;              //uso un puntatore ad atleta in modo da ottimizzare le ricerca
    list_atleta * next;
};

list_atleta * leggiFile(FILE *fp);
list_atleta * listAdd(list_atleta * lista,list_atleta * new);
void free_list(list_atleta * lista);
void free_list2(list_atleta * lista);
void setChiaveCodice(list_atleta * atleti);
void setChiaveNome(list_atleta * atleti);
void setChiaveCognome(list_atleta * atleti);
void setChiaveCategoria(list_atleta * atleti);
list_atleta * ricerca_lineare(list_atleta * lista, char * chiave,int p);
void stampa_x_categoria(list_atleta *lista);
void stampaLista(FILE *fp,list_atleta * lista);
int leggiComando();


int main(int argc, char ** argv) {
    FILE *fp;
    list_atleta *lista,*supp;
    int cmd,agg;
    char ricerche[MAXC];
    if (argc == 2) {
        fp = fopen(argv[1], "r");
        lista = leggiFile(fp);
        fclose(fp);
        do {
            cmd = leggiComando();
            switch (cmd) {
                case 1:
                    printf("\n");
                    stampaLista(stdout,lista);
                    break;
                case 2:
                    stampa_x_categoria(lista);
                    break;
                case 3:
                    printf("inserisci codice e aggiornamento ");
                    scanf("%s %d",ricerche,&agg);
                    setChiaveCodice(lista);
                    supp=ricerca_lineare(lista,ricerche,0);
                    if(supp!=NULL) {
                        supp->data->ore = agg;
                        printf("elemento aggiornato");
                    }
                    else
                        printf("elemento non trovato\n");
                    free_list2(supp);
                    break;
                case 4:
                    printf("inserisci codice-->");
                    scanf("%s",ricerche);
                    setChiaveCodice(lista);
                    supp=ricerca_lineare(lista,ricerche,0);
                    if(supp!=NULL)
                        stampaLista(stdout,supp);
                    else
                        printf("elemento non trovato\n");
                    free_list2(supp);
                    break;
                case 5:
                    printf("inserisci cognome-->");
                    scanf("%s",ricerche);
                    setChiaveCognome(lista);
                    supp=ricerca_lineare(lista,ricerche,1);
                    if(supp!=NULL)
                        stampaLista(stdout,supp);
                    else
                        printf("elemento non trovato\n");
                    free(supp);
                    break;
                case 6:
                    supp=(list_atleta *)malloc(sizeof(list_atleta));
                    supp->data=(atleta *)malloc(sizeof(atleta));
                    printf("inserisci dati atleta (codice nome cognome categoria data monte ore)\n");
                    scanf("%s %s %s %s %s %d",supp->data->codice,supp->data->nome,supp->data->cognome,supp->data->categoria,supp->data->data,&supp->data->ore);
                    lista=listAdd(lista,supp);
                    supp->next=NULL;
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
        free_list(lista);
    }

    return 0;
}

int leggiComando(){
    int n;
    printf("\n1-visualizza dati\n");
    printf("2-raggruppa atleti\n");
    printf("3-aggiorna monte ore\n");
    printf("4-ricerca per codice\n");
    printf("5-ricerca per cognome\n");
    printf("6-aggiungi atleta\n");
    printf("0-fine\n");
    printf("inserisci comando-->");
    scanf("%d",&n);
    return n;
}

list_atleta * leggiFile(FILE *fp){
    int i,n;
    fscanf(fp,"%d",&n);
    list_atleta * lista;
    list_atleta * supp;

    for(i=0;i<n;i++) {
        supp=(list_atleta *)malloc(sizeof(list_atleta));
        supp->data=(atleta *)malloc(sizeof(atleta));
        fscanf(fp, "%s %s %s %s %s %d", supp->data->codice, supp->data->nome, supp->data->cognome, supp->data->categoria, supp->data->data,
               &(supp->data->ore));
        supp->data->chiave=NULL;
        supp->data->flag=0;
        supp->next=NULL;
       lista= listAdd(lista,supp);
    }
    return lista;

}

list_atleta * listAdd(list_atleta * lista,list_atleta * new){
    list_atleta * sup;
    if(lista==NULL)
        lista=new;
    else {
        sup=lista;
        while (sup->next != NULL)
            sup = sup->next;
        sup->next=new;
    }
    return lista;
}

void free_list(list_atleta * lista){        //dealloco la lista e tutti gli atleti
    if(lista->next==NULL) {
        free (lista->data);
        free(lista);
    }
    else
        free_list(lista->next);
    return;
}

void free_list2(list_atleta * lista){       //dealloca solo la lista
    if(lista->next==NULL)
        free(lista);
    else
        free_list(lista->next);
    return;
}

void stampaLista(FILE *fp,list_atleta * lista){
    if(lista!=NULL) {
        fprintf(fp, "%s  %s %s %s %s %d\n", lista->data->codice, lista->data->nome, lista->data->cognome,
                lista->data->categoria, lista->data->data, lista->data->ore);
        printf("\n");
        stampaLista(fp,lista->next);
    }
}

list_atleta * ricerca_lineare(list_atleta * lista, char * chiave,int p){
    list_atleta * ret=NULL;
    list_atleta * new=NULL;
    list_atleta *supp=lista;
    while(supp!=NULL){
        if(strcmp(supp->data->chiave,chiave)==0 || (strstr(supp->data->chiave,chiave)!=NULL && p==1) )
        {
            new=(list_atleta *)malloc(sizeof(list_atleta));
            new->data=supp->data;
            new->next=NULL;
            ret=listAdd(ret,new);
        }
        supp=supp->next;
    }
    return ret;
}

void stampa_x_categoria(list_atleta *lista){
    list_atleta * sup=lista;
    list_atleta * cat,*sup_cat;
    setChiaveCategoria(lista);
    while(sup!=NULL){
        if(sup->data->flag==0){
            cat=ricerca_lineare(lista,sup->data->categoria,0);
            sup_cat=cat;
            printf("%s\n",sup->data->categoria);
            stampaLista(stdout,cat);
            while(sup_cat!=NULL){
                sup_cat->data->flag=1;
                sup_cat=sup_cat->next;
            }
            free_list2(cat);
        }
        sup=sup->next;
    }
    sup=lista;
    while (sup!=NULL){
        sup->data->flag=0;
        sup=sup->next;
    }
}

void setChiaveCodice(list_atleta * atleti){
    while(atleti!=NULL) {
        atleti->data->chiave=atleti->data->codice;
        atleti=atleti->next;
    }
}

void setChiaveCognome(list_atleta * atleti){
    while(atleti!=NULL) {
        atleti->data->chiave=atleti->data->cognome;
        atleti=atleti->next;
    }
}

void setChiaveNome(list_atleta * atleti){
    while(atleti!=NULL) {
        atleti->data->chiave=atleti->data->nome;
        atleti=atleti->next;
    }
}


void setChiaveCategoria(list_atleta * atleti){
    while(atleti!=NULL) {
        atleti->data->chiave=atleti->data->categoria;
        atleti=atleti->next;
    }
}
