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

    char dataR[10+1];
    char *chiave;
} atleta;


typedef struct{
    atleta ** codice;
    atleta ** nome;
    atleta ** cognome;
    atleta ** categoria;
    atleta ** data;
}ordinamenti;

atleta ** leggiFile(FILE *fp,int *n);
void stampaTabella(FILE *fp,atleta ** atleti,int n);
int leggiComando();
void ordina(atleta **atleti,ordinamenti * supp,int n);
void Merge(ordinamenti * ret,ordinamenti * ord,int l,int q,int r);
void MergeSort(ordinamenti * ret,ordinamenti * supp,int l,int r);
void raggruppAtleti(atleta ** atleti,int n);
void setChiaveCodice(atleta ** atleti,int n);
void setChiaveCognome(atleta ** atleti,int n);
void setChiaveNome(atleta ** atleti,int n);
void setChiaveData(atleta ** atleti,int n);
void setChiaveCategoria(atleta ** atleti,int n);
atleta** RicercaDicotomicaM(atleta ** atleti,int l,int r,char * chiave,int *n);
atleta * RicercaDicotomica(atleta ** atleti,int l,int r,char * chiave,int *i);


int main(int argc, char **argv) {
    FILE *fp;
    atleta **atleti,**supp;
    int n, cmd,i,agg,n_supp;
    char ricerche[MAXC];
    ordinamenti ord;

    if (argc == 2) {
        fp = fopen(argv[1], "r");
        atleti = leggiFile(fp, &n);
        fclose(fp);

        ordina(atleti,&ord,n);

        do {
            cmd = leggiComando();
            switch (cmd) {
                case 1:
                    stampaTabella(stdout,atleti,n);
                    break;
                case 2:
                    stampaTabella(stdout,ord.data,n);
                    break;
                case 3:
                    stampaTabella(stdout,ord.codice,n);
                    break;
                case 4:
                    stampaTabella(stdout,ord.cognome,n);
                    break;
                case 5:
                    raggruppAtleti(ord.categoria,n);
                    break;
                case 6:
                    printf("inserisci codice e aggiornamento ");
                    scanf("%s %d",ricerche,&agg);
                    setChiaveCodice(atleti,n);
                    supp=RicercaDicotomicaM(ord.codice,0,n-1,ricerche,&n_supp);
                    if(supp!=NULL) {
                        supp[0]->ore = agg;
                        printf("elemento aggiornato");
                    }
                    free(supp);
                    break;
                case 7:
                    printf("inserisci codice-->");
                    scanf("%s",ricerche);
                    setChiaveCodice(atleti,n);
                    supp=RicercaDicotomicaM(ord.codice,0,n-1,ricerche,&n_supp);
                    if(supp!=NULL)
                        stampaTabella(stdout,supp,n_supp);
                    free(supp);
                    break;
                case 8:
                    printf("inserisci cognome-->");
                    scanf("%s",ricerche);
                    setChiaveCognome(atleti,n);
                    supp=RicercaDicotomicaM(ord.cognome,0,n-1,ricerche,&n_supp);
                    if(supp!=NULL)
                        stampaTabella(stdout,supp,n_supp);
                    else
                        printf("elemento non trovato\n");
                    free(supp);
                    break;
                case 0:
                    printf(" fine programma");
                    break;
                default:
                    printf("comando non riconosciuto");
                    break;
            }
        } while(cmd>0);

        for(i=0;i<n;i++)
            free(atleti[i]);
        free(atleti);

        free(ord.codice);
        free(ord.nome);
        free(ord.cognome);
        free(ord.categoria);
        free(ord.data);
    }

    return 0;
}


int leggiComando(){
    int n;
    printf("\n1-visualizza dati\n");
    printf("2-ordina secondo la data\n");
    printf("3-ordina secondo il codice\n");
    printf("4-ordina secondo il cognome\n");
    printf("5-raggruppa atleti\n");
    printf("6-aggiorna monte ore\n");
    printf("7-ricerca per codice\n");
    printf("8-ricerca per cognome\n");
    printf("0-fine\n");
    printf("inserisci comando-->");
    scanf("%d",&n);
    return n;
}

atleta ** leggiFile(FILE *fp,int *n){
    int i,s_anno,s_mese,s_giorno;
    fscanf(fp,"%d",n);
    atleta ** atleti,**supp;
    atleti=(atleta **)malloc((*n)*sizeof(atleta*));
    supp=atleti;
    for(i=0;i<*n;i++,atleti++) {
        (*atleti)=(atleta *)malloc(sizeof(atleta));
        fscanf(fp, "%s %s %s %s %s %d", (*atleti)->codice, (*atleti)->nome, (*atleti)->cognome, (*atleti)->categoria, (*atleti)->data,
               &((*atleti)->ore));
        (*atleti)->chiave=NULL;
        sscanf((*atleti)->data,"%d/%d/%d",&s_giorno,&s_mese,&s_anno);
        sprintf((*atleti)->dataR,"%d/%d/%d",s_anno,s_mese,s_giorno);
    }
    return supp;

}

void stampaTabella(FILE *fp,atleta ** atleti,int n){

    int i;
    printf("\n");
    for (i=0;i<n;i++,atleti++)
        fprintf(fp,"%s  %s %s %s %s %d\n",(*atleti)->codice,(*atleti)->nome,(*atleti)->cognome,(*atleti)->categoria,(*atleti)->data,(*atleti)->ore);
    printf("\n");
}

void ordina(atleta **atleti,ordinamenti * ret,int n){

    int i=0;
    ordinamenti supp;
    ret->codice=(atleta **)malloc(n*sizeof(atleta *));
    ret->nome=(atleta **)malloc(n*sizeof(atleta *));
    ret->cognome=(atleta **)malloc(n*sizeof(atleta *));
    ret->categoria=(atleta **)malloc(n*sizeof(atleta *));
    ret->data=(atleta **)malloc(n*sizeof(atleta *));

    supp.codice=(atleta **)malloc(n*sizeof(atleta *));
    supp.nome=(atleta **)malloc(n*sizeof(atleta *));
    supp.cognome=(atleta **)malloc(n*sizeof(atleta *));
    supp.categoria=(atleta **)malloc(n*sizeof(atleta *));
    supp.data=(atleta **)malloc(n*sizeof(atleta *));

    for(i=0;i<n;i++){
        ret->codice[i]=atleti[i];
        ret->nome[i]=atleti[i];
        ret->cognome[i]=atleti[i];
        ret->categoria[i]=atleti[i];
        ret->data[i]=atleti[i];
    }


    MergeSort(ret,&supp,0,n-1);
}

void MergeSort(ordinamenti * ret,ordinamenti * supp,int l,int r){
    int q=(l+r)/2;
    if(l>=r)
        return;
    MergeSort(ret,supp,l,q);
    MergeSort(ret,supp,q+1,r);
    Merge(ret,supp,l,q,r);

    return;
}

void Merge(ordinamenti * ret,ordinamenti * ord,int l,int q,int r){
    int i1,i2,i3,i4,i5,j1,j2,j3,j4,j5,k;
    i1=i2=i3=i4=i5=l;
    j1=j2=j3=j4=j5=q+1;
    for(k=l;k<=r;k++){
        //ordinamento per nome
        if(i1>q)
            ord->nome[k]=ret->nome[j1++];
        else if(j1>r)
            ord->nome[k]=ret->nome[i1++];
        else if(strcmp(ret->nome[i1]->nome,ret->nome[j1]->nome)<=0)
            ord->nome[k]=ret->nome[i1++];
        else
            ord->nome[k]=ret->nome[j1++];

        //ordinamento per cognome
        if(i2>q)
            ord->cognome[k]=ret->cognome[j2++];
        else if(j2>r)
            ord->cognome[k]=ret->cognome[i2++];
        else if(strcmp(ret->cognome[i2]->cognome,ret->cognome[j2]->cognome)<0)
            ord->cognome[k]=ret->cognome[i2++];
        else if (strcmp(ret->cognome[i2]->cognome,ret->cognome[j2]->cognome)==0 && strcmp(ret->cognome[i2]->nome,ret->cognome[j2]->nome)<=0)
            ord->cognome[k]=ret->cognome[i2++];
        else
            ord->cognome[k]=ret->cognome[j2++];

        //ordinamento per categoria
        if(i3>q)
            ord->categoria[k]=ret->categoria[j3++];
        else if(j3>r)
            ord->categoria[k]=ret->categoria[i3++];
        else if(strcmp(ret->categoria[i3]->categoria,ret->categoria[j3]->categoria)<=0)
            ord->categoria[k]=ret->categoria[i3++];
        else
            ord->categoria[k]=ret->categoria[j3++];

        //ordinamento per data
        if(i4>q)
            ord->data[k]=ret->data[j4++];
        else if(j4>r)
            ord->data[k]=ret->data[i4++];
        else if(strcmp(ret->data[i4]->dataR,ret->data[j4]->dataR)<=0)
            ord->data[k]=ret->data[i4++];
        else
            ord->data[k]=ret->data[j4++];

        //ordinamento per codice
        if(i5>q)
            ord->codice[k]=ret->codice[j5++];
        else if(j5>r)
            ord->codice[k]=ret->codice[i5++];
        else if(strcmp(ret->codice[i5]->codice,ret->codice[j5]->codice)<=0)
            ord->codice[k]=ret->codice[i5++];
        else
            ord->codice[k]=ret->codice[j5++];
    }

    for(k=l;k<=r;k++) {
        ret->codice[k] = ord->codice[k];
        ret->nome[k] = ord->nome[k];
        ret->cognome[k] = ord->cognome[k];
        ret->categoria[k] = ord->categoria[k];
        ret->data[k] = ord->data[k];
    }
    return ;

}

void raggruppAtleti(atleta ** atleti,int n){    //bisogna passargli i vettore ordinato per categoria
    int i;
    char * cur_cat=NULL;
    for(i=0;i<n;i++){
        if(cur_cat==NULL || strcmp(cur_cat,atleti[i]->categoria)!=0){
            cur_cat=atleti[i]->categoria;
            printf("\n%s\n",cur_cat);
        }
        printf("%s\n",atleti[i]->codice);
    }
    printf("\n");

}

atleta** RicercaDicotomicaM(atleta ** atleti,int l,int r,char * chiave,int *n){
    atleta ** ret=NULL;
    *n=0;
    int count=1,j,i;
    atleta * supp=RicercaDicotomica(atleti,l,r,chiave,&i);
    if(supp!=NULL){
        for(i++; i<=r && strcmp(supp->chiave,atleti[i]->chiave)==0;count++,i++) ;
        for(i-=count; i>=l && strcmp(supp->chiave,atleti[i]->chiave)==0;count++,i--) ;
        count--;
        ret=(atleta **)malloc(count*sizeof(atleta *));
        for(j=0,i++;j<count;j++,i++)
            ret[j]=atleti[i];
        *n=count;
    }
    return ret;
}

atleta * RicercaDicotomica(atleta ** atleti,int l,int r,char * chiave,int *i){
    int q=(l+r)/2,supp;
    supp=strcmp(atleti[q]->chiave,chiave);
    if(supp==0) {
        *i=q;
        return atleti[q];
    }
    if(l>=r)
        return NULL;

    if(supp>0)
        return RicercaDicotomica(atleti,l,q,chiave,i);

    return RicercaDicotomica(atleti,q+1,r,chiave,i);

}

void setChiaveCodice(atleta ** atleti,int n){
    int i;
    for(i=0;i<n;i++)
        atleti[i]->chiave=atleti[i]->codice;
}

void setChiaveCognome(atleta ** atleti,int n){
    int i;
    for(i=0;i<n;i++)
        atleti[i]->chiave=atleti[i]->cognome;
}

void setChiaveNome(atleta ** atleti,int n){
    int i;
    for(i=0;i<n;i++)
        atleti[i]->chiave=atleti[i]->nome;
}

void setChiaveData(atleta ** atleti,int n){
    int i;
    for(i=0;i<n;i++)
        atleti[i]->chiave=atleti[i]->dataR;
}

void setChiaveCategoria(atleta ** atleti,int n){
    int i;
    for(i=0;i<n;i++)
        atleti[i]->chiave=atleti[i]->categoria;
}
